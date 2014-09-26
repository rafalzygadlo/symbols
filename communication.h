#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include <wx/wx.h>
#include "listctrl.h"

class CCommunication;
class CCommunicationDialog: public wxDialog
{
	wxString m_Field;	
	wxString m_Order;
	CListCtrl *m_List;	
	wxString m_Id,m_Name;
	wxPanel *GetPanel(wxWindow *Parent);
	void Read();
	void Clear();
	void Select();

public:

	CCommunicationDialog(int type = -1);
	~CCommunicationDialog();
	
	void OnNew();
	void OnEdit(wxString id);
	void OnDelete(wxString id);
	void OnColumnCLick(wxString field, int order);
	wxString GetCommunicationId();
	wxString GetCommunicationName();
		
	
};

class CCommunicationPanel: public wxPanel
{
	wxWindow *m_Parent, *m_Top;
	wxBoxSizer *m_Sizer;
	wxPanel *m_Panel;
	wxBoxSizer *m_PanelSizer;
	wxArrayPtrVoid m_Panels;
	
	void New(wxString id, wxString name);
			
public:

	CCommunicationPanel(wxWindow *parent, wxWindow *top);
	~CCommunicationPanel();
	void OnNew(wxCommandEvent &event);
	void OnDelete(CCommunication *ptr);
	void OnEdit(CCommunication *ptr);
	wxArrayPtrVoid GetPanels();

	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_NEW = 8124,
	};

};

class CCommunication: public wxPanel
{
	wxWindow *m_Parent;
	CCommunicationPanel *m_BatteryPanel;
	wxBoxSizer *m_Sizer;
	wxPanel *m_Panel;
	wxStaticText *m_Name;
	
	void OnContextMenu(wxContextMenuEvent &event);
	void OnDelete(wxCommandEvent &event);
	void OnEdit(wxCommandEvent &event);

public:

	CCommunication(wxWindow *parent, CCommunicationPanel *panel);
	~CCommunication();
	void SetBatteryId(wxString v);
	void SetBatteryName(wxString v);

	
	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_DELETE = 8124,
		ID_EDIT,
	};

};



#endif