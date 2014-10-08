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
	wxTextCtrl *m_TextCapacity;
	wxTextCtrl *m_TextFlash;
	wxTextCtrl *m_TextVoltage;
	wxTextCtrl *m_TextPower;
	wxComboBox *m_ComboItemType;
	wxPanel *m_FeaturePanel;
	wxBoxSizer *m_ItemSizer;

	void GetPanel(int type);

	wxPanel *EditNamePanel();
	wxPanel *EditTypePanel();
	wxPanel *EditItemPanel();
	wxPanel *LightPanel();
	
	wxComboBox *GetComboItemType(wxWindow *Parent);
	wxPanel *GetItemFeaturePanel(wxWindow *Parent);
	void OnComboItem(wxCommandEvent &event);

	bool Validate();
		
public:

	CNew(int type, int id_type = -1);
	~CNew();
	wxString GetName();
	wxString GetInfo();
	wxString GetType();
	wxString GetCapacity();
	wxString GetVoltage();
	wxString GetPower();
	int GetItemType();

	void SetName(wxString v);
	void SetInfo(wxString v);
	void SetType(wxString v);
	void SetCapacity(wxString v);
	void SetVoltage(wxString v);
	void SetPower(wxString v);

	DECLARE_EVENT_TABLE();

	enum
	{
		ID_ITEM_TYPE = 5224,
	};
	


};

#endif