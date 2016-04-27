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
	
	void UpdateSBMSCommand(int id,wxString cmd);
	void SetAnswer(int id_command, int mmsi, int id_base_station);
	void SetGroupAnswer(int cmd_id, int id_group);

public:
	
	CCommand();
	~CCommand();
	
	void ClearAll(int id_sbms);
	void DeactivateCommand(int id, int type);
	void SetGroupCommand(int cmd_id, wxString code, int id_group, bool on);
	void SetCommand(int cmd_id, int id_sbms, int mmsi,int SBMSID, int id_base_station, int param1);

};

#endif