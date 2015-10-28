#ifdef ANDROID_PLATFORM

#ifndef GAMESERVICES_H
#define GAMESERVICES_H

#define JUIHELPER_CLASS_NAME "com.PukApp.MPACK"

#include <jni.h>
#include <android_native_app_glue.h>
#include <string>
#include <sstream>
#include "gpg/gpg.h"

using namespace std;

namespace MPACK
{
	namespace SERVICES
	{
		class GameServices
		{
			public:
				const static int ERROR_CONNECTING = -1;
				const static int OFFLINE = 0;
				const static int CONNECTING = 1;
				const static int ONLINE = 2;
				const static int DISCONNECTING = 3;

				const static int NOTHING = 0;
				const static int SAVING = 1;
				const static int SAVING_ERROR = -1;
				const static int SAVING_OK = 3;
				const static int LOADING = 2;
				const static int LOADING_ERROR = -2;
				const static int LOADING_OK = 4;

			private:
				ANativeActivity* mActivity;
				jobject mClazz;
				gpg::AndroidPlatformConfiguration mPlatformConfiguration;
				std::unique_ptr<gpg::GameServices> mGameServices;
				string mConnectedClientId = "";
				int mConnectionState = OFFLINE;

				int mMaxRetry;
				int mMaxSnapshots;
				bool mAllowCreateSnapshotInUI;
				bool mAllowDeleteSnapshotInUI;
				char* mSnapshotUITitle;
				gpg::SnapshotMetadata mCurrentSnapshot;
				vector<unsigned char> mCurrentSnapshotData;
				int mSavedGameState = NOTHING;

			public:
				//GameServices login methods
				GameServices();
				void signIn();
				void signOut();
				int getState();
				void loadSnapShotUI();
				void destroy();
				int getConnectionState();
				string getConnectedClientId();

			public:
				//Saved games methods
				void initSavedGames(const int max_snapshots,const bool allow_create, const bool allow_delete, const char* title);
				void save(const vector<unsigned char> new_data,const char* description, const char* png_path);
				void save(const vector<unsigned char> new_data,const char* description, const vector<unsigned char> &png);
				void save(const vector<unsigned char> new_data,const char* description);
				void fetchSaves();
				int getSavedGameState();
				vector<unsigned char> getCurrentSaveData();
				bool ableToStartSavingProcess();
				bool ableToStartLoadingProcess();

			public:
				void OnAuthActionStarted(gpg::AuthOperation op);
				void OnAuthActionFinished(gpg::AuthOperation op, gpg::AuthStatus status);

			private :
				//private Save games methods
				bool resolveConflicts(gpg::SnapshotManager::OpenResponse const &openResponse, const int retry);
				void loadFromSnapshot();
				string generateSaveFileName();
				vector<unsigned char> setupSnapshotData();
				vector<unsigned char> getImageBytes(const char* path);
		};
	}
}


#endif
#endif
