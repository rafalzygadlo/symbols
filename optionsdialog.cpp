#include <wx/statline.h>
#include <wx/notebook.h>
#include "geometrytools.h"
#include "options.h"
#include "optionsdialog.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "dbconfig.h"
#include "tools.h"


BEGIN_EVENT_TABLE(COptionsDialog,wxDialog)
	EVT_COLOURPICKER_CHANGED(wxID_ANY,OnColorPicker)
	EVT_SLIDER(wxID_ANY,OnAlpha)
	EVT_SLIDER(ID_VIEW_NAME_SCALE, OnNameScale)
	EVT_SLIDER(ID_FONT_SIZE,OnFontSize)
	EVT_SLIDER(ID_SCALE_FACTOR,OnScaleFactor)
	EVT_CHECKBOX(ID_SHOW_NAMES,OnShowNames)
	EVT_TEXT(ID_RESTRICTED_AREA,OnRestrictedArea)
	EVT_TEXT(ID_LOWER_THRESHOLD,OnLowerThreshold)
	EVT_TEXT(ID_UPPER_THRESHOLD,OnUpperThreshold)
	EVT_TEXT(ID_OFF_POSITION_AREA,OnOffPositionArea)
	EVT_TEXT(ID_SUN_LON,OnLon)
	EVT_TEXT(ID_SUN_LAT,OnLat)
	EVT_TEXT(ID_REPORT_TIMEOUT,OnReportTimeout)
	EVT_RADIOBUTTON(ID_GPS,OnPositionFromGps)
	EVT_RADIOBUTTON(ID_SYMBOL,OnPositionFromSymbol)
	EVT_BUTTON(ID_DB_CONFIG,OnDbConfig)
END_EVENT_TABLE()

COptionsDialog::COptionsDialog()
	:wxDialog(NULL,wxID_ANY,wxEmptyString)
{
	m_DegreeFormat = DEFAULT_DEGREE_FORMAT;
	m_LonValid = false;
	m_LatValid = false;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(Sizer);		
	
	wxNotebook *m_Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME);
	m_Notebook->AddPage(GetPage1(m_Notebook),GetMsg(MSG_SYMBOL));
	m_Notebook->AddPage(GetPage2(m_Notebook),GetMsg(MSG_GLOBAL_OPTIONS));
	
	Sizer->Add(m_Notebook,1,wxALL|wxEXPAND,0);		
	
	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,10);
	
	SetSizer(Sizer);
	Fit();
	Center();
}

COptionsDialog::~COptionsDialog()
{
	
}

wxPanel *COptionsDialog::GetPage1(wxWindow *Parent)
{
	wxPanel *Panel = new wxPanel(Parent);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(Sizer);
	
	Sizer->Add(GetPositionFromPanel(Panel),0,wxALL|wxEXPAND,0);
	Sizer->Add(GetFontPanel(Panel),0,wxALL|wxEXPAND,0);
	Sizer->Add(GetColorPanel(Panel),0,wxALL|wxEXPAND,0);
	Sizer->Add(GetOtherPanel(Panel),0,wxALL|wxEXPAND,0);
	
	return Panel;
}

wxPanel *COptionsDialog::GetPage2(wxWindow *Parent)
{
	wxPanel *Panel = new wxPanel(Parent);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(Sizer);
	
	//Sizer->Add(GetFontPanel(Panel),0,wxALL|wxEXPAND,0);
	//Sizer->Add(GetColorPanel(Panel),0,wxALL|wxEXPAND,0);
	Sizer->Add(GetGlobalThresholdPanel(Panel),0,wxALL|wxEXPAND,0);
	Sizer->Add(GetGlobalSunPanel(Panel),0,wxALL|wxEXPAND,0);
	Sizer->Add(GetGlobalOtherPanel(Panel),0,wxALL|wxEXPAND,0);

	wxButton *Button = new wxButton(Panel,ID_DB_CONFIG,GetMsg(MSG_DB_CONFIG));
	Sizer->Add(Button,0,wxALL|wxEXPAND,5);
	return Panel;
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


wxPanel *COptionsDialog::GetFontPanel(wxWindow *Parent)
{
	wxColor color;
	
	wxPanel *Panel = new wxPanel(Parent);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBoxSizer *Box = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_SYMBOL_FONT));
	Sizer->Add(Box,0,wxALL|wxEXPAND,5);
	Panel->SetSizer(Sizer);
	
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	Box->Add(FlexSizer,1,wxALL|wxEXPAND,5);
	
	m_ShowNames = new wxCheckBox(Panel,ID_SHOW_NAMES,GetMsg(MSG_SHOW_NAMES));
	m_ShowNames->SetValue(GetShowFontNames());
	FlexSizer->Add(m_ShowNames,0,wxALL,1);
	FlexSizer->AddSpacer(1);

	wxStaticText *TextFontSize = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_FONT_SIZE),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextFontSize,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	m_FontSize = new wxSlider(Panel,ID_FONT_SIZE,0,0,1,wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(m_FontSize,0,wxALL,2);
	m_FontSize->SetMin(50);
	m_FontSize->SetMax(200);
	m_FontSize->SetValue(GetFontSize() * 10);
	
	wxStaticText *TextViewNameScale = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_VIEW_NAME_SCALE),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextViewNameScale,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	m_ViewNameScale = new wxSlider(Panel,ID_VIEW_NAME_SCALE,0,0,1,wxDefaultPosition,wxDefaultSize);
	m_ViewNameScale->SetMin(1);
	m_ViewNameScale->SetMax(10000);
	m_ViewNameScale->SetValue(GetViewFontScale());
	
	FlexSizer->Add(m_ViewNameScale,0,wxALL,2);
	

	return Panel;
}

