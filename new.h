#ifndef __NEW_H
#define __NEW_H

#include <wx/wx.h>
#include "picture.h"

class CNew: public wxDialog
{
	int m_IdType;
	wxTextValidator m_TextValidator;
	wxTextCtrl *m_TextName;
	wxTextCtrl *m_TextInfo;
	wxTextCtrl *m_TextType;
	wxComboBox *m_ComboItemType;
	wxComboBox *m_ComboFilterType;
	wxListBox *m_ListBox;
	wxPanel *m_Panel;
	wxFlexGridSizer *m_FlexGridSizer;
	wxArrayPtrVoid m_Controls,m_Ids;
	wxString m_ItemId;
	bool m_Edit;
	CPicturePanel *m_PicturePanel;

	void GetPanel(int type);

	wxPanel *EditNamePanel();
	wxPanel *EditTypePanel();
	wxPanel *EditItemPanel();
	wxPanel *EditPicturePanel();
	wxPanel *LightPanel();
	void LightItem();
	
	wxComboBox *GetComboItemType(wxWindow *Parent);
	void GetItemFeaturePanel(wxWindow *Parent);
	void OnComboItem(wxCommandEvent &event);
	void OnComboFilter(wxCommandEvent &event);
	bool Validate();
		
public:

	CNew(int type, int id_type = -1, wxString item_id = wxEmptyString, bool edit = false);
	~CNew();
	wxString GetName();
	wxString GetInfo();
	wxString GetType();
	int GetItemType();
	wxArrayPtrVoid GetFeatureControls();
	void SetName(wxString v);
	void SetInfo(wxString v);
	void SetType(wxString v);
	void SetItemTypeID(int v);
	void SetItemId(wxString v);
	wxImage GetImage();
	void SetImageId(wxString id);

	DECLARE_EVENT_TABLE();

	enum
	{
		ID_ITEM_TYPE = 5224,
		ID_FILTER,
	};
	


};

#endif