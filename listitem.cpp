#include "listitem.h"
#include "conf.h"
#include "tools.h"
#include "db.h"


CListItem::CListItem()
{
	m_Exists = false;
	m_Id = 0;
}

CListItem::~CListItem()
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

//GET
int CListItem::GetId()
{
	return m_Id;
}

bool CListItem::GetExists()
{
	return m_Exists;
}