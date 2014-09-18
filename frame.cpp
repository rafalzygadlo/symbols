#include "frame.h"
#include "conf.h"
#include "dll.h"
#include <wx/statline.h>
#include <wx/dirdlg.h>
#include "NaviMapIOApi.h"
#include "tools.h"


BEGIN_EVENT_TABLE(CMyFrame,wxDialog)
	EVT_BUTTON(ID_CLOSE,CMyFrame::OnCloseButton)
//	EVT_BUTTON(ID_SAVE,CMyFrame::OnSaveButton)
	EVT_TEXT(ID_NAME,CMyFrame::OnTextChanged)
	EVT_TEXT(ID_DESCRIPTION,CMyFrame::OnTextChanged)
	EVT_BUTTON(ID_DELETE,CMyFrame::OnMarkerDelete)
	EVT_TEXT(ID_LON,CMyFrame::OnLon)
	EVT_TEXT(ID_LAT,CMyFrame::OnLat)
END_EVENT_TABLE()

extern CNaviMapIOApi *ThisPtr;
extern CNaviBroker *BrokerPtr;
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//FRAME

CMyFrame::CMyFrame(void *Parent, wxWindow *ParentPtr)
	:wxDialog(ParentPtr,wxID_ANY, GetMsg(MSG_MANAGER), wxDefaultPosition, wxDefaultSize)
{
	m_DLL = (CMapPlugin*)Parent;
	_ParentPtr = ParentPtr;
	AfterInit = false;
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel->SetBackgroundColour(*wxWHITE);
			
	// Page1
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
		
	GridSizer = new wxFlexGridSizer(2,0,0);	
	PanelSizer->Add(GridSizer,1,wxALL|wxEXPAND,5);
	
	// marker name
	wxStaticText *labelname = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_NAME),wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(labelname,0,wxALL,5);
	textname = new wxTextCtrl(Panel,ID_NAME,wxEmptyString, wxDefaultPosition, wxDefaultSize);
	GridSizer->AddGrowableCol(1);
	GridSizer->AddGrowableRow(1);
	GridSizer->Add(textname,0,wxALL|wxEXPAND,5);
	
	// marker description
	wxStaticText *labeldescription = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_DESCRIPTION),wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(labeldescription,0,wxALL,5);
	textdescription = new wxTextCtrl(Panel,ID_DESCRIPTION,wxEmptyString,wxDefaultPosition,wxSize(250,100),wxTE_MULTILINE);
	GridSizer->Add(textdescription,0,wxALL|wxEXPAND,5);
		
	wxStaticText *labellat = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_LATITUDE),wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(labellat,0,wxALL,5);
	
	textlat = new wxTextCtrl(Panel,ID_LAT,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	
	GridSizer->Add(textlat,0,wxALL,5);
	
	wxStaticText *labellon = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_LONGITUDE) ,wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(labellon,0,wxALL,5);

	textlon = new wxTextCtrl(Panel,ID_LON,wxEmptyString, wxDefaultPosition, wxDefaultSize);
	GridSizer->Add(textlon,0,wxALL,5);
			
	Panel->SetSizer(PanelSizer);
		
	//Other
	MainSizer->Add(Panel,1,wxALL|wxEXPAND,0);
	ButtonClose = new wxButton(this,ID_CLOSE,GetMsg(MSG_CLOSE),wxDefaultPosition,wxDefaultSize);
	MainSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);
		
	this->SetSizer(MainSizer);
		
	if(GetSizer())
		GetSizer()->SetSizeHints(this);
		
	Center();

	//this->SetTransparent(200);
	AfterInit = true;
}

CMyFrame::~CMyFrame(void)
{

}

void CMyFrame::OnLon(wxCommandEvent &event)
{

	float value = MarkerSelectedPtr->x;
	
	if(SetLon(textlon->GetValue().char_str(),&value))
	{
		double y,to_x,to_y;
		y = MarkerSelectedPtr->y;
		m_DLL->GetBroker()->Unproject(value,y,&to_x,&to_y);
		MarkerSelectedPtr->x = to_x;
					
		m_DLL->GetBroker()->Refresh(m_DLL->GetBroker()->GetParentPtr());
		textlon->SetForegroundColour(wxSYS_COLOUR_WINDOWTEXT);
		textlon->Refresh();

	}else{
		
		textlon->SetForegroundColour(*wxRED);
		textlon->Refresh();
	
	}


}

