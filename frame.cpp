#include "frame.h"
#include "conf.h"
#include "dll.h"
#include <wx/statline.h>
#include <wx/dirdlg.h>
#include "NaviMapIOApi.h"
#include "tools.h"
#include "db.h"

BEGIN_EVENT_TABLE(CMyFrame,wxDialog)
	EVT_BUTTON(ID_CLOSE,CMyFrame::OnCloseButton)
//	EVT_BUTTON(ID_SAVE,CMyFrame::OnSaveButton)
	EVT_TEXT(ID_NAME,CMyFrame::OnTextChanged)
	EVT_TEXT(ID_DESCRIPTION,CMyFrame::OnTextChanged)
	EVT_TEXT(ID_LON,CMyFrame::OnLon)
	EVT_TEXT(ID_LAT,CMyFrame::OnLat)
END_EVENT_TABLE()

extern CNaviMapIOApi *ThisPtr;
extern CNaviBroker *BrokerPtr;
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//FRAME
CMyFrame::CMyFrame(void *db,void *Parent, wxWindow *ParentPtr)
	:wxDialog(ParentPtr,wxID_ANY, GetMsg(MSG_MANAGER), wxDefaultPosition, wxDefaultSize)
{
	m_DB = db;
	m_DLL = (CMapPlugin*)Parent;
	_ParentPtr = ParentPtr;
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
		
	m_CommandPanel = new CCommandPanel(db,this);
	MainSizer->Add(m_CommandPanel,0,wxALL,5);

	// Page1
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxHORIZONTAL);
	
	m_PicturePanel = new CPicturePanel(db,Panel);
	PanelSizer->Add(m_PicturePanel,0,wxALL,5);
			
	wxFlexGridSizer *GridSizer = new wxFlexGridSizer(2,0,0);	
	PanelSizer->Add(GridSizer,1,wxALL|wxEXPAND,5);
		
	
	wxStaticText *labelname = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_NAME),wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(labelname,0,wxALL,5);
	m_TextName = new wxTextCtrl(Panel,ID_NAME,wxEmptyString, wxDefaultPosition, wxDefaultSize);
	GridSizer->AddGrowableCol(1);
	GridSizer->AddGrowableRow(1);
	GridSizer->Add(m_TextName,0,wxALL|wxEXPAND,5);
	
	// marker description
	wxStaticText *labeldescription = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_DESCRIPTION),wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(labeldescription,0,wxALL,5);
	m_TextInfo = new wxTextCtrl(Panel,ID_DESCRIPTION,wxEmptyString,wxDefaultPosition,wxSize(250,100),wxTE_MULTILINE);
	GridSizer->Add(m_TextInfo,0,wxALL|wxEXPAND,5);
		
	wxStaticText *labellat = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_LATITUDE),wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(labellat,0,wxALL,5);
	
	m_TextLat = new wxTextCtrl(Panel,ID_LAT,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(m_TextLat,0,wxALL,5);
	
	wxStaticText *labellon = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_LONGITUDE) ,wxDefaultPosition,wxDefaultSize);
	GridSizer->Add(labellon,0,wxALL,5);

	m_TextLon = new wxTextCtrl(Panel,ID_LON,wxEmptyString, wxDefaultPosition, wxDefaultSize);
	GridSizer->Add(m_TextLon,0,wxALL,5);
			
	Panel->SetSizer(PanelSizer);
		
	//Other
	MainSizer->Add(Panel,1,wxALL|wxEXPAND,0);
	ButtonClose = new wxButton(this,ID_CLOSE,GetMsg(MSG_CLOSE),wxDefaultPosition,wxDefaultSize);
	MainSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);
		
	this->SetSizer(MainSizer);
		
	if(GetSizer())
		GetSizer()->SetSizeHints(this);
		
	Center();
}

CMyFrame::~CMyFrame(void)
{

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
	//wcscpy_s(MarkerSelectedPtr->name,SYMBOL_NAME_SIZE, textname->GetValue().wc_str()); 
	//wcscpy_s(MarkerSelectedPtr->description, SYMBOL_DESCRIPTION_SIZE, textdescription->GetValue().wc_str()); 
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
		SelectedPtr = m_DLL->GetSelectedPtr();
		if(SelectedPtr == NULL)
			return;
		
		m_DLL->GetBroker()->Project(SelectedPtr->lon,SelectedPtr->lat,&to_x,&to_y);
		double vm[4];
		m_DLL->GetBroker()->GetVisibleMap(vm);
		
		float scale = m_DLL->GetBroker()->GetMapScale();
		wxPoint pt;
		pt.x = (int)((-vm[0] + SelectedPtr->lon) * scale) + ParentX;
		pt.y = (int)((-vm[1] + SelectedPtr->lat) * scale) + ParentY;
			
		this->SetPosition(pt);
		
		wxString sql = wxString::Format(_("SELECT *FROM `%s` WHERE id ='%d'"),TABLE_SYMBOL,SelectedPtr->id);
		my_query(m_DB,sql);
			
		void *result = db_result(m_DB);
		
		char **row = NULL;
		if(result == NULL)
			return;
		
		row = (char**)db_fetch_row(result);
		m_TextName->SetValue(wxString::Format(_("%s"),Convert(row[FI_SYMBOL_NAME]).wc_str()));
		m_TextInfo->SetValue(wxString::Format(_("%s"),Convert(row[FI_SYMBOL_INFO]).wc_str()));
		db_free_result(result);
		
		m_TextLon->SetLabel(FormatLongitude(to_x,DEFAULT_DEGREE_FORMAT));
		m_TextLat->SetLabel(FormatLatitude(-to_y,DEFAULT_DEGREE_FORMAT));

		sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_symbol='%d'"),TABLE_SYMBOL_PICTURE,SelectedPtr->id);
		my_query(m_DB,sql);
			
		result = db_result(m_DB);
		if(result == NULL)
			return;
		
		row = (char**)db_fetch_row(result);
		if(row == NULL)
			return;
		
		m_PicturePanel->SetPictureId(atoi(row[FI_SYMBOL_PICTURE_ID_PICTURE]));
		
		db_free_result(result);
	}
	
	Show(show);
}

