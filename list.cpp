#include "list.h"
#include "conf.h"
#include "tools.h"
#include "db.h"

CList::CList()
{
}

CList::~CList()
{
}

int CList::_Length()
{
	return size();
}

void *CList::_Get(int id)
{
	return Item(id);
}

void CList::_Clear()
{
	for(int i = 0; i < size();i++)
	{
		CListItem *ListItem = (CListItem*)Item(i);
		delete ListItem;
	}

	Clear();
}


void CList::_SetExists(bool v)
{
	for(size_t i = 0; i < size();i++)
	{
		CListItem *ptr = (CListItem*)Item(i);
		ptr->SetExists(v);
	}
}

CListItem *CList::_Exists(int id)
{
	for(size_t i = 0; i < size(); i++)
	{
		CListItem *ptr = (CListItem*)Item(i);
		if(id == ptr->GetId())
			return ptr;
	}

	return NULL;
}

CListItem *CList::_Exists(int id, int type)
{
	for(size_t i = 0; i < size(); i++)
	{
		CListItem *ptr = (CListItem*)Item(i);
		if(id == ptr->GetId() && type == ptr->GetType())
			return ptr;
	}

	return NULL;
}


void CList::_Remove()
{

	for(size_t i = 0; i < size(); i++)
	{
		CListItem *ptr = (CListItem*)Item(i);
		
		if(!ptr->GetExists())
		{
			Remove(ptr);
			delete ptr;
			i = 0;
		}
	}

}

void CList::_Mouse(int x, int y, bool lmb, bool mmb, bool rmb)
{
	for(size_t i = 0; i < size();i++)
	{
		CListItem *ptr = (CListItem*)Item(i);
		ptr->Mouse(x,y,lmb,mmb,rmb);
	}
}

void CList::_Render()
{
	for(size_t i = 0; i < size();i++)
	{
		CListItem *ptr = (CListItem*)Item(i);
		ptr->Render();
	}

}