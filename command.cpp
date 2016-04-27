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

void CCommand::SetAnswer(int id_command, int mmsi, int id_base_station)
{
	void *db = DBConnect();
    if (db == NULL)
        return;
		
	wxString sql = wxString::Format(_("SELECT id_sbms,mmsi FROM `%s`,`%s` WHERE id_symbol=`%s`.id AND mmsi='%d'"),TABLE_SBMS,TABLE_SYMBOL,TABLE_SYMBOL,mmsi);
		
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
        
		sql = wxString::Format(_("INSERT INTO `%s` SET id_sbms_command='%d', mmsi='%d'"), TABLE_SBMS_COMMAND_ANSWER, id_command,mmsi);
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
	
	SetAnswer(id,mmsi,id_base_station);
}

//..................................................................................

// grupowe komendy
void CCommand::SetGroupCommand(int cmd_id, wxString code, int id_group, bool on)
{
	const char *cmd = GetCommand(cmd_id);
	wxString _cmd = wxString::Format(_(cmd),code,on);
	int id = SetGroupCommand(0,0,0,0,cmd_id,_cmd);
	
	SetGroupAnswer(id,id_group);
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


void CCommand::SetGroupAnswer(int id_command, int id_group)
{
	wxString sql = wxString::Format(_("SELECT id_sbms,mmsi,id_base_station,SBMSID from `%s`"),TABLE_SYMBOL_GROUP);
	sql << wxString::Format(_(" LEFT JOIN `%s` on id=id_group"),TABLE_SYMBOL_TO_GROUP);
	sql << wxString::Format(_(" LEFT JOIN `%s` on `%s`.id=`%s`.id_symbol"),TABLE_SYMBOL,TABLE_SYMBOL,TABLE_SYMBOL_TO_GROUP);
	sql << wxString::Format(_(" LEFT JOIN `%s` on `%s`.id=`%s`.id_symbol WHERE id_group='%d' AND sbms.id_symbol > 0"),TABLE_SBMS,TABLE_SYMBOL,TABLE_SBMS,id_group);
	
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
        
			sql = wxString::Format(_("INSERT INTO `%s` SET id_sbms_command='%d', mmsi='%d'"), TABLE_SBMS_COMMAND_ANSWER, id_command,mmsi);
			my_query(db, sql);
			
		}
	}
	
	db_free_result(result);
	DBClose(db);

}
