#include "Playlist.hpp"
#include "Resource.hpp"


namespace Core
{
	Playlist::Playlist(const char* pPath) :
        mSound(NULL), mPlayMode(FORWARD), mLoop(true)
    {
		Load(pPath, true);

    }


	Playlist::~Playlist()
	{
		delete mSound;


	}

	void Playlist::Load(const char* pPath, bool forced)
	{
		strcpy(mNFile, pPath);
		if(forced)
			useNewPlist();
	}

	void Playlist::useNewPlist()
	{
		mList.clear();

		char *plist;

		Resource *pResource=Core::LoadResource(mNFile);
		pResource->Open();
		int size = pResource->GetLength();

		plist = new char[size];


		pResource->Read(plist, size);
		pResource->Close();
		delete pResource;

		int len = 0, maxLen = 0, num = 0;

		for(int i = 0; plist[i] != '\0'; i++)
		{
			len++;
			if(plist[i] == '\n')
			{
				num++;
				if(len > maxLen)
				{
					maxLen = len;
				}

				while(plist[i+1] == '\n')
				{
					i++;
				}

				len = 0;
			}
		}




		mList.resize(num);

		int p = 0;
		list<vector<char> >::iterator t = mList.begin();
		num = 0;
		for(int i = 0; plist[i] != '\0' && num < mList.size(); i++)
		{

			if(plist[i] == '\n')
			{
				(*t).push_back('\0');
				t++;
				p=0;
				num++;

				while(plist[i+1] == '\n')
				{
					i++;
				}

			}
			else
			{
				(*t).push_back(plist[i]);
				p++;
			}
		}

		mCurTrackIt = mList.begin();

		if(mSound != NULL)
			delete mSound;

		mSound = new Sound(&(*mCurTrackIt)[0] );
		mSound->Load();

		delete [] plist;

		strcpy(mCFile, mNFile);
		mNFile[0] = '\0';


		Print();


	}

	void Playlist::Print()
	{
		LOGI("Playlist %s:", mCFile);
		LOGI("%d Tracks", mList.size());

		int i = 1;
		for(list<vector <char> >::iterator it = mList.begin(); it != mList.end(); ++it)
		{
			LOGI("%d %s", i, &(*it)[0]);
			i++;
		}
		LOGI("End of Playlist");
	}

	void Playlist::updateSound(){
		if(strcmp(&(*mCurTrackIt)[0], mSound->GetPath()) != 0)
		{
			delete mSound;

			mSound = new Sound(&(*mCurTrackIt)[0]);
			mSound->Load();
		}
	}

	bool Playlist::Next()
	{
		if(mNFile[0] != '\0')
			useNewPlist();

		switch(mPlayMode)
		{

		case FORWARD:
			mCurTrackIt++;

			if(mCurTrackIt == mList.end())
			{

				if(mLoop)
				{
					mCurTrackIt = mList.begin();
				}
				else
				{
					mCurTrackIt--;
					return false;
				}
			}

			break;

		case BACKWARD:
			if(mCurTrackIt == mList.begin())
			{
				if(mLoop)
				{
					mCurTrackIt = mList.end();
				}
				else
				{
					return false;
				}
			}

			mCurTrackIt--;
			break;
		case SHUFFLE:
			mCurTrackIt = mList.begin();
			int n;
			n = Core::Random::Int(0, mList.size() - 1);
			LOGI("SHUFFLED FOR %d", n);
			for(int i = 0; i < n; i++)
			{
				mCurTrackIt++;
			}
			break;

		default:
			LOGE("Bad enum value in playlist PlayMode");
		}


		updateSound();

		return true;
	}



	Sound* Playlist::GetSound()
	{
		return mSound;
	}

	void Playlist::setPlayMode(PlayMode p){
		mPlayMode = p;
	}
}
