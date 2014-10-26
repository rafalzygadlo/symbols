#ifndef __LIGHT_H
#define __LIGHT_H

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/spinctrl.h>

class CLight;
class CLightPanel: public wxPanel
{
	wxWindow *m_Top;
	wxArrayPtrVoid m_List;
	void OnNew(wxCommandEvent &event);
	void AppendPanel();
	void RemovePanel(CLight *panel);
				
public:

	CLightPanel(wxWindow *top, wxWindow *parent);
	~CLightPanel();
	void Read(wxString query);
	wxArrayPtrVoid GetItems();
	//void _Layout();
	void OnDelete(CLight *panel);

	DECLARE_EVENT_TABLE();
	enum
	{
		ID_DELETE = 8124,
		ID_NEW,
		ID_EDIT,
	};
	
};

class CLight: public wxPanel
{
	int m_Counter;
	CLightPanel *m_ItemPanel;
	wxString m_Id;
	
	wxSpinCtrl *m_SectorTextFrom,*m_SectorTextTo;
	wxTextCtrl *m_CoverageText;
	
	void OnNew(wxCommandEvent &event);
	void OnDelete(wxCommandEvent &event);
	void AppendCombo();

public:

	CLight(CLightPanel *parent);
	~CLight();
	void _SetId(wxString v);
	void _SetName(wxString v);
	wxString _GetId();
	//void OnDelete(CComboPanel *panel);

	
	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_DELETE = 8124,
		ID_NEW,
		ID_EDIT,
	};

};

class CColorLight :public wxPanel
{
	
public:

	CColorLight(wxWindow *parent);
	void OnDClick(wxMouseEvent &event);
	void OnWindowEnter(wxMouseEvent &event);

	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_COLOR = 6323
	};

};

#endif