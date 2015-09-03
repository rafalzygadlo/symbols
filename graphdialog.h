#ifndef __GRAPH_DIALOG_H
#define __GRAPH_DIALOG_H

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
	//wxStaticText *m_Min;
	wxPanel *GetButtonPanel(wxWindow *parent);
	wxPanel *GetGraphPanel(wxWindow *parent);
	wxPanel *GetTopPanel(wxWindow *parent);

public:

	CGraphDialog(wxWindow *parent,CSymbol *ptr);
	~CGraphDialog();
	CGraph *GetGraph();
	void SetTitle(wxString v);
	void SetMin(wxString v);
	
};


#endif