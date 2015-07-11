#include "frame.h"
#include "conf.h"
#include "dll.h"
#include <wx/statline.h>
#include <wx/dirdlg.h>
#include "NaviMapIOApi.h"
#include "tools.h"
#include "db.h"
#include "GeometryTools.h"

BEGIN_EVENT_TABLE(CMyFrame,wxDialog)
	EVT_BUTTON(ID_CLOSE,CMyFrame::OnCloseButton)
	EVT_BUTTON(ID_COMMAND,CMyFrame::OnCommandButton)
	EVT_TEXT(ID_NAME,CMyFrame::OnTextChanged)
	EVT_TEXT(ID_DESCRIPTION,CMyFrame::OnTextChanged)
	EVT_TEXT(ID_LON,CMyFrame::OnLon)
	EVT_TEXT(ID_LAT,CMyFrame::OnLat)
END_EVENT_TABLE()

//extern CNaviMapIOApi *ThisPtr;
//extern CNaviBroker *BrokerPtr;
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//FRAME
CMyFrame::CMyFrame(void *Parent, wxWindow *ParentPtr)
	:wxDialog(ParentPtr,wxID_ANY, GetMsg(MSG_MANAGER), wxDefaultPosition, wxDefaultSize,  wxRESIZE_BORDER|wxDEFAULT_DIALOG_STYLE)
{
	m_SymbolPanel = NULL;
	m_DLL = (CMapPlugin*)Parent;
	_ParentPtr = ParentPtr;
	
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);

	m_Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME);
	m_Notebook->AddPage(GetPage1(m_Notebook),GetMsg(MSG_INFO));
	
	//Other
	MainSizer->Add(m_Notebook,1,wxALL|wxEXPAND,0);
	
	wxPanel *ButtonPanel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	MainSizer->Add(ButtonPanel,0,wxALL|wxEXPAND,5);
	wxBoxSizer *ButtonPanelSizer = new wxBoxSizer(wxHORIZONTAL);
	ButtonPanel->SetSizer(ButtonPanelSizer);
		
	ButtonPanelSizer->AddStretchSpacer(1);
	ButtonClose = new wxButton(ButtonPanel,ID_CLOSE,GetMsg(MSG_CLOSE),wxDefaultPosition,wxDefaultSize);
	ButtonPanelSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);
		
	this->SetSizer(MainSizer);
		
	if(GetSizer())
		GetSizer()->SetSizeHints(this);
	
	ReadConfig();

	SetSize(m_FrameWidth,m_FrameHeight);

	Center();
}

CMyFrame::~CMyFrame(void)
{
	WriteConfig();
}

void CMyFrame::WriteConfig()
{
	wxFileConfig *FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetConfigFile(),wxEmptyString);
	FileConfig->Write(_(KEY_FRAME_WIDTH),this->GetSize().GetWidth());
	FileConfig->Write(_(KEY_FRAME_HEIGHT),this->GetSize().GetHeight());
	delete FileConfig;
}

void CMyFrame::ReadConfig()
{
	wxFileConfig *FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetConfigFile(),wxEmptyString);
	FileConfig->Read(_(KEY_FRAME_WIDTH),&m_FrameWidth,DEFAULT_FRAME_WIDTH);
	FileConfig->Read(_(KEY_FRAME_HEIGHT),&m_FrameHeight,DEFAULT_FRAME_HEIGHT);
	delete FileConfig;
}

wxPanel *CMyFrame::GetPage1(wxWindow *parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel->SetSizer(Sizer);
	m_SymbolPanel = new CSymbolPanel(Panel);
	Sizer->Add(m_SymbolPanel,1,wxALL|wxEXPAND,5);
	return Panel;
}

wxPanel *CMyFrame::GetPage2(wxWindow *parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel->SetSizer(Sizer);
	return Panel;
}


void CMyFrame::OnLon(wxCommandEvent &event)
{
	/*
	float value = MarkerSelectedPtr->x;
	
	if(_SetLon(textlon->GetValue().char_str(),&value))
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
	*/
}

void CMyFrame::OnLat(wxCommandEvent &event)
{
	/*
	float value = MarkerSelectedPtr->y;

	if(_SetLat(textlat->GetValue().char_str(),&value))
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
	*/
}


void CMyFrame::OnTextChanged(wxCommandEvent &event)
{	
	
	// ButtonSave->Enable();
}

void CMyFrame::OnCloseButton(wxCommandEvent &event)
{	
	Hide();
}

void CMyFrame::OnCommandButton(wxCommandEvent &event)
{	
	
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
		
		SelectedPtr = m_DLL->GetSelectedPtr();
		if(SelectedPtr == NULL)
			return;


		double vm[4];
		m_DLL->GetBroker()->GetVisibleMap(vm);
		
		float scale = m_DLL->GetBroker()->GetMapScale();
		wxPoint pt;
		pt.x = (int)((-vm[0] + SelectedPtr->GetLonMap()) * scale) + ParentX;
		pt.y = (int)((-vm[1] + SelectedPtr->GetLatMap()) * scale) + ParentY;
		
		wxPoint p2,p4;
		wxSize size = this->GetSize();
				
		p2.x = pt.x + size.GetWidth(); p2.y = pt.y;
				
		if(!IsOnScreen(p2.x,p2.y))
		{
			pt.x = pt.x - size.GetWidth();
			pt.y = pt.y;
		}
						
		p4.x = pt.x; p4.y = pt.y + size.GetHeight();

		if(!IsOnScreen(p4.x,p4.y))
		{
			pt.x = pt.x;
			pt.y = pt.y - size.GetHeight();
		}
		
		if(pt.y < 0)
			pt.y = 0;


		m_SymbolPanel->SetPage1(SelectedPtr);
		this->SetPosition(pt);
		
				
	}
	
	Show(show);
}

bool CMyFrame::IsOnScreen(int x, int y)
{
	int sWidth;
	int sHeight;
	wxDisplaySize(&sWidth,&sHeight);
	
	if(IsPointInsideBox(x, y, 0 , 0, sWidth, sHeight))
		return true;

	return false;
}