#include "command.h"
#include "conf.h"
#include "tools.h"
#include "db.h"

BEGIN_EVENT_TABLE(CCommandPanel, wxPanel)
	//EVT_HYPERLINK(ID_NEW,CCommandPanel::OnNew)
	//EVT_HYPERLINK(ID_PICK,CCommandPanel::OnPick)
END_EVENT_TABLE()

CCommandPanel::CCommandPanel(void *db,wxWindow *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_DB = db;
	m_Sizer = new wxStaticBoxSizer(wxVERTICAL,this,GetMsg(MSG_COMMAND));
	SetSizer(m_Sizer);
	Read();
	Refresh();
	Layout();
}

CCommandPanel::~CCommandPanel()
{

}

void CCommandPanel::Read()
{
	wxString sql;
	sql = wxString::Format(_("SELECT * FROM `%s`"),TABLE_COMMAND);

	my_query(m_DB,sql);

	void *result = db_result(m_DB);
	if(result == NULL)
		return;
	char **row = NULL;
	
	wxFont font;
	font.SetPointSize(10);
	while(row = (char**)db_fetch_row(result))
	{
		wxHyperlinkCtrl *HyperLink = new wxHyperlinkCtrl(this,wxID_ANY,Convert(row[FI_COMMAND_NAME]),wxEmptyString);
		HyperLink->SetFont(font);
		m_Sizer->Add(HyperLink,0,wxALL,2);
	}
	
	db_free_result(result);
	
}