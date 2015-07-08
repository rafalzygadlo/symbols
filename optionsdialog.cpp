#include <wx/statline.h>
#include <wx/notebook.h>
#include "options.h"
#include "optionsdialog.h"
#include "conf.h"
#include "tools.h"
#include "db.h"


BEGIN_EVENT_TABLE(COptionsDialog,wxDialog)
	EVT_COLOURPICKER_CHANGED(wxID_ANY,OnColorPicker)
	EVT_SLIDER(wxID_ANY,OnAlpha)
END_EVENT_TABLE()

COptionsDialog::COptionsDialog()
	:wxDialog(NULL,wxID_ANY,wxEmptyString)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(Sizer);		
	
	wxNotebook *m_Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME);
	m_Notebook->AddPage(GetColorPanel(m_Notebook),GetMsg(MSG_COLOR));
	Sizer->Add(m_Notebook,1,wxALL|wxEXPAND,0);		
	
	wxStaticLine *line = new wxStaticLine(this,wxID_ANY);
	Sizer->Add(line,0,wxALL|wxEXPAND,0);
	
	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,10);
	
	SetSizer(Sizer);
	Fit();
	Center();
}

COptionsDialog::~COptionsDialog()
{
	
}

wxPanel *COptionsDialog::GetColorPanel(wxWindow *Parent)
{
	wxColor color;
	
	wxPanel *Panel = new wxPanel(Parent);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBoxSizer *Box = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_SYMBOL_COLORS));
	Sizer->Add(Box,0,wxALL|wxEXPAND,5);
	Panel->SetSizer(Sizer);	
		
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(3);
	Box->Add(FlexSizer,1,wxALL|wxEXPAND,5);

	//NORMAL COLOR
	wxStaticText *TextSymbolNormalColor = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SYMBOL_COLOR_NORMAL),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextSymbolNormalColor,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	m_SymbolNormalColor = new wxColourPickerCtrl(Panel,ID_SYMBOL_NORMAL_COLOR,*wxBLACK,wxDefaultPosition,wxDefaultSize);
	color.Set(GetColor(SYMBOL_NORMAL_COLOR).R,GetColor(SYMBOL_NORMAL_COLOR).G,GetColor(SYMBOL_NORMAL_COLOR).B,GetColor(SYMBOL_NORMAL_COLOR).A);
	m_SymbolNormalColor->SetColour(color);
	FlexSizer->Add(m_SymbolNormalColor,0,wxALL,2);
	
	m_SymbolNormalColorAlpha = new wxSlider(Panel,ID_SYMBOL_NORMAL_ALPHA,0,0,1,wxDefaultPosition,wxDefaultSize);
	m_SymbolNormalColorAlpha->SetMin(0);
	m_SymbolNormalColorAlpha->SetMax(255);
	m_SymbolNormalColorAlpha->SetValue(GetAlpha(SYMBOL_NORMAL_COLOR));
	FlexSizer->Add(m_SymbolNormalColorAlpha,0,wxALL,2);
	
	//NO MONITOR
	wxStaticText *TextSymbolNoMonitorColor = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SYMBOL_NO_MONITOR),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextSymbolNoMonitorColor,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	m_SymbolNoMonitorColor = new wxColourPickerCtrl(Panel,ID_SYMBOL_NO_MONITOR_COLOR,*wxBLACK,wxDefaultPosition,wxDefaultSize);
	color.Set(GetColor(SYMBOL_NO_MONITOR_COLOR).R,GetColor(SYMBOL_NO_MONITOR_COLOR).G,GetColor(SYMBOL_NO_MONITOR_COLOR).B,GetColor(SYMBOL_NO_MONITOR_COLOR).A);
	m_SymbolNoMonitorColor->SetColour(color);
	FlexSizer->Add(m_SymbolNoMonitorColor,0,wxALL,2);
	
	m_SymbolNoMonitorColorAlpha = new wxSlider(Panel,ID_SYMBOL_NO_MONITOR_ALPHA,0,0,1,wxDefaultPosition,wxDefaultSize);
	m_SymbolNoMonitorColorAlpha->SetMin(0);
	m_SymbolNoMonitorColorAlpha->SetMax(255);
	m_SymbolNoMonitorColorAlpha->SetValue(GetAlpha(SYMBOL_NO_MONITOR_COLOR));
	FlexSizer->Add(m_SymbolNoMonitorColorAlpha,0,wxALL,2);
	
	//ERROR
	wxStaticText *TextSymbolErrorColor = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SYMBOL_ERROR_COLOR),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextSymbolErrorColor,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	m_SymbolErrorColor = new wxColourPickerCtrl(Panel,ID_SYMBOL_ERROR_COLOR,*wxBLACK,wxDefaultPosition,wxDefaultSize);
	color.Set(GetColor(SYMBOL_ERROR_COLOR).R,GetColor(SYMBOL_ERROR_COLOR).G,GetColor(SYMBOL_ERROR_COLOR).B,GetColor(SYMBOL_ERROR_COLOR).A);
	m_SymbolErrorColor->SetColour(color);
	FlexSizer->Add(m_SymbolErrorColor,0,wxALL,2);
	
	m_SymbolErrorAlpha = new wxSlider(Panel,ID_SYMBOL_ERROR_ALPHA,0,0,1,wxDefaultPosition,wxDefaultSize);
	m_SymbolErrorAlpha->SetMin(0);
	m_SymbolErrorAlpha->SetMax(255);
	m_SymbolErrorAlpha->SetValue(GetAlpha(SYMBOL_ERROR_COLOR));
	FlexSizer->Add(m_SymbolErrorAlpha,0,wxALL,2);

	//LIGHT ON
	wxStaticText *TextSymbolLightOn = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SYMBOL_LIGHT_ON),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextSymbolLightOn,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	m_SymbolLightOn = new wxColourPickerCtrl(Panel,ID_SYMBOL_LIGHT_ON_COLOR,*wxBLACK,wxDefaultPosition,wxDefaultSize);
	color.Set(GetColor(SYMBOL_LIGHT_ON_COLOR).R,GetColor(SYMBOL_LIGHT_ON_COLOR).G,GetColor(SYMBOL_LIGHT_ON_COLOR).B,GetColor(SYMBOL_LIGHT_ON_COLOR).A);
	m_SymbolLightOn->SetColour(color);
	FlexSizer->Add(m_SymbolLightOn,0,wxALL,2);
	
	m_SymbolLightOnAlpha = new wxSlider(Panel,ID_SYMBOL_LIGHT_ON_ALPHA,0,0,1,wxDefaultPosition,wxDefaultSize);
	m_SymbolLightOnAlpha->SetMin(0);
	m_SymbolLightOnAlpha->SetMax(255);
	m_SymbolLightOnAlpha->SetValue(GetAlpha(SYMBOL_LIGHT_ON_COLOR));
	FlexSizer->Add(m_SymbolLightOnAlpha,0,wxALL,2);


	return Panel;
	
}


