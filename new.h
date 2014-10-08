#ifndef __NEW_H
#define __NEW_H

#include <wx/wx.h>

class CNew: public wxDialog
{
	int m_IdType;
	wxTextValidator m_TextValidator;
	wxTextCtrl *m_TextName;
	wxTextCtrl *m_TextInfo;
	wxTextCtrl *m_TextType;
	wxComboBox *m_ComboItemType;
	wxPanel *m_Panel;
	wxFlexGridSizer *m_FlexGridSizer;
	wxArrayPtrVoid m_Controls;

	void GetPanel(int type);

	wxPanel *EditNamePanel();
	wxPanel *EditTypePanel();
	wxPanel *EditItemPanel();
	wxPanel *LightPanel();
	
	wxComboBox *GetComboItemType(wxWindow *Parent);
	void GetItemFeaturePanel(wxWindow *Parent);
	void OnComboItem(wxCommandEvent &event);

	bool Validate();
		
public:

	CNew(int type, int id_type = -1);
	~CNew();
	wxString GetName();
	wxString GetInfo();
	wxString GetType();
	int GetItemType();

	void SetName(wxString v);
	void SetInfo(wxString v);
	void SetType(wxString v);
	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_ITEM_TYPE = 5224,
	};
	


};

#endif