void CMyFrame::OnLat(wxCommandEvent &event)
{
	float value = MarkerSelectedPtr->y;

	if(SetLat(textlat->GetValue().char_str(),&value))
	{
		
		double x,to_x,to_y;
		x = MarkerSelectedPtr->x;
		//fprintf(stdout,"x:%f value:%f\n",x,value);
		m_DLL->GetBroker()->Unproject(x,value,&to_x,&to_y);

		//fprintf(stdout,"to_x:%f to_y:%f\n",to_x,to_y);
		MarkerSelectedPtr->y = (float)to_y;
					
		m_DLL->GetBroker()->Refresh(m_DLL->GetBroker()->GetParentPtr());
		textlat->SetForegroundColour(wxSYS_COLOUR_WINDOWTEXT);
		textlat->Refresh();

	}else{
		
		textlat->SetForegroundColour(*wxRED);
		textlat->Refresh();
	}
		
}

void CMyFrame::ShowIconChanger(bool show)
{
	PanelIcon->Show(show);
	if(GetSizer())
		GetSizer()->SetSizeHints(this);

}

void CMyFrame::OnTextChanged(wxCommandEvent &event)
{	
	if(!AfterInit)
		return;
	
	if(event.GetId() == ID_NAME)
	{
		if(textname->GetValue().Length() >= MARKER_NAME_SIZE)
			ButtonClose->Disable();
		else
			ButtonClose->Enable();
	}

	if(event.GetId() == ID_DESCRIPTION)
	{
		if(textdescription->GetValue().Length() >= MARKER_DESCRIPTION_SIZE)
			ButtonClose->Disable();
		else
			ButtonClose->Enable();
	}
	
	
	// ButtonSave->Enable();
}

void CMyFrame::OnMarkerDelete(wxCommandEvent &event)
{
	int sel = markerlistbox->GetSelection();
	MarkerList->erase(MarkerList->begin() + sel);
	markerlistbox->Delete(sel);
}

void CMyFrame::OnCloseButton(wxCommandEvent &event)
{	
	wcscpy_s(MarkerSelectedPtr->name,MARKER_NAME_SIZE, textname->GetValue().wc_str()); 
	wcscpy_s(MarkerSelectedPtr->description, MARKER_DESCRIPTION_SIZE, textdescription->GetValue().wc_str()); 
	Hide();
}

void CMyFrame::OnClose(wxCloseEvent &event)
{
	Hide();
}
void CMyFrame::OnLeftClick(wxCommandEvent &event)
{
	
}
void CMyFrame::ShowWindow(bool show)
{
	if(show)
	{
		
		ParentX = _ParentPtr->GetScreenPosition().x;
		ParentY = _ParentPtr->GetScreenPosition().y;
		
		double to_x, to_y;
		MarkerSelectedPtr = m_DLL->GetSelectedPtr();
		if(MarkerSelectedPtr == NULL)
			return;
		
		m_DLL->GetBroker()->Project(MarkerSelectedPtr->x,MarkerSelectedPtr->y,&to_x,&to_y);
	
		double vm[4];
		m_DLL->GetBroker()->GetVisibleMap(vm);
		
		float scale = m_DLL->GetBroker()->GetMapScale();
		wxPoint pt;
		pt.x = (int)((-vm[0] + MarkerSelectedPtr->x) * scale) + ParentX;
		pt.y = (int)((-vm[1] + MarkerSelectedPtr->y) * scale) + ParentY;
			
		this->SetPosition(pt);
		textname->SetValue(wxString::Format(_("%s"),MarkerSelectedPtr->name));
		textdescription->SetValue(wxString::Format(_("%s"),MarkerSelectedPtr->description));
		
		textlon->SetLabel(FormatLongitude(to_x));
		textlat->SetLabel(FormatLatitude(-to_y));
	}
	
	Show(show);
}

