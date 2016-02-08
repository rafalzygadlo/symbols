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

void CList::_Render()
{
	for(size_t i = 0; i < size();i++)
	{
		CListItem *ptr = (CListItem*)Item(i);
		ptr->Render();
	}

}