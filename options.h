#ifndef __OPTIONS
#define __OPTIONS
#include <wx/wx.h>

#define DEFAULT_FG_COLOR wxColor(230,230,230)
#define DEFAULT_BG_COLOR wxColor(50,50,50)

wxColor GetBGColor();
wxColor GetFGColor();

void SetFGColor(wxColor v);
void SetBGColor(wxColor v);

#endif
