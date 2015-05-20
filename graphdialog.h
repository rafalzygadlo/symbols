#ifndef __GRAPH_DIALOG_H
#define __GRAPH_DIALOG_H

#include <wx/wx.h>
#include <wx/hyperlink.h>
#include "conf.h"
#include "symbol.h"
#include "graph.h"

class CGraphDialog: public wxDialog
{
	CGraph *m_Graph;
	wxPanel *GetButtonPanel(wxWindow *parent);

public:

	CGraphDialog(wxWindow *parent,CSymbol *ptr);
	~CGraphDialog();
	CGraph *GetGraph();

};


#endif