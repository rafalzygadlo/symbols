#include "listitem.h"
#include "conf.h"
#include "tools.h"
#include "db.h"


CListItem::CListItem()
{
	m_Exists = false;
	m_Id = 0;
	m_Type = 0;
}

CListItem::~CListItem()
{


}

void CListItem::Mouse(int x, int y, bool lmb, bool mmb, bool rmb)
{

}

void CListItem::Render()
{

}

//SET
void CListItem::SetExists(bool v)
{
	m_Exists = v;
}

void CListItem::SetId(int v)
{
	m_Id = v;
}

void CListItem::SetType(int v)
{
	m_Type = v;
}

//GET
int CListItem::GetId()
{
	return m_Id;
}

bool CListItem::GetExists()
{
	return m_Exists;
}

int CListItem::GetType()
{
	return m_Type;
}