#include "conf.h"
#include "info.h"
#include "tools.h"
#include <wx/mstream.h>
#include <wx/animate.h>

CMyInfo::CMyInfo(wxWindow *Parent, wxString text, bool center_on_screen)
	:wxDialog(Parent, wxID_ANY, GetProductName(), wxDefaultPosition, wxDefaultSize)
{
	//wxMemoryInputStream in((const unsigned char*)waitanim, waitanim_size);
	
	wxBoxSizer *MainSizer = new wxBoxSizer(wxHORIZONTAL);
	wxAnimation data;
	//data.Load(in);
	wxAnimationCtrl *Animation = new wxAnimationCtrl(this,wxID_ANY,data);
	Animation->SetAnimation(data);
	Animation->Play();
	MainSizer->Add(Animation,0,wxALL|wxCENTER|wxALIGN_CENTER ,5);
	
	Text = new wxStaticText(this,wxID_ANY,text,wxDefaultPosition);
	MainSizer->Add(Text,1,wxALL|wxCENTER|wxALIGN_CENTER ,5);
	
	this->SetBackgroundColour(*wxWHITE);
	this->SetForegroundColour(*wxWHITE);
	this->SetSizer(MainSizer);
	this->Fit();
	if(center_on_screen)
		this->CenterOnScreen();
	else
		this->CenterOnParent();	
	this->Show(true);
    this->Refresh();
    this->Update();
	
	
		
	
}

CMyInfo::~CMyInfo(void)
{
	this->Show(false);
	this->Close();
	//this->EndModal(0);
}

void CMyInfo::SetText(wxString str)
{
	Text->SetLabel(str);
}