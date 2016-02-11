#ifndef __LIST
#define __LIST

#include <wx/wx.h>
#include "listitem.h"

class CList: public wxArrayPtrVoid
{
	void *m_DB;

public:

	CList();
	virtual ~CList();
	
	void _SetExists(bool v);
	void _Clear();
	void _Remove();
	void _Render();
	void _Mouse(int x, int y, bool lmb, bool mmb, bool rmb);
	CListItem *_Exists(int id);

};

#endif