#include <wx/dateevt.h>
#include <wx/timectrl.h>
#include <wx/datectrl.h>
#include "graphdialog.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "options.h"


CGraphDialog::CGraphDialog(wxWindow *parent, CSymbol *ptr)
	:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Sizer->Add(GetTopPanel(this),0,wxALL|wxEXPAND,2);
	Sizer->Add(GetGraphPanel(this),1,wxALL|wxEXPAND,2);
	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,2);
	SetSizer(Sizer);
	Fit();
	Center();
}

CGraphDialog::~CGraphDialog()
{
	
}

wxPanel *CGraphDialog::GetTopPanel(wxWindow *parent)
{
	wxPanel *Panel = new wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(Sizer);
	wxFont font;
	font.SetPointSize(12);
	font.SetWeight(wxBOLD);
	m_Title = new wxStaticText(Panel,wxID_ANY,wxEmptyString);
	m_Title->SetFont(font);
	Sizer->Add(m_Title,0,wxALL|wxEXPAND,2);
	
	//m_Min = new wxStaticText(Panel,wxID_ANY,wxEmptyString);
	//Sizer->Add(m_Min,0,wxALL|wxEXPAND,5);
	
	return Panel;
}


wxPanel *CGraphDialog::GetGraphPanel(wxWindow *parent)
{
	wxPanel *Panel = new wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(Sizer);
	
	m_Graph = new CGraph(Panel);
	m_Graph->SetMinSize(wxSize(600,250));
	Sizer->Add(m_Graph,1,wxALL|wxEXPAND,5);

	return Panel;
}

wxPanel *CGraphDialog::GetButtonPanel(wxWindow *parent)
{

	wxPanel *Panel = new wxPanel(this);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);

	wxStaticText *LabelProductInfo = new wxStaticText(Panel,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	Sizer->Add(LabelProductInfo,0,wxALL,5);
	Sizer->AddStretchSpacer(1);

	wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CLOSE));
	Sizer->AddStretchSpacer();
	Sizer->Add(ButtonClose,0,wxALL,2);
	
	return Panel;
}

CGraph *CGraphDialog::GetGraph()
{
	return m_Graph;
}

void CGraphDialog::SetTitle(wxString v)
{
	m_Title->SetLabel(v);
}