wxPanel *COptionsDialog::GetPositionFromPanel(wxWindow *Parent)
{
	wxPanel *Panel = new wxPanel(Parent);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBoxSizer *Box = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_SYMBOL_POSITION));
	Sizer->Add(Box,0,wxALL|wxEXPAND,5);
	Panel->SetSizer(Sizer);
		
	m_PositionFromGps = new wxRadioButton(Panel,ID_GPS,GetMsg(MSG_GPS));
	Box->Add(m_PositionFromGps,0,wxALL,5);

	m_PositionFromSymbol = new wxRadioButton(Panel,ID_SYMBOL,GetMsg(MSG_SYMBOL));
	Box->Add(m_PositionFromSymbol,0,wxALL,5);
	
	m_PositionFromGps->SetValue(GetPositionFromGps());
	m_PositionFromSymbol->SetValue(!GetPositionFromGps());
	
	return Panel;
}

wxPanel *COptionsDialog::GetOtherPanel(wxWindow *Parent)
{
	wxPanel *Panel = new wxPanel(Parent);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBoxSizer *Box = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_OTHER));
	Sizer->Add(Box,0,wxALL|wxEXPAND,5);
	Panel->SetSizer(Sizer);
		
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	Box->Add(FlexSizer,1,wxALL|wxEXPAND,5);
	
	wxStaticText *TextScaleFactor = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SCALE_FACTOR),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextScaleFactor,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
		
	m_ScaleFactor = new wxSlider(Panel,ID_SCALE_FACTOR,0,0,1,wxDefaultPosition,wxDefaultSize);
	m_ScaleFactor->SetMin(1);
	m_ScaleFactor->SetMax(10000);
	m_ScaleFactor->SetValue(GetScaleFactor());
	FlexSizer->Add(m_ScaleFactor,0,wxALL,5);


	
	//wxStaticText *TextRestrictedArea = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_RESTRICTED_AREA_RADIUS),wxDefaultPosition,wxDefaultSize);
	//FlexSizer->Add(TextRestrictedArea,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
		
	//m_RestrictedArea = new wxTextCtrl(Panel,ID_RESTRICTED_AREA);
	//m_RestrictedArea->SetValue(wxString::Format(_("%d"),GetRestrictedArea()));
	//FlexSizer->Add(m_RestrictedArea,0,wxALL,5);

	/*
	m_CommTimeout = new wxSpinCtrl(Panel,ID_VIEW_NAME_SCALE,wxEmptyString);
	FlexSizer->Add(m_CommTimeout,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_CommTimeout->SetMin(0);
	m_CommTimeout->SetMax(60*24);
	m_CommTimeout->SetValue(GetCommTimeout());
	*/

	//m_CommTimeout = new wxSpinCtrlDouble(Panel,ID_VIEW_NAME_SCALE,wxEmptyString);
	//FlexSizer->Add(m_CommTimeout,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	//m_CommTimeout->SetValue(GetCommTimeout());


	//m_CommTimeout = new wxSpinCtrlDouble(Panel,ID_VIEW_NAME_SCALE,wxEmptyString);
	//m_CommTimeout->SetValue(GetViewFontScale());


	return Panel;

}