wxPanel *COptionsDialog::GetButtonPanel(wxWindow *parent)
{

	wxPanel *Panel = new wxPanel(this);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);	
	wxButton *ButtonOk = new wxButton(Panel,wxID_OK,GetMsg(MSG_CLOSE));
	//wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CANCEL));
	Sizer->AddStretchSpacer();
	Sizer->Add(ButtonOk,0,wxALL,2);
	//Sizer->Add(ButtonClose,0,wxALL,2);
	
	return Panel;
}

void COptionsDialog::OnColorPicker(wxColourPickerEvent &event)
{
	nvRGBA color;
	wxColor cl = event.GetColour();
		
	color.R = cl.Red();
	color.G = cl.Green();
	color.B = cl.Blue();

	switch(event.GetId())
	{
		case ID_SYMBOL_NORMAL_COLOR:		color.A = GetColor(SYMBOL_NORMAL_COLOR).A;		SetColor(SYMBOL_NORMAL_COLOR,color);		break;	
		case ID_SYMBOL_NO_MONITOR_COLOR:	color.A = GetColor(SYMBOL_NO_MONITOR_COLOR).A;	SetColor(SYMBOL_NO_MONITOR_COLOR,color);	break;
		case ID_SYMBOL_ERROR_COLOR:			color.A = GetColor(SYMBOL_ERROR_COLOR).A;		SetColor(SYMBOL_ERROR_COLOR,color);			break;
		case ID_SYMBOL_LIGHT_ON_COLOR:		color.A = GetColor(SYMBOL_LIGHT_ON_COLOR).A;	SetColor(SYMBOL_LIGHT_ON_COLOR,color);		break;
	}

	//Signal();
		
}

void COptionsDialog::OnAlpha(wxCommandEvent &event)
{
	switch(event.GetId())
	{
		case ID_SYMBOL_NORMAL_ALPHA:		SetAlpha(SYMBOL_NORMAL_COLOR,event.GetInt());		break;
		case ID_SYMBOL_NO_MONITOR_ALPHA:	SetAlpha(SYMBOL_NO_MONITOR_COLOR,event.GetInt());	break;
		case ID_SYMBOL_ERROR_ALPHA:			SetAlpha(SYMBOL_ERROR_COLOR,event.GetInt());		break;
		case ID_SYMBOL_LIGHT_ON_ALPHA:		SetAlpha(SYMBOL_LIGHT_ON_COLOR,event.GetInt());		break;
	}

	///Signal();
	
}
