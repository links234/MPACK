#ifdef ANDROID_PLATFORM

#include "GameServices.hpp"
#include "Global.hpp"
#include "Resources.hpp"


namespace MPACK
{
	namespace SERVICES
	{
		bool mCanceledGameServicesLoginProcess = false;

		GameServices::GameServices()
		{
			mActivity = MPACK::Global::pAndroidApp->activity;
			mClazz = MPACK::Global::pAndroidApp->activity->clazz;
			mProcessing = 0;

			//init
			mSilentLogin = true;
			mPlatformConfiguration.SetActivity(mClazz);
			mGameServices = gpg::GameServices::Builder()
			        .SetDefaultOnLog(gpg::LogLevel::VERBOSE)
			        .SetOnAuthActionStarted([this](gpg::AuthOperation op) {
						OnAuthActionStarted(op);
			        })
			        .SetOnAuthActionFinished([this](gpg::AuthOperation op, gpg::AuthStatus status) {
						OnAuthActionFinished(op, status);
			        })
			        .EnableSnapshots()
			        .Create(mPlatformConfiguration);
		}

		GameServices::~GameServices()
		{
			LOGI("DEACTIVTE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
			//mGameServices->FlushBlocking();
			mGameServices.reset();
			mGameServices = nullptr;
		}

		void GameServices::OnAuthActionStarted(gpg::AuthOperation op)
		{
			mProcessing++;
			if (mConnectionState != DISCONNECTING)
				mConnectionState = CONNECTING;
			LOGI("OnAuthActionStarted %d", op);
			//mConnectionState = CONNECTING;
		}

		int GameServices::isProcessing()
		{
			return mProcessing;
		}

		void GameServices::OnAuthActionFinished(gpg::AuthOperation op, gpg::AuthStatus status)
		{
			LOGI("OnAuthActionFinisged %d %d",op, status);
			if (op == gpg::AuthOperation::SIGN_OUT)
			{
				LOGI("RIGHT HERE");
				mConnectionState = OFFLINE;
				LOGI("HEREEEEEE");
				mSilentLogin = false;
				mProcessing--;
				return;
			}
			LOGI("OnAuthActionFinisged %d",status);
			if (gpg::IsSuccess(status))
			{
				if (mGameServices != nullptr)
				{
					gpg::PlayerManager::FetchSelfResponse response = mGameServices->Players().FetchSelfBlocking(std::chrono::milliseconds(2000));
					if (gpg::IsSuccess(response.status))
					{
						mConnectedClientId = response.data.Id();
						LOGI("mConnectClientId = %s",response.data.Id().c_str());
					}
					else
					{
						LOGI("Error fetching reponse");
						mConnectedClientId = "";
					}
					fetchSaves();
				}
				mSilentLogin = false;
			}
			else
			{
				LOGI("STATUS = %d", status);
				if (!mCanceledGameServicesLoginProcess && !mSilentLogin)
					mConnectionState = ERROR_CONNECTING;
				else
					mConnectionState = OFFLINE;
				mCanceledGameServicesLoginProcess = false;
				mSilentLogin = false;
			}
			mProcessing--;
			LOGI("Schimbare status onAuthActionFinished");
		}

		void GameServices::signOut()
		{
			LOGI("mConnectionState = %d", mConnectionState);
			if (mGameServices != nullptr && mConnectionState == ONLINE && mGameServices->IsAuthorized()
					&& (mSavedGameState != SAVING && mSavedGameState != LOADING))
			{
				LOGI("Signout process started");
				mCurrentSnapshotData.clear();
				if (mGameServices != nullptr) mGameServices->SignOut();
				mConnectionState = DISCONNECTING;
				mConnectedClientId = "";
			}
		}

		void GameServices::signIn()
		{

			if (mGameServices != nullptr && !mGameServices->IsAuthorized() && (mConnectionState == OFFLINE || mConnectionState == ERROR_CONNECTING) )
			{
				LOGI("Signin process started");
				mConnectedClientId = "";
				mConnectionState = CONNECTING;
				if (mGameServices != nullptr)  mGameServices->StartAuthorizationUI();
			}
		}

		string GameServices::getConnectedClientId()
		{
			if (mConnectionState == ONLINE)
			{
				if (mConnectedClientId == "")
				{
					if (mGameServices != nullptr)
					{
						gpg::PlayerManager::FetchSelfResponse response = mGameServices->Players().FetchSelfBlocking(std::chrono::milliseconds(2000));
						if (gpg::IsSuccess(response.status))
						{
							mConnectedClientId = response.data.Id();
							LOGI("id == %s",response.data.Id().c_str());
						}
						else
						{
							LOGI("Error fetching response for id!");
							return mConnectedClientId;
						}
					}
					else
						return "";
				}
				else
				{
					return mConnectedClientId;
				}
			}
			else
				return "";
		}

		int GameServices::getConnectionState()
		{
			return mConnectionState;
		}

		void GameServices::resetConnectionState()
		{
			if (mConnectionState == ERROR_CONNECTING)
				mConnectionState = OFFLINE;
		}

		void GameServices::initSavedGames(const int max_snapshots,const bool allow_create, const bool allow_delete, const char* title)
		{
			mMaxSnapshots = max_snapshots;
			mAllowCreateSnapshotInUI = allow_create;
			mAllowDeleteSnapshotInUI = allow_delete;
			mSnapshotUITitle = new char[strlen(title)+1];
			memcpy(mSnapshotUITitle, title, strlen(title));
			mSnapshotUITitle[strlen(title)] = 0;
		}

		int GameServices::getSavedGameState()
		{
			return  mSavedGameState;
		}

		bool GameServices::ableToStartLoadingProcess()
		{
			if (mConnectionState != ONLINE) return false;
			if (mSavedGameState == SAVING || mSavedGameState == LOADING)
				return false;
			return true;
		}

		bool GameServices::ableToStartSavingProcess()
		{
			if (mConnectionState != ONLINE) return false;
			if (mSavedGameState == SAVING || mSavedGameState == LOADING)
				return false;
			return true;
		}

		vector<unsigned char> GameServices::getImageBytes(const char* path)
		{
			MPACK::Core::AssetInputResource asset = MPACK::Core::AssetInputResource(path);
			asset.Open();
			vector<unsigned char> res;
			LOGI("path = %s",path);
			unsigned char * buffer = (unsigned char*) asset.Bufferize();
			res.assign(  buffer, buffer + asset.GetLength());
			asset.Close();
			return res;
		}

		vector<unsigned char> GameServices::getCurrentSaveData()
		{
			return mCurrentSnapshotData;
		}

		void GameServices::save(const vector<unsigned char> new_data, const char* description, const char* png_path)
		{
			mProcessing++;
			if (!ableToStartSavingProcess())
			{
				LOGI("Another process already! %d %d",mConnectionState, mSavedGameState);
				mProcessing--;
				return;
			}
			mSavedGameState = SAVING;
			std::string fileName;
			if (mCurrentSnapshot.Valid() == false)
			{
				fetchSnapshot();
			}

			if (mCurrentSnapshot.Valid() == false)
			{
				fileName = generateSaveFileName();
				LOGI("Creating new snapshot %s", fileName.c_str());
			}
			else
			{
				fileName = mCurrentSnapshot.FileName();
			}

			if (mGameServices != nullptr)
				mGameServices->Snapshots().Open(fileName, gpg::SnapshotConflictPolicy::LONGEST_PLAYTIME, [this, png_path, description, new_data](gpg::SnapshotManager::OpenResponse const & response)
				{
					LOGI("Opened file");
					if (IsSuccess(response.status))
					{
						gpg::SnapshotMetadata metadata = response.data;
						if (response.conflict_id != "")
						{
							//Conflict detected
							LOGI("Snapshot conflict detected going to resolve that");
							bool b = resolveConflicts(response, 0);
							if (!b)
							{
								LOGI("Failed resolving conflicts");
								mSavedGameState = SAVING_ERROR;
								mProcessing--;
								return;
							}
						}

						//Create image to represent the snapshot
						//Reading png from asset for now
						std::vector<unsigned char> pngData = getImageBytes(png_path);

						gpg::SnapshotMetadataChange::Builder builder;
						gpg::SnapshotMetadataChange metadata_change =
						builder.SetDescription(description)
							.SetCoverImageFromPngData(pngData).Create();

						// Save the snapshot.
						gpg::SnapshotManager::CommitResponse commitResponse = mGameServices->Snapshots()
							  .CommitBlocking(metadata, metadata_change, new_data);


						if (IsSuccess(commitResponse.status))
						{
							mSavedGameState = SAVING_OK;
							LOGI("Saved game");
//							if (mCurrentSnapshot.Valid() == false)
//								fetchSaves();
//							else
							mCurrentSnapshotData = new_data;
						}
						else
						{
							mSavedGameState = SAVING_ERROR;
							LOGI("Saved game failed error: %d", commitResponse.status);
						}
						mProcessing--;
					}
					else
					{
						mSavedGameState = SAVING_ERROR;
						mProcessing--;
					}
				});
		}

		void GameServices::save(const vector<unsigned char> new_data, const char* description)
		{
			mProcessing++;
			if (!ableToStartSavingProcess())
			{
				LOGI("Another process already! %d %d",mConnectionState, mSavedGameState);
				mProcessing--;
				return;
			}
			mSavedGameState = SAVING;
			std::string fileName;
			if (mCurrentSnapshot.Valid() == false)
			{
				fetchSnapshot();
			}

			if (mCurrentSnapshot.Valid() == false)
			{
				fileName = generateSaveFileName();
				LOGI("Creating new snapshot %s", fileName.c_str());
			}
			else
			{
				fileName = mCurrentSnapshot.FileName();
			}

			if (mGameServices != nullptr)
				mGameServices->Snapshots().Open(fileName, gpg::SnapshotConflictPolicy::LONGEST_PLAYTIME, [this,  description, new_data](gpg::SnapshotManager::OpenResponse const & response)
				{
					LOGI("Opened file");
					if (IsSuccess(response.status))
					{
						gpg::SnapshotMetadata metadata = response.data;
						if (response.conflict_id != "")
						{
							//Conflict detected
							LOGI("Snapshot conflict detected going to resolve that");
							bool b = resolveConflicts(response, 0);
							if (!b)
							{
								LOGI("Failed resolving conflicts");
								mSavedGameState = SAVING_ERROR;
								mProcessing--;
								return;
							}
						}

						//Create image to represent the snapshot
						//Reading png from asset for now

						gpg::SnapshotMetadataChange::Builder builder;
						gpg::SnapshotMetadataChange metadata_change =
						builder.SetDescription(description)
							.Create();

						LOGI("Got here2");
						// Save the snapshot.
						gpg::SnapshotManager::CommitResponse commitResponse = mGameServices->Snapshots()
							  .CommitBlocking(metadata, metadata_change, new_data);

						LOGI("Got here3");

						if (IsSuccess(commitResponse.status))
						{
							mSavedGameState = SAVING_OK;
							LOGI("Saved game");
//							if (mCurrentSnapshot.Valid() == false)
//							{
//								fetchSaves();
//							}
							mCurrentSnapshotData = new_data;
						}
						else
						{
							mSavedGameState = SAVING_ERROR;
							LOGI("Saved game failed error: %d", commitResponse.status);
						}
						mProcessing--;
					}
					else
					{
						mSavedGameState = SAVING_ERROR;
						mProcessing--;
					}
				});
		}

		void GameServices::save(const vector<unsigned char> new_data, const char* description, const vector<unsigned char> & png)
		{
			mProcessing++;
			if (!ableToStartSavingProcess())
			{
				LOGI("Another process already! %d %d",mConnectionState, mSavedGameState);
				mProcessing--;
				return;
			}
			mSavedGameState = SAVING;
			std::string fileName;
			if (mCurrentSnapshot.Valid() == false)
			{
				fetchSnapshot();
			}

			if (mCurrentSnapshot.Valid() == false)
			{
				fileName = generateSaveFileName();
				LOGI("Creating new snapshot %s", fileName.c_str());
			}
			else
			{
				fileName = mCurrentSnapshot.FileName();
			}

			mGameServices->Snapshots().Open(fileName, gpg::SnapshotConflictPolicy::LONGEST_PLAYTIME, [this, png, description, new_data](gpg::SnapshotManager::OpenResponse const & response)
			{
				LOGI("Opened file");
				if (IsSuccess(response.status))
				{
					gpg::SnapshotMetadata metadata = response.data;
					if (response.conflict_id != "")
					{
						//Conflict detected
						LOGI("Snapshot conflict detected going to resolve that");
						bool b = resolveConflicts(response, 0);
						if (!b)
						{
							LOGI("Failed resolving conflicts");
							mSavedGameState = SAVING_ERROR;
							mProcessing--;
							return;
						}
					}

					//Create image to represent the snapshot
					//Reading png from asset for now

					gpg::SnapshotMetadataChange::Builder builder;
					gpg::SnapshotMetadataChange metadata_change =
					builder.SetDescription(description)
						.SetCoverImageFromPngData(png).Create();

					LOGI("Got here2");
					// Save the snapshot.
					gpg::SnapshotManager::CommitResponse commitResponse = mGameServices->Snapshots()
						  .CommitBlocking(metadata, metadata_change, new_data);

					LOGI("Got here3");

					if (IsSuccess(commitResponse.status))
					{
						mSavedGameState = SAVING_OK;
						LOGI("Saved game");
//						if (mCurrentSnapshot.Valid() == false)
//							fetchSaves();
//						else
						mCurrentSnapshotData = new_data;
					}
					else
					{
						mSavedGameState = SAVING_ERROR;
						LOGI("Saved game failed error: %d", commitResponse.status);
					}
					mProcessing--;
				}
				else
				{
					mSavedGameState = SAVING_ERROR;
					mProcessing--;
				}
			});
		}

		void GameServices::fetchSnapshot()
		{
			gpg::SnapshotManager::FetchAllResponse response;
			do
			{
				response = mGameServices->Snapshots().FetchAllBlocking(std::chrono::milliseconds(1000));
			}
			while (!IsSuccess(response.status));

			if (response.data.size() > 0)
			{
				mCurrentSnapshot = response.data[0];
			}
		}

		void GameServices::loadSnapShotUI()
		{
			mProcessing++;
			if (!ableToStartLoadingProcess())
			{
				LOGI("Another process already! %d %d",mConnectionState, mSavedGameState);
				mProcessing--;
				return;
			}
			mSavedGameState = LOADING;
			if (mGameServices != nullptr)
				mGameServices->Snapshots().ShowSelectUIOperation(
					  mAllowCreateSnapshotInUI,
					  mAllowDeleteSnapshotInUI,
					  mMaxSnapshots,
					  mSnapshotUITitle,
					  [this](gpg::SnapshotManager::SnapshotSelectUIResponse const & response)
					  {
							LOGI("Snapshot selected");
							if (IsSuccess(response.status))
							{
								if (response.data.Valid())
								{
									LOGI("Description: %s", response.data.Description().c_str());
									LOGI("FileName %s", response.data.FileName().c_str());

									//Opening the snapshot data
									mCurrentSnapshot = response.data;
									loadFromSnapshot();
								}
								else
								{
									mSavedGameState = LOADING_ERROR;
									LOGI("Creating new snapshot");
									//saveSnapshot();
								}
							}
							else
							{
								LOGI("ShowSelectUIOperation returns an error %d", response.status);
								mSavedGameState = LOADING_ERROR;
							}
							mProcessing--;
					  });
		}

		void GameServices::fetchSaves()
		{
			mProcessing++;
			mSavedGameState = LOADING;
			LOGI("FetchSaves");
			if (mGameServices != nullptr)
			{
				gpg::SnapshotManager::FetchAllResponse response;
				do
				{
					response = mGameServices->Snapshots().FetchAllBlocking(std::chrono::milliseconds(1000));
				}
				while (!IsSuccess(response.status));

				if (IsSuccess(response.status))
				{
					LOGI("Success FetchingAllResponse");
					if (response.data.size() > 0)
					{
						mCurrentSnapshot = response.data[0];
					}
				}
				else
					LOGI("FetchingAllResponse error!");
				loadFromSnapshot();
			}
			mProcessing--;
		}

		void GameServices::loadFromSnapshot()
		{
			mProcessing++;
			if (!mCurrentSnapshot.Valid()) {
			    LOGI("Snapshot is not valid!");
			    mSavedGameState = LOADING_ERROR;
			    mConnectionState = ONLINE;
			    mProcessing--;
			    return;
			  }
			LOGI("Opening file");
			if (mGameServices != nullptr)
				mGameServices->Snapshots()
					.Open(mCurrentSnapshot.FileName(),
					gpg::SnapshotConflictPolicy::LONGEST_PLAYTIME,
					[this](gpg::SnapshotManager::OpenResponse const & response)
						{
							LOGI("Opened file");
							if (IsSuccess(response.status))
							{
								  //Do need conflict resolution?
								  if (response.data.Valid() == false)
								  {
										if (response.conflict_id != "")
										{
											LOGI("Need conflict resolution");
											bool b = resolveConflicts(response, 0);
											if (!b)
											{
												mSavedGameState = LOADING_ERROR;
												LOGI("Failed resolving conflicts");
												mProcessing--;
												return;
											}
										}
										else
										{
											mSavedGameState = LOADING_ERROR;
											mProcessing--;
											return;
										}
								  }

								  LOGI("Reading file %d", mProcessing);
								  if (mGameServices != nullptr)
								  {
									  gpg::SnapshotManager::ReadResponse responseRead =
										  mGameServices->Snapshots().ReadBlocking(response.data);
									  if (IsSuccess(responseRead.status))
									  {
										  LOGI("Data loaded");
										  mCurrentSnapshotData = responseRead.data;
										  mSavedGameState = LOADING_OK;
									  }
									  else
										  mSavedGameState = LOADING_ERROR;
								  }
								  mProcessing--;
								  mConnectionState = ONLINE;
							}
							else
							{
								mSavedGameState = LOADING_ERROR;
								LOGI("Error opening snapshot!");
								mConnectionState = ONLINE;
								mProcessing--;
							}

						});
		}

		bool GameServices::resolveConflicts(gpg::SnapshotManager::OpenResponse const &openResponse, const int retry)
		{
			//Here should be written the Manual Merge method

			return true;
		}

		string GameServices::generateSaveFileName()
		{
			timeval Time;
			gettimeofday(&Time, NULL);

			std::ostringstream str;
			str << "snapshotTemp-" << Time.tv_usec;

			return str.str();
		}
	}
}


void setCancel()
{
	MPACK::SERVICES::mCanceledGameServicesLoginProcess = true;
}

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
	gpg::AndroidInitialization::JNI_OnLoad(vm);

