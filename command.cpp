#include "tools.h"
#include "command.h"
#include "conf.h"
#include "db.h"
CCommand::CCommand()
{
	
}

CCommand::~CCommand()
{

}

void CCommand::ClearAll(int id_sbms)
{
	wxString sql = wxString::Format(_("UPDATE `%s` SET active='%d' WHERE id_sbms='%d'"),TABLE_SBMS_COMMAND,COMMAND_NOT_ACTIVE,id_sbms);
	void *db = DBConnect();
	my_query(db,sql);
	DBClose(db);
}

void CCommand::DeactivateCommand(int id, int type)
{
	wxString sql;

	switch(type)
	{
		case DRIVER_TYPE_SBMS:
			sql = wxString::Format(_("UPDATE `%s` SET active='%d' WHERE id='%d'"),TABLE_SBMS_COMMAND,COMMAND_NOT_ACTIVE,id);
		break;

		case DRIVER_TYPE_GE64:
			sql = wxString::Format(_("UPDATE `%s` SET active='%d' WHERE id='%d'"),TABLE_GE64_COMMAND,COMMAND_NOT_ACTIVE,id);
		break;
	}

	void *db = DBConnect();
	my_query(db,sql);
	DBClose(db);
}

// pojedyncze komendy
//..................................................................................

int CCommand::SetCommand(int id_sbms,int mmsi,int SBMSID,int id_base_station, int id_command,wxString cmd)
{
	wxString sql = wxString::Format(_("INSERT INTO `%s` SET command='%s', id_sbms='%d',mmsi='%d',SBMSID='%d',id_base_station='%d',id_command='%d',id_user='%d',active='%d',add_local_utc_time=utc_timestamp()"),TABLE_SBMS_COMMAND,cmd,id_sbms,mmsi,SBMSID,id_base_station,id_command,_GetUID(),COMMAND_ACTIVE);
	void *db = DBConnect();
	my_query(db,sql);
	int last_id = db_last_insert_id(db);
	DBClose(db);
	return last_id;
}

void CCommand::SetAnswer(int id_command, int id_base_station, int mmsi , int SBMSID)
{
	void *db = DBConnect();
    if (db == NULL)
        return;
		
	wxString sql = wxString::Format(_("SELECT id_sbms,mmsi FROM `%s`,`%s` WHERE id_symbol=`%s`.id AND mmsi='%d' AND SBMSID='%d'"),TABLE_SBMS,TABLE_SYMBOL,TABLE_SYMBOL,mmsi,SBMSID);
		
	my_query(db, sql);
    void *result = db_result(db);

	char **row = NULL;
    if (result == NULL)
    {
        DBClose(db);
        return;
    }
    
    while (row = (char**) db_fetch_row(result))
    {
        int id_sbms = atoi(row[0]);
        int mmsi = atoi(row[1]);
        
		sql = wxString::Format(_("INSERT INTO `%s` SET id_sbms_command='%d', mmsi='%d', SBMSID='%d'"), TABLE_SBMS_COMMAND_ANSWER, id_command,mmsi,SBMSID);
        my_query(db, sql);
    }
 
	db_free_result(result);
	DBClose(db);
}

void CCommand::SetCommand(int cmd_id,int id_sbms,int mmsi,int SBMSID, int id_base_station, int param1)
{
	const char *cmd = GetCommand(cmd_id);
	wxString sbmsid = wxString::Format(_("%d"),SBMSID);
	wxString _cmd = wxString::Format(_(cmd),sbmsid,param1);
	int id = SetCommand(id_sbms,mmsi,SBMSID,id_base_station,cmd_id,_cmd);
	
	SetAnswer(id,id_base_station,mmsi,SBMSID);
}

//..................................................................................

// grupowe komendy

wxArrayInt CCommand::GetBaseStationIdsInGroup(int id_group)
{
	wxArrayInt ids;
	
	wxString sql = wxString::Format(_("SELECT id_base_station FROM `symbol`, `sbms`, `symbol_to_group` WHERE `symbol`.id=`sbms`.id_symbol AND `symbol`.id=`symbol_to_group`.id_symbol AND `symbol_to_group`.id_group='%d' GROUP BY id_base_station"),id_group);
	void *db = DBConnect();
	my_query(db,sql);
		
	void *result = db_result(db);
	if(result)
	{
		char **row = NULL;
		while(row = (char**)db_fetch_row(result))
		{
			ids.Add(atoi(row[0]));		
		}
	}
	
	db_free_result(result);
	DBClose(db);

	return ids;

}

void CCommand::SetGroupCommand(int cmd_id, wxString code, int id_group, bool on)
{
	const char *cmd = GetCommand(cmd_id);
	wxString _cmd = wxString::Format(_(cmd),code,on);
	
	wxArrayInt ids = GetBaseStationIdsInGroup(id_group);
	
	for(int i = 0; i < ids.Count(); i++)
	{

		int id_base_station = ids.Item(i);
		int id = SetGroupCommand(0,0,0,id_base_station,cmd_id,_cmd);
		SetGroupAnswer(id,id_group,id_base_station);
	}
}

int CCommand::SetGroupCommand(int id_sbms,int mmsi,int SBMSID,int id_base_station, int id_command,wxString cmd)
{
	wxString sql = wxString::Format(_("INSERT INTO `%s` SET command='%s', id_sbms='%d',mmsi='%d',SBMSID='%d',id_base_station='%d',id_command='%d',id_user='%d',active='%d',add_local_utc_time=utc_timestamp()"),TABLE_SBMS_COMMAND,cmd,id_sbms,mmsi,SBMSID,id_base_station,id_command,_GetUID(),COMMAND_ACTIVE);
	void *db = DBConnect();
	my_query(db,sql);
	int last_id = db_last_insert_id(db);
	DBClose(db);
	return last_id;
}


void CCommand::SetGroupAnswer(int id_command, int id_group , int id_base_station)
{

	wxString sql = wxString::Format(_("SELECT id_sbms,mmsi,SBMSID FROM `symbol`, `sbms`, `symbol_to_group` WHERE `symbol`.id=`sbms`.id_symbol AND `symbol`.id=`symbol_to_group`.id_symbol AND `symbol_to_group`.id_group='%d' AND id_base_station='%d'"),id_group,id_base_station);
		
	void *db = DBConnect();
	my_query(db,sql);
		
	void *result = db_result(db);
	if(result)
	{
		char **row = NULL;
		while(row = (char**)db_fetch_row(result))
		{
			
			int id_sbms = atoi(row[0]);
			int mmsi = atoi(row[1]);
			int SBMSID = atoi(row[2]);
        
			sql = wxString::Format(_("INSERT INTO `%s` SET id_sbms_command='%d', mmsi='%d', SBMSID='%d'"), TABLE_SBMS_COMMAND_ANSWER, id_command,mmsi,SBMSID);
			my_query(db, sql);
			
		}
	}
	
	db_free_result(result);
	DBClose(db);

}
