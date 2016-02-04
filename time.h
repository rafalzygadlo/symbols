#ifndef __TIME
#define __TIME

#include <wx/wx.h>
#include <wx/wrapsizer.h>

class CTime;
class CTimePanel: public wxPanel
{
	void *m_DB;
	wxWindow *m_Top;
	wxArrayPtrVoid m_List;
	wxTextCtrl *m_CharacteristicText;
	wxBoxSizer *m_Sizer;

	void OnNew(wxCommandEvent &event);
	void RemovePanel(CTime *panel);
				
public:

	CTimePanel(void *db,wxWindow *top, wxWindow *parent);
	~CTimePanel();
	void Read(wxString query);
	wxArrayPtrVoid GetItems();
	void OnDelete(CTime *panel);
	void OnNewSector();
	void OnDeleteSector();
	void AppendPanel(CTime *panel);
	
	size_t GetCount();
	CTime *GetTime(int id);


	DECLARE_EVENT_TABLE();
	enum
	{
		ID_DELETE = 2700,
		ID_NEW,
		ID_EDIT,
	};
	
};

class CTime: public wxPanel
{
	CTimePanel *m_Panel;
	wxString m_Id;
	wxTextCtrl *m_TextOn;
	wxTextCtrl *m_TextOff;
		
	void OnNew(wxCommandEvent &event);
	void OnDelete(wxCommandEvent &event);
	
public:

	CTime(CTimePanel *parent);
	~CTime();
		
	wxString _GetId();
	float GetOn();
	float GetOff();


	void _SetId(wxString v);
	void SetOn(float v);
	void SetOff(float v);
	

		
	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_DELETE = 2800,
		ID_NEW,
		
	};

};


#endif