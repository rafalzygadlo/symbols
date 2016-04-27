#ifndef __GRAPH_DIALOG
#define __GRAPH_DIALOG

#include <wx/wx.h>
#include <wx/hyperlink.h>
#include "conf.h"
#include "symbol.h"
#include "graph.h"

class CSymbol;
class CGraphDialog: public wxDialog
{
	CGraph *m_Graph;
	wxStaticText *m_Title;
	
	void OnClose(wxCloseEvent &event);
	void OnButtonClose(wxCommandEvent &event);
	wxPanel *GetButtonPanel(wxWindow *parent);
	wxPanel *GetGraphPanel(wxWindow *parent);
	wxPanel *GetTopPanel(wxWindow *parent);

public:

	CGraphDialog(wxWindow *parent);
	~CGraphDialog();
	CGraph *GetGraph();
	void _SetTitle(wxString v);
	void SetMin(wxString v);
		
};


#endif