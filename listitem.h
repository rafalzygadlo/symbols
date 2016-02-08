#ifndef __LISTITEM
#define __LISTITEM


class CListItem
{
	bool m_Exists;
	int m_Id;

public:

	CListItem();
	virtual ~CListItem();
	
	//SET
	void SetExists(bool v);
	void SetId(int v);
	
	//GET
	int GetId();
	bool GetExists();
	

	virtual void Render();
		
	
};

#endif