wxPanel *COptionsDialog::GetGlobalOtherPanel(wxWindow *Parent)
{
	wxPanel *Panel = new wxPanel(Parent);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBoxSizer *Box = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_OTHER));
	Sizer->Add(Box,0,wxALL|wxEXPAND,5);
	Panel->SetSizer(Sizer);
		
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	Box->Add(FlexSizer,1,wxALL|wxEXPAND,5);
	
	wxStaticText *TextOffPositionArea = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_OFF_POSITION_RADIUS),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextOffPositionArea,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
		
	m_OffPositionArea = new wxTextCtrl(Panel,ID_OFF_POSITION_AREA);
	m_OffPositionArea->SetValue(wxString::Format(_("%d"),GetOffPositionArea()));
	FlexSizer->Add(m_OffPositionArea,0,wxALL,5);

	wxStaticText *TextRestrictedArea = new wxStaticText(Panel,ID_RESTRICTED_AREA,GetMsg(MSG_RESTRICTED_AREA_RADIUS),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextRestrictedArea,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
		
	m_RestrictedArea = new wxTextCtrl(Panel,ID_RESTRICTED_AREA);
	m_RestrictedArea->SetValue(wxString::Format(_("%d"),GetRestrictedArea()));
	FlexSizer->Add(m_RestrictedArea,0,wxALL,5);
	
	wxStaticText *TextReportTimeout = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_REPORT_TIMEOUT),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextReportTimeout,0,wxALL|wxALIGN_CENTER_VERTICAL,5);

	m_ReportTimeout = new wxTextCtrl(Panel,ID_REPORT_TIMEOUT,wxEmptyString);
	FlexSizer->Add(m_ReportTimeout,0,wxALL,5);
	m_ReportTimeout->SetValue(wxString::Format(_("%d"),GetReportTimeout()));
	

	//m_CommTimeout = new wxSpinCtrlDouble(Panel,ID_VIEW_NAME_SCALE,wxEmptyString);
	//FlexSizer->Add(m_CommTimeout,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	//m_CommTimeout->SetValue(GetCommTimeout());


	//m_CommTimeout = new wxSpinCtrlDouble(Panel,ID_VIEW_NAME_SCALE,wxEmptyString);
	//m_CommTimeout->SetValue(GetViewFontScale());


	return Panel;

}


wxPanel *COptionsDialog::GetGlobalThresholdPanel(wxWindow *Parent)
{
	
	wxPanel *Panel = new wxPanel(Parent);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBoxSizer *Box = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_THRESHOLD));
	Sizer->Add(Box,0,wxALL|wxEXPAND,5);


	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	Box->Add(FlexSizer,1,wxALL|wxEXPAND,5);

	wxStaticText *TextLowerThreshold = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_LOWER_THRESHOLD));
	FlexSizer->Add(TextLowerThreshold,0,wxALL,5);
	m_LowerThreshold = new wxTextCtrl(Panel,ID_LOWER_THRESHOLD);
	m_LowerThreshold->SetValue(wxString::Format(_("%4.2f"),GetLowerThreshold()));
	FlexSizer->Add(m_LowerThreshold,0,wxALL,5);

	wxStaticText *TextUpperThreshold = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_UPPER_THRESHOLD));
	FlexSizer->Add(TextUpperThreshold,0,wxALL,5);
	m_UpperThreshold = new wxTextCtrl(Panel,ID_UPPER_THRESHOLD);
	m_UpperThreshold->SetValue(wxString::Format(_("%4.2f"),GetUpperThreshold()));
	FlexSizer->Add(m_UpperThreshold,0,wxALL,5);

	Panel->SetSizer(Sizer);

	return Panel;
}

