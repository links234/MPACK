#ifdef ANDROID_PLATFORM

#include "AndroidInputService.hpp"

#include <android_native_app_glue.h>
#include <cmath>

#include "InputService.hpp"

using namespace std;
using namespace MPACK::Math;
using namespace MPACK::Core;

namespace MPACK
{
	namespace Input
	{
		AndroidInputService::AndroidInputService()
		{
			LOGI("Creating InputService.");
		}

		AndroidInputService::~AndroidInputService()
		{
			LOGI("Destroying InputService.");
			for(vector<Finger*>::iterator it=m_finger.begin();it!=m_finger.end();++it)
			{
				delete *it;
			}
			m_finger.clear();
		}

		void AndroidInputService::Update()
		{
		}

		void AndroidInputService::Reset()
		{
		}

		void AndroidInputService::ClearLinks()
		{
			m_callbackFunc_FDOWN.clear();
			m_callbackFunc_FUP.clear();
			m_callbackFunc_KEYBACK.clear();
		}

		bool AndroidInputService::onTouchEvent(AInputEvent* pEvent)
		{
			size_t action = AMotionEvent_getAction(pEvent) & AMOTION_EVENT_ACTION_MASK;

			if(action==AMOTION_EVENT_ACTION_POINTER_DOWN || action==AMOTION_EVENT_ACTION_DOWN)
			{
				size_t index = (AMotionEvent_getAction(pEvent) & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
				size_t id = AMotionEvent_getPointerId(pEvent, index);

				AddFinger(id,Vector2f(AMotionEvent_getX(pEvent, index),AMotionEvent_getY(pEvent, index)));
			}
			else if(action==AMOTION_EVENT_ACTION_POINTER_UP || action==AMOTION_EVENT_ACTION_UP)
			{
				size_t index = (AMotionEvent_getAction(pEvent) & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
				size_t id = AMotionEvent_getPointerId(pEvent, index);

				DeleteFinger(id);
			}
			else if(action==AMOTION_EVENT_ACTION_MOVE)
			{
				size_t pointerCount=AMotionEvent_getPointerCount(pEvent);

				for (size_t i=0;i<pointerCount;++i)
				{
					size_t id = AMotionEvent_getPointerId(pEvent, i);

					UpdateFinger(id,Vector2f(AMotionEvent_getX(pEvent, i),AMotionEvent_getY(pEvent, i)));
				}
			}
			return true;
		}

		void AndroidInputService::UpdateFinger(GLuint id, Vector2f pos)
		{
			for(vector<Finger*>::iterator it=m_finger.begin();it!=m_finger.end();++it)
			{
				if((*it)->m_id==id)
				{
					(*it)->m_pos=pos;
					return;
				}
			}
		}

		void AndroidInputService::AddFinger(GLuint id, Vector2f pos)
		{
			Finger *pFinger=new Finger();
			pFinger->m_id=id;
			pFinger->m_flag=Finger::FREE;
			pFinger->m_pos=pos;
			m_finger.push_back(pFinger);

			for(vector<Param2PtrCallbackStruct>::iterator it=m_callbackFunc_FDOWN.begin();it!=m_callbackFunc_FDOWN.end();++it)
			{
				it->function(it->param1,(void*)(pFinger));
			}
		}

		void AndroidInputService::DeleteFinger(GLuint id)
		{
			size_t i=0;
			for(;i<m_finger.size();++i)
			{
				if(m_finger[i]->m_id==id)
				{
					break;
				}
			}

			for(vector<Param2PtrCallbackStruct>::iterator it=m_callbackFunc_FUP.begin();it!=m_callbackFunc_FUP.end();++it)
			{
				it->function(it->param1,(void*)(m_finger[i]));
			}

			delete m_finger[i];
			swap(m_finger[i],m_finger[m_finger.size()-1]);
			m_finger.pop_back();
		}

		bool AndroidInputService::onKeyBack()
		{
			for(vector<Param1PtrCallbackStruct>::iterator it=m_callbackFunc_KEYBACK.begin();it!=m_callbackFunc_KEYBACK.end();++it)
			{
				(*it).function((*it).param1);
			}
			return true;
		}

		void AndroidInputService::Link_FUP(const Param2PtrCallbackStruct &link)
		{
			m_callbackFunc_FUP.push_back(link);
		}

		void AndroidInputService::Link_FDOWN(const Param2PtrCallbackStruct &link)
		{
			m_callbackFunc_FDOWN.push_back(link);
		}

		void AndroidInputService::Link_KEYBACK(const Param1PtrCallbackStruct &link)
		{
			m_callbackFunc_KEYBACK.push_back(link);
		}

		void AndroidInputService::UnLink_FUP(const Param2PtrCallbackStruct &link)
		{
			for(vector<Param2PtrCallbackStruct>::iterator it=m_callbackFunc_FUP.begin();it!=m_callbackFunc_FUP.end();++it)
			{
				if(*it==link)
				{
					m_callbackFunc_FUP.erase(it);
					return;
				}
			}
		}

		void AndroidInputService::UnLink_FDOWN(const Param2PtrCallbackStruct &link)
		{
			for(vector<Param2PtrCallbackStruct>::iterator it=m_callbackFunc_FDOWN.begin();it!=m_callbackFunc_FDOWN.end();++it)
			{
				if(*it==link)
				{
					m_callbackFunc_FDOWN.erase(it);
					return;
				}
			}
		}

		void AndroidInputService::UnLink_KEYBACK(const Param1PtrCallbackStruct &link)
		{
			for(vector<Param1PtrCallbackStruct>::iterator it=m_callbackFunc_KEYBACK.begin();it!=m_callbackFunc_KEYBACK.end();++it)
			{
				if(*it==link)
				{
					m_callbackFunc_KEYBACK.erase(it);
					return;
				}
			}
		}
	}
}

#endif
