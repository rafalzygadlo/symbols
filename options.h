#ifndef __OPTIONS
#define __OPTIONS
#include <wx/wx.h>

#define DEFAULT_FG_COLOR wxColor(230,230,230)
#define DEFAULT_BG_COLOR wxColor(50,50,50)

wxColor GetBGColor();
wxColor GetFGColor();
wxString GetDBHost();
wxString GetDBUser();
wxString GetDBPassword();
wxString GetDBName();
int GetDBPort();

void SetFGColor(wxColor v);
void SetBGColor(wxColor v);
void SetDBHost(wxString v);
void SetDBUser(wxString v);
void SetDBPassword(wxString v);
void SetDBName(wxString v);
void SetDBPort(int v);

#endif
