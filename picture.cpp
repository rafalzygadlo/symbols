#include "picture.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include <wx/stattext.h>
#include <wx/mstream.h>
#include <wx/log.h>
#include "dialog.h"

BEGIN_EVENT_TABLE(CPicturePanel, wxPanel)
	EVT_HYPERLINK(ID_NEW,CPicturePanel::OnNew)
	EVT_HYPERLINK(ID_PICK,CPicturePanel::OnPick)
END_EVENT_TABLE()


CPicturePanel::CPicturePanel(void *db,wxWindow *parent, int type)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_ID = -1;
	m_DB = db;
	wxStaticBoxSizer *Sizer = new wxStaticBoxSizer(wxVERTICAL,this,GetMsg(MSG_PICTURE));
	SetSizer(Sizer);

	m_Info = new wxStaticText(this,wxID_ANY,wxEmptyString);
	Sizer->Add(m_Info,0,wxALL|wxALIGN_CENTER,2);
	m_StaticPicture = new wxStaticBitmap(this,wxID_ANY,wxNullBitmap);
	m_StaticPicture->SetMinSize(wxSize(PICTURE_MAX_WIDTH,PICTURE_MAX_HEIGHT));
	Sizer->Add(m_StaticPicture,0,wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL,2);
	
	if(type == PICTURE_PANEL_NEW)
	{
		wxHyperlinkCtrl *m_New = new wxHyperlinkCtrl(this,ID_NEW,GetMsg(MSG_CHOOSE_PICTURE),wxEmptyString);
		Sizer->Add(m_New,0,wxALL|wxALIGN_CENTER,2);
	}
	
	if(type == PICTURE_PANEL_PICKER)
	{
		wxHyperlinkCtrl *m_New = new wxHyperlinkCtrl(this,ID_PICK,GetMsg(MSG_CHOOSE_PICTURE),wxEmptyString);
		Sizer->Add(m_New,0,wxALL|wxALIGN_CENTER,2);
	}
			
	SetSizer(Sizer);
}

CPicturePanel::~CPicturePanel()
{

}

void CPicturePanel::SetDB(void *db)
{
	m_DB = db;
}

wxImage CPicturePanel::GetPicture()
{
	return m_Picture;
}

void CPicturePanel::SetPictureId(int id)
{
	m_ID = id;
	Clear();
	Read();
	//m_Image = image;
	//wxBitmap bmp(image);
	//m_Picture->SetBitmap(bmp);
}

int CPicturePanel::GetPictureId()
{
	return m_ID;
}

void CPicturePanel::OnPick(wxHyperlinkEvent &event)
{
	CDialog *Dialog = new CDialog(m_DB,CONTROL_PICTURE,true);
	if(Dialog->ShowModal() == wxID_OK)
	{
		SetPictureId(Dialog->_GetId());
	}
	
	delete Dialog;
}

void CPicturePanel::OnNew(wxHyperlinkEvent &event)
{
	New();
}

void CPicturePanel::New()
{
	wxFileDialog *File = new wxFileDialog(this);
	if(File->ShowModal() == wxID_OK)
	{
		wxLogNull log;
		wxImage image;
		if(image.LoadFile(File->GetPath()))
		{
			int height = image.GetHeight();
			int width = image.GetWidth();
			float ratio = 1;
			
			if(height > PICTURE_MAX_HEIGHT || width > PICTURE_MAX_WIDTH)
			{
				if(height > width)
				{
					ratio = (float)height/width;
					image.Rescale(PICTURE_MAX_WIDTH /ratio,PICTURE_MAX_HEIGHT);
				}else{
					ratio = (float)width/height;
					image.Rescale(PICTURE_MAX_WIDTH ,PICTURE_MAX_HEIGHT/ ratio);
				}
			}
		
			if(image.IsOk())
			{
				wxMemoryOutputStream stream;
				if(!image.SaveFile(stream,wxBITMAP_TYPE_PNG))
					return;
				
				if(stream.GetOutputStreamBuffer()->GetBufferSize() > PICTURE_MAX_SIZE)
				{
					wxMessageBox(wxString::Format(GetMsg(MSG_PICTURE_TO_BIG),PICTURE_MAX_SIZE/1000 )); 
				
				}else{
									
					Clear();
					m_Info->SetLabel(wxString::Format(GetMsg(MSG_PICTURE_INFO),image.GetWidth(),image.GetHeight()));	
					wxBitmap bmp_0(image);
					m_StaticPicture->SetBitmap(bmp_0);
					m_Picture = image;
					this->Refresh();
					this->Layout();
				}
			}

		}
	}
	
	delete File;
}

void CPicturePanel::Clear()
{
	m_Info->SetLabel(wxEmptyString);
	m_StaticPicture->SetSize(PICTURE_MAX_WIDTH,PICTURE_MAX_HEIGHT);
	m_StaticPicture->SetBitmap(wxNullBitmap);
	m_StaticPicture->Refresh();
	this->Refresh();
}

void CPicturePanel::_SetId(int id)
{
	m_ID = id;
}


void CPicturePanel::Read()
{
	wxString sql;
	sql = wxString::Format(_("SELECT * FROM `%s` WHERE id = '%d'"),TABLE_PICTURE,m_ID);

	my_query(m_DB,sql);

	void *result = db_result(m_DB);
	
	char **row = (char**)db_fetch_row(result);
	
	unsigned long *len = db_fetch_lengths(result);
	//m_StaticPicture->ClearBackground();
	m_StaticPicture->SetBitmap(wxNullBitmap);

	if(row && len)
	{
		int size = len[FI_PICTURE_DATA];
		
		
		if(size > 0)
		{
			wxMemoryInputStream stream( row[FI_PICTURE_DATA],len[FI_PICTURE_DATA]);
			wxLogNull log;
			wxImage img(stream);
			Clear();
		
			if(img.IsOk())
			{
				m_Info->SetLabel(wxString::Format(GetMsg(MSG_PICTURE_INFO),img.GetWidth(),img.GetHeight()));	
				wxBitmap bmp(img);
				m_StaticPicture->SetBitmap(bmp);
			}
		}
				
	}else{
		
		m_Info->SetLabel(GetMsg(MSG_NO_PICTURE));	
	
	}
	
	this->Refresh();
	this->Layout();

	db_free_result(result);
	
}