wxPanel *COptionsDialog::GetGlobalSunPanel(wxWindow *Parent)
{
	
	wxPanel *Panel = new wxPanel(Parent);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBoxSizer *Box = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_SUNRISE_SUNSET));
	Sizer->Add(Box,0,wxALL|wxEXPAND,5);
	
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	Box->Add(FlexSizer,1,wxALL|wxEXPAND,5);

	wxStaticText *LabelLat = new wxStaticText(Panel,wxID_ANY,wxString::Format(_("%s\n(%s)"),GetMsg(MSG_LATITUDE),GetDegreeFormat(DEGREE_FORMAT_DDMMSS,DIR_LAT)),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(LabelLat,0,wxALL,5);
	m_TextLat = new wxTextCtrl(Panel,ID_SUN_LAT,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(m_TextLat,0,wxALL,5);
	
	wxStaticText *LabelLon = new wxStaticText(Panel,wxID_ANY,wxString::Format(_("%s\n(%s)"),GetMsg(MSG_LONGITUDE),GetDegreeFormat(DEGREE_FORMAT_DDMMSS,DIR_LON)),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(LabelLon,0,wxALL,5);
	m_TextLon = new wxTextCtrl(Panel,ID_SUN_LON,wxEmptyString, wxDefaultPosition, wxDefaultSize);
	FlexSizer->Add(m_TextLon,0,wxALL,5);
	
	if(!UNDEFINED_VAL(GetSunLon()))
		m_TextLon->SetValue(FormatLongitude(GetSunLon(),m_DegreeFormat));
	if(!UNDEFINED_VAL(GetSunLat()))
		m_TextLat->SetValue(FormatLatitude(GetSunLat(),m_DegreeFormat));

	Panel->SetSizer(Sizer);

	return Panel;
}

/*
wxPanel *COptionsDialog::GetRestrictedAreaPanel(wxWindow *Parent)
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

}
*/
wxPanel *COptionsDialog::GetButtonPanel(wxWindow *parent)
{

	wxPanel *Panel = new wxPanel(this);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);	
			
	wxStaticText *LabelProductInfo = new wxStaticText(Panel,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	Sizer->Add(LabelProductInfo,0,wxALL,5);
	Sizer->AddStretchSpacer(1);
	
	wxButton *ButtonOk = new wxButton(Panel,wxID_OK,GetMsg(MSG_CLOSE));
	//wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CANCEL));
	Sizer->AddStretchSpacer();
	Sizer->Add(ButtonOk,0,wxALL,5);
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

	event.Skip();
	///Signal();
	

}

void COptionsDialog::OnPositionFromGps(wxCommandEvent &event)
{
	SetPositionFromGps(true);
}

void COptionsDialog::OnPositionFromSymbol(wxCommandEvent &event)
{
	SetPositionFromGps(false);
}


void COptionsDialog::OnNameScale(wxCommandEvent &event)
{
	SetViewFontScale(event.GetInt());
		
}

void COptionsDialog::OnFontSize(wxCommandEvent &event)
{
	SetFontSize(event.GetInt());
}

void COptionsDialog::OnScaleFactor(wxCommandEvent &event)
{
	SetScaleFactor(event.GetInt());
}

void COptionsDialog::OnShowNames(wxCommandEvent &event)
{
	SetShowFontNames(event.IsChecked());
}

void COptionsDialog::OnRestrictedArea(wxCommandEvent &event)
{
	long v;
	m_RestrictedArea->GetValue().ToLong(&v);
	SetRestrictedArea(v);
}

void COptionsDialog::OnUpperThreshold(wxCommandEvent &event)
{
	long v;
	m_UpperThreshold->GetValue().ToLong(&v);
	SetUpperThreshold(v);
}

void COptionsDialog::OnLowerThreshold(wxCommandEvent &event)
{
	long v;
	m_LowerThreshold->GetValue().ToLong(&v);
	SetLowerThreshold(v);
}

void COptionsDialog::OnOffPositionArea(wxCommandEvent &event)
{
	long v;
	m_OffPositionArea->GetValue().ToLong(&v);
	SetOffPositionArea(v);
}

void COptionsDialog::OnReportTimeout(wxCommandEvent &event)
{
	long v;
	m_ReportTimeout->GetValue().ToLong(&v);
	SetReportTimeout(v);
}

void COptionsDialog::OnLon(wxCommandEvent &event)
{	
	if(m_TextLon->GetValue().empty())
	{
		m_LonValid = false;
		return;
	}
		
	if(_SetLon(m_TextLon->GetValue().char_str(),&m_Lon,m_DegreeFormat))
	{
		m_LonValid = true;
		SetSunLon(m_Lon);
		m_TextLon->SetForegroundColour(wxSYS_COLOUR_WINDOWTEXT);
		m_TextLon->Refresh();

	}else{
		
		m_LonValid = false;
		m_TextLon->SetForegroundColour(*wxRED);
		m_TextLon->Refresh();
	
	}

}

void COptionsDialog::OnLat(wxCommandEvent &event)
{
	if(m_TextLat->GetValue().empty())
	{
		m_LatValid = false;
		return;
	}
			
	if(_SetLat(m_TextLat->GetValue().char_str(),&m_Lat,m_DegreeFormat))
	{
		m_LatValid = true;
		SetSunLat(m_Lat);
		m_TextLat->SetForegroundColour(wxSYS_COLOUR_WINDOWTEXT);
		m_TextLat->Refresh();

	}else{
		
		m_LatValid = false;
		m_TextLat->SetForegroundColour(*wxRED);
		m_TextLat->Refresh();
	}

}

void COptionsDialog::OnDbConfig(wxCommandEvent &event)
{
	
	CDBConfig *DBConfig = new CDBConfig();
	DBConfig->CreateGUI();
	DBConfig->SetFooter(GetProductInfo());
	DBConfig->SetHost(GetDBHost());
	DBConfig->SetDatabaseName(GetDBName());
	DBConfig->SetUser(GetDBUser());
	DBConfig->SetPassword(GetDBPassword());
	DBConfig->SetPort(GetDBPort());
	DBConfig->Fit();
	DBConfig->Layout();
	DBConfig->Center();

	if(DBConfig->ShowModal() == wxID_OK)
	{
		SetDBHost(DBConfig->GetHost());
		SetDBName(DBConfig->GetDatabaseName());
		SetDBUser(DBConfig->GetUser());
		SetDBPassword(DBConfig->GetPassword());
		SetDBPort(DBConfig->GetPort());
		WriteDBConfig();
	}
		
	delete DBConfig;

}