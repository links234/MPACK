#ifndef MPACK_INDEXEDSKIPLISTIMPLEMENTATION_HPP
#define MPACK_INDEXEDSKIPLISTIMPLEMENTATION_HPP

#include <cstring>

#include "Random.hpp"

using namespace MPACK::Core;

namespace MPACK
{
	namespace Algorithm
	{
		template<class T> IndexedSkipList<T>::IndexedSkipList(int maxHeight)
			: m_size(0), m_maxHeight(maxHeight)
		{
			head=new IndexedSkipListNode<T>(static_cast<T>(0),m_maxHeight);
		}

		template<class T> IndexedSkipList<T>::~IndexedSkipList()
		{
			while(head->link[0].next)
			{
				IndexedSkipListNode<T> *temp=head;
				head=head->link[0].next;
				delete temp;
			}
		}

		template<class T> int IndexedSkipList<T>::Size() const
		{
			return m_size;
		}

		template<class T> bool IndexedSkipList<T>::Empty() const
		{
			return m_size==0;
		}

		template<class T> void IndexedSkipList<T>::Insert(int pos, T value)
		{
			if(pos>m_size || pos<0)
			{
				return;
			}

			int insertPos=pos+1;

			int height=1;
			while(height<m_maxHeight && Random::FlipCoin())
			{
				++height;
			}
			IndexedSkipListNode<T> *newNode=new IndexedSkipListNode<T>(value,height);

			int *chainLength=new int[m_maxHeight+1];
			memset(chainLength,0,sizeof(int)*(m_maxHeight+1));
			IndexedSkipListNode<T> *pointer=head;
			for(int level=m_maxHeight-1;level>=height;--level)
			{
				for(;pointer->link[level].width<=pos && pointer->link[level].next;pos-=pointer->link[level].width,pointer=pointer->link[level].next)
				{
					chainLength[level]+=pointer->link[level].width;
				}
				chainLength[level]+=chainLength[level+1];

				++pointer->link[level].width;
			}

			for(int level=height-1;level>=0;--level)
			{
				for(;pointer->link[level].width<=pos && pointer->link[level].next;pos-=pointer->link[level].width,pointer=pointer->link[level].next)
				{
					chainLength[level]+=pointer->link[level].width;
				}
				chainLength[level]+=chainLength[level+1];

				int unbrokenLinkLength=pointer->link[level].width+1;

				pointer->link[level].width=insertPos-chainLength[level];
				newNode->link[level].width=unbrokenLinkLength-pointer->link[level].width;

				newNode->link[level].next=pointer->link[level].next;
				pointer->link[level].next=newNode;
			}

			++m_size;
		}

		template<class T> void IndexedSkipList<T>::Erase(int pos)
		{
			if(pos>=m_size || pos<0)
			{
				return;
			}
			int tmpPos=pos;

			++pos;
			IndexedSkipListNode<T> *pointer=head;
			for(int level=m_maxHeight-1;level>=0;--level)
			{
				for(;pointer->link[level].width<=pos && pointer->link[level].next;pos-=pointer->link[level].width,pointer=pointer->link[level].next);
			}

			int height=pointer->m_height;

			pointer=head;
			pos=tmpPos;
			for(int level=m_maxHeight-1;level>=height;--level)
			{
				for(;pointer->link[level].width<=pos && pointer->link[level].next;pos-=pointer->link[level].width,pointer=pointer->link[level].next);
				--pointer->link[level].width;
			}

			for(int level=height-1;level>=1;--level)
			{
				for(;pointer->link[level].width<=pos && pointer->link[level].next;pos-=pointer->link[level].width,pointer=pointer->link[level].next);
				if(pointer->link[level].next)
				{
					pointer->link[level].width+=pointer->link[level].next->link[level].width-1;
					pointer->link[level].next=pointer->link[level].next->link[level].next;
				}
				else
				{
					--pointer->link[level].width;
					pointer->link[level].next=NULL;
				}
			}

			for(;pointer->link[0].width<=pos && pointer->link[0].next;pos-=pointer->link[0].width,pointer=pointer->link[0].next);
			IndexedSkipListNode<T> *temp=pointer->link[0].next;
			if(pointer->link[0].next)
			{
				pointer->link[0].width+=pointer->link[0].next->link[0].width-1;
				pointer->link[0].next=pointer->link[0].next->link[0].next;
			}
			else
			{
				--pointer->link[0].width;
				pointer->link[0].next=NULL;
			}
			delete temp;

			--m_size;
		}

		template<class T> T IndexedSkipList<T>::At(int pos) const
		{
			if(pos>=m_size || pos<0)
			{
				return static_cast<T>(0);
			}

			++pos;
			IndexedSkipListNode<T> *pointer=head;
			for(int level=m_maxHeight-1;level>=0;--level)
			{
				for(;pointer->link[level].width<=pos && pointer->link[level].next;pos-=pointer->link[level].width,pointer=pointer->link[level].next);
			}

			return pointer->m_data;
		}
	}
}

#endif
