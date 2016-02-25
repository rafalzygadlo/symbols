#ifndef __LISTITEM
#define __LISTITEM


class CListItem
{
	bool m_Exists;
	int m_Id;
	int m_Type;

public:

	CListItem();
	virtual ~CListItem();
	
	//SET
	void SetExists(bool v);
	void SetType(int v);
	void SetId(int v);
	
	//GET
	int GetId();
	int GetType();
	bool GetExists();
	

	virtual void Render();
	virtual void Mouse(int x, int y, bool lmb, bool mmb, bool rmb);
		
};

#endif