#ifndef __COMMAND
#define __COMMAND

#include <wx/wx.h>
#include <wx/htmllbox.h>
#include "display.h"
#include "dll.h"
#include "command.h"

class CCommand
{
	
	int SetCommand(int id_sbms,int mmsi,int SBMSID,int id_base_station, int id_command, wxString cmd);
	int SetGroupCommand(int id_sbms,int mmsi,int SBMSID,int id_base_station, int id_command, wxString cmd);
	
	wxArrayInt GetBaseStationIdsInGroup(int id_group);	//do których stacji bazowych należą sbmsy z grupy
	void UpdateSBMSCommand(int id,wxString cmd);
	void SetAnswer(int id_command, int id_base_station, int mmsi , int SBMSID);
	void SetGroupAnswer(int cmd_id, int id_group, int id_base_station);

public:
	
	CCommand();
	~CCommand();
	
	void ClearAll(int id_sbms);
	void DeactivateCommand(int id, int type);
	void SetGroupCommand(int cmd_id, wxString code, int id_group, bool on);
	void SetCommand(int cmd_id, int id_sbms, int mmsi,int SBMSID, int id_base_station, int param1);

};

#endif