#include "conf.h"
#include "right.h"
#include "tools.h"
#include "db.h"

int nvRightId[][2] =
{
	{MODULE_USER_GROUP,ACTION_RIGHT},
	{MODULE_USER_GROUP,ACTION_NEW},
	{MODULE_USER_GROUP,ACTION_EDIT},
	
	{MODULE_USER,ACTION_NEW},
	{MODULE_USER,ACTION_EDIT},
	{MODULE_USER,ACTION_DELETE},

	{MODULE_AREA,ACTION_NEW},
	{MODULE_AREA,ACTION_EDIT},
	{MODULE_AREA,ACTION_DELETE},

	{MODULE_SEAWAY,ACTION_NEW},
	{MODULE_SEAWAY,ACTION_EDIT},
	{MODULE_SEAWAY,ACTION_DELETE},

	{MODULE_SYMBOL_TYPE,ACTION_NEW},
	{MODULE_SYMBOL_TYPE,ACTION_EDIT},
	{MODULE_SYMBOL_TYPE,ACTION_DELETE},

	{MODULE_ITEM,ACTION_NEW},
	{MODULE_ITEM,ACTION_EDIT},
	{MODULE_ITEM,ACTION_DELETE},

	{MODULE_PICTURE,ACTION_NEW},
	{MODULE_PICTURE,ACTION_EDIT},
	{MODULE_PICTURE,ACTION_DELETE},
	
	{MODULE_SYMBOL,ACTION_NEW},
	{MODULE_SYMBOL,ACTION_EDIT},
	{MODULE_SYMBOL,ACTION_DELETE},
	{MODULE_SYMBOL,ACTION_MANAGEMENT},
	{MODULE_SYMBOL,ACTION_ADD_TO_GROUP},
	
	{MODULE_SYMBOL_GROUP,ACTION_NEW},
	{MODULE_SYMBOL_GROUP,ACTION_EDIT},
	{MODULE_SYMBOL_GROUP,ACTION_DELETE},

	{MODULE_CHARACTERISTIC,ACTION_NEW},
	{MODULE_CHARACTERISTIC,ACTION_EDIT},
	{MODULE_CHARACTERISTIC,ACTION_DELETE},
	
	{MODULE_BASE_STATION,ACTION_NEW},
	{MODULE_BASE_STATION,ACTION_EDIT},
	{MODULE_BASE_STATION,ACTION_DELETE},
	{-1,-1}

};

SModule nvModule[] =
{	
	{MODULE_USER_GROUP,GetMsg(MSG_USER_GROUP)},
	{MODULE_USER,GetMsg(MSG_USER)},
	{MODULE_AREA,GetMsg(MSG_AREA)},
	{MODULE_SEAWAY,GetMsg(MSG_SEAWAY)},
	{MODULE_SYMBOL_TYPE,GetMsg(MSG_SYMBOL_TYPE)},
	{MODULE_ITEM,GetMsg(MSG_ITEMS)},
	{MODULE_PICTURE,GetMsg(MSG_PICTURE)},
	{MODULE_SYMBOL,GetMsg(MSG_SYMBOL)},
	{MODULE_SYMBOL_GROUP,GetMsg(MSG_SYMBOL_GROUP)},
	{MODULE_CHARACTERISTIC,GetMsg(MSG_CHARACTERISTIC)},
	{MODULE_BASE_STATION,GetMsg(MSG_BASE_STATION)},
	{MODULE_SBMS,GetMsg(MSG_DRIVER)},
	{MODULE_OPTION,GetMsg(MSG_OPTIONS)},
	{-1,L"-1"}
};

SAction nvAction[] =
{
	{ACTION_NEW,GetMsg(MSG_NEW)},
	{ACTION_EDIT,GetMsg(MSG_EDIT)},
	{ACTION_DELETE,GetMsg(MSG_DELETE)},
//	{ACTION_RIGHT,GetMsg(MSG_RIGHT)},
	{ACTION_MANAGEMENT,GetMsg(MSG_MANAGEMENT)},
	{ACTION_ADD_TO_GROUP,GetMsg(MSG_ADD_TO_GROUP)},
	{-1,L"-1"}
};

const wchar_t *CRight::GetModuleName(int id)
{
	return nvModule[id].name;
}

int CRight::GetModuleId(int id)
{
	return nvModule[id].id;
}

bool CRight::IsBuiltIn(void *db, int uid)
{
	// czy wbudowany user
	wxString query = wxString::Format(_("SELECT * FROM `%s` WHERE built_in = '1' AND id = '%d'"),TABLE_USER,uid);
	if(!my_query(db,query))
		return false;
	
	void *result = db_result(db);
	int count = db_num_rows(result);
	db_free_result(result);
	if(count == 1)
		return true;

	return false;
}

//uprawnienia
bool CRight::CheckRight(void *db,int id_module, int id_action, int uid)
{
	
	if(IsBuiltIn(db,uid))
		return true;

	wxString query = wxString::Format(_("SELECT * FROM `%s` WHERE id_module = '%d' AND id_action = '%d'"),TABLE_RIGHT,id_module,id_action);
	if(!my_query(db,query))
		return false;
	
	void *result = db_result(db);
	int count = db_num_rows(result);

	if(count == 0)
	{
		db_free_result(result);
		wxString query = wxString::Format(_("INSERT INTO `%s` SET id_module = '%d' AND id_action ='%d'"),TABLE_RIGHT,id_module,id_action);
		my_query(db,query);
		return false;
		// nie ma rekordu z uprawnieniem
	}
	
	char **row  = (char**)db_fetch_row(result);
	query = wxString::Format(_("SELECT * FROM `%s`, `%s` WHERE %s.id_group = %s.id_group AND %s.id_user = '%d' AND %s.id_right='%s'"),TABLE_USER_TO_GROUP, TABLE_USER_GROUP_RIGHT,TABLE_USER_TO_GROUP,TABLE_USER_GROUP_RIGHT,TABLE_USER_TO_GROUP,uid,TABLE_USER_GROUP_RIGHT,row[FI_RIGHT_ID]);
	db_free_result(result);
	
	if(!my_query(db,query))
	{
		DBClose(db);
		return false;
	}

	result = db_result(db);
	count = db_num_rows(result);
	db_free_result(result);
	DBClose(db);
	
	bool res = false;
	if(count > 0)
		res = true;
	
	return res;
}
