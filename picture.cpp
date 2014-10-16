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


CPicturePanel::CPicturePanel(wxWindow *parent, int type)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	this->SetWindowStyle(wxBORDER_SIMPLE);
	//SetBackgroundColour(*wxWHITE);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);

	m_Info = new wxStaticText(this,wxID_ANY,wxEmptyString);
	Sizer->Add(m_Info,0,wxALL,5);
	m_Picture = new wxStaticBitmap(this,wxID_ANY,wxNullBitmap);
	m_Picture->SetBackgroundColour(*wxWHITE);
	m_Picture->SetWindowStyle(wxBORDER_SIMPLE);
	m_Picture->SetMinSize(wxSize(PICTURE_MAX_WIDTH,PICTURE_MAX_HEIGHT));
	Sizer->Add(m_Picture,0,wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL,0);
	
	if(type == PICTURE_PANEL_NEW)
	{
		wxHyperlinkCtrl *m_New = new wxHyperlinkCtrl(this,ID_NEW,GetMsg(MSG_CHOOSE_PICTURE),wxEmptyString);
		Sizer->Add(m_New,0,wxALL,10);
	}
	
	if(type == PICTURE_PANEL_PICKER)
	{
		wxHyperlinkCtrl *m_New = new wxHyperlinkCtrl(this,ID_PICK,GetMsg(MSG_CHOOSE_PICTURE),wxEmptyString);
		Sizer->Add(m_New,0,wxALL,10);
	}

	wxBoxSizer *VSizer = new wxBoxSizer(wxHORIZONTAL);
	Sizer->Add(VSizer,0,wxALL,0);
		
	SetSizer(Sizer);
}

CPicturePanel::~CPicturePanel()
{

}
wxImage CPicturePanel::GetImage()
{
	return m_Image;
}

void CPicturePanel::SetImageId(wxString id)
{
	m_ID = id;
	Clear();
	Read();
	//m_Image = image;
	//wxBitmap bmp(image);
	//m_Picture->SetBitmap(bmp);
}

void CPicturePanel::OnPick(wxHyperlinkEvent &event)
{
	CDialog *Dialog = new CDialog(CONTROL_PICTURE,true);
	if(Dialog->ShowModal() == wxID_OK)
	{
		SetImageId(Dialog->_GetId());
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
				if(!image.SaveFile(stream,wxBITMAP_TYPE_JPEG))
					return;
				
				if(stream.GetOutputStreamBuffer()->GetBufferSize() > PICTURE_MAX_SIZE)
				{
					wxMessageBox(wxString::Format(GetMsg(MSG_PICTURE_TO_BIG),PICTURE_MAX_SIZE/1000 )); 
				
				}else{
									
					Clear();
					m_Info->SetLabel(wxString::Format(GetMsg(MSG_PICTURE_INFO),image.GetWidth(),image.GetHeight()));	
					wxBitmap bmp_0(image);
					m_Picture->SetBitmap(bmp_0);
					m_Image = image;
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
	m_Picture->SetSize(PICTURE_MAX_WIDTH,PICTURE_MAX_HEIGHT);
	m_Picture->SetBitmap(wxNullBitmap);
	m_Picture->Refresh();
	this->Refresh();
}

void CPicturePanel::_SetId(wxString id)
{
	m_ID = id;
}

void CPicturePanel::Read()
{
	wxString sql;
	sql = wxString::Format(_("SELECT * FROM `%s` WHERE id = '%s'"),TABLE_PICTURE,m_ID);

	my_query(sql);

	void *result = db_result();
	
	char **row = (char**)db_fetch_row(result);
	
	unsigned long *len = db_fetch_lengths(result);

	if(row && len)
	{
		int size = len[FI_PICTURE_DATA];
		m_Picture->ClearBackground();
		m_Picture->SetBitmap(wxNullBitmap);
		
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
				m_Picture->SetBitmap(bmp);
			}
		}
		
		this->Refresh();
		this->Layout();
	}

	db_free_result(result);
	
}