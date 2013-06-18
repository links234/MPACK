#include "Playlist.hpp"

namespace Core
{
	Playlist::Playlist(const char* pPath) :
        mResource(pPath),
        mList(NULL), mLength(0), mCurTrack(0)
    {
		Asset lAsset(pPath);
		lAsset.Open();
		int size = lAsset.GetLength();
		char *plist;
		plist = new char[size];


		lAsset.Read(plist, size);

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



		mNumTracks = num;

		mList = new char*[mNumTracks];
		for(int i = 0; i < mNumTracks; i++)
		{
			mList[i] = new char[maxLen];
		}


		int t = 0, p = 0;
		num = 0;
		for(int i = 0; plist[i] != '\0' && num < mNumTracks; i++)
		{

			if(plist[i] == '\n')
			{
				mList[t][p] = '\0';
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
				mList[t][p] = plist[i];
				p++;
			}
		}

		mSound = new Sound(mList[0]);
		mSound->Load();

		delete [] plist;

		/*
		LOGI("Playlist:");
		LOGI("%d Tracks", mNumTracks);

		for(int i = 0; i < mNumTracks; i++)
		{
			LOGI("%d %s", i, mList[i]);
		}
		LOGI("End of Playlist");
		*/

    }

	Playlist::~Playlist()
	{
		delete mSound;

		for(int i = 0; i < mNumTracks; i++)
		{
			delete[] mList[i];
		}

		delete[] mList;
	}

	Sound* Playlist::Next()
	{

		mCurTrack++;

		mCurTrack %= mNumTracks;

		if(strcmp(mList[mCurTrack], mSound->GetPath()) != 0)
		{
			delete mSound;

			mSound = new Sound(mList[mCurTrack]);
			mSound->Load();
		}

		return mSound;
	}

	Sound* Playlist::Prev()
	{

		mCurTrack--;

		mCurTrack = (mCurTrack + mNumTracks) % mNumTracks;

		if(strcmp(mList[mCurTrack], mSound->GetPath()) != 0)
		{
			delete mSound;

			mSound = new Sound(mList[mCurTrack]);
			mSound->Load();
		}

		return mSound;
	}

	Sound* Playlist::GetSound()
	{
		return mSound;
	}

	const char* Playlist::GetPath()
	{
		return mResource.GetPath();
	}
}
