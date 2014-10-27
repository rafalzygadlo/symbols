#ifndef __LIGHT_H
#define __LIGHT_H

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/spinctrl.h>

class CLight;
class CSectorPanel;
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
	void OnDelete(CLight *panel);
	void OnNewSector();
	void OnDeleteSector();

	size_t GetCount();
	CLight *GetLight(int id);


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
	wxArrayPtrVoid m_Sectors;
	wxSpinCtrl *m_CoverageText;
	wxStaticBoxSizer *m_SectorSizer;
	
	void OnNewSector(wxCommandEvent &event);
	//void OnDeleteSector(wxCommandEvent &event);
	void OnDelete(wxCommandEvent &event);
	wxPanel *GetSectorPanel(wxWindow *parent, bool _add = true);

public:

	CLight(CLightPanel *parent);
	~CLight();
	void _SetId(wxString v);
	void _SetName(wxString v);
	wxString _GetId();
	wxColor GetColor();
	void OnDeleteSector(CSectorPanel *panel);
	//void OnDelete(CComboPanel *panel);

	
	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_DELETE = 8124,
		ID_NEW_SECTOR,
		
	};

};

class CColorLight :public wxPanel
{
	
public:

	CColorLight(wxWindow *parent);
	void OnClick(wxMouseEvent &event);
	void OnWindowEnter(wxMouseEvent &event);

	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_COLOR = 6323
	};

};

class CSectorPanel :public wxPanel
{
	CLight *m_Light;
	wxSpinCtrl *m_SectorTextFrom,*m_SectorTextTo;

	void OnDelete(wxCommandEvent &event);

public:
	CSectorPanel(CLight *parent, bool _add = false);
	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_DELETE,
	};
};


#endif