	return JNI_VERSION_1_6;
}


extern "C" {
	/*
	 * These callbacks are necessary to work Google Play Game Services UIs properly
	 *
	 * For apps which target Android 2.3 or 3.x devices (API Version prior to 14),
	 * Play Game Services has no way to automatically receive Activity lifecycle
	 * callbacks. In these cases, Play Game Services relies on the owning Activity
	 * to notify it of lifecycle events. Any Activity which owns a GameServices
	 * object should call the AndroidSupport::* functions from within their own
	 * lifecycle callback functions. The arguments in these functions match those
	 * provided by Android, so no additional processing is necessary.
	 */
	JNIEXPORT void
	Java_com_PukApp_ElasticEscape_MainActivity_nativeOnActivityResult(
		JNIEnv *env, jobject thiz, jobject activity, jint requestCode,
		jint resultCode, jobject data)
	{
	  if (resultCode == 0)
	  {
		  setCancel();
	  }
	  gpg::AndroidSupport::OnActivityResult(env, activity, requestCode, resultCode,
											data);
	}

	JNIEXPORT void
	Java_com_PukApp_ElasticEscape_MainActivity_nativeOnActivityCreated(
		JNIEnv *env, jobject thiz, jobject activity, jobject saved_instance_state)
	{
	  gpg::AndroidSupport::OnActivityCreated(env, activity, saved_instance_state);
	}

	JNIEXPORT void
	Java_com_PukApp_ElasticEscape_MainActivity_nativeOnActivityDestroyed(
		JNIEnv *env, jobject thiz, jobject activity)
	{
	  gpg::AndroidSupport::OnActivityDestroyed(env, activity);
	}

	JNIEXPORT void
	Java_com_PukApp_ElasticEscape_MainActivity_nativeOnActivityPaused(
		JNIEnv *env, jobject thiz, jobject activity) {
	  gpg::AndroidSupport::OnActivityPaused(env, activity);
	}

	JNIEXPORT void
	Java_com_PukApp_ElasticEscape_MainActivity_nativeOnActivityResumed(
		JNIEnv *env, jobject thiz, jobject activity)
	{
	  gpg::AndroidSupport::OnActivityResumed(env, activity);
	}

	JNIEXPORT void
	Java_com_PukApp_ElasticEscape_MainActivity_nativeOnActivitySaveInstanceState(
		JNIEnv *env, jobject thiz, jobject activity, jobject out_state)
	{
	  gpg::AndroidSupport::OnActivitySaveInstanceState(env, activity, out_state);
	}

	JNIEXPORT void
	Java_com_PukApp_ElasticEscape_MainActivity_nativeOnActivityStarted(
		JNIEnv *env, jobject thiz, jobject activity)
	{
	  gpg::AndroidSupport::OnActivityStarted(env, activity);
	}

	JNIEXPORT void
	Java_com_PukApp_ElasticEscape_MainActivity_nativeOnActivityStopped(
		JNIEnv *env, jobject thiz, jobject activity)
	{
	  gpg::AndroidSupport::OnActivityStopped(env, activity);
	}
}

#endif
