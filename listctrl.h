#ifndef __LIST
#define __LIST

#include <wx/wx.h>
#include <wx/listctrl.h>


class CDisplayPlugin;
class CAisList;
class CListCtrl: public wxListCtrl
{
	wxArrayPtrVoid m_ColumnArray;
	wxArrayString m_DataArray;
	wxArrayInt m_ColumnIds;
	wxArrayString m_ColumnFields;
	int m_FieldCount;
	wxMenu *m_Menu;
	int m_ControlType;
	void *m_Control;
	int m_SelectedItem;
	int m_ColumnWithId;
	wxImageList *m_ImageListSmall;
	
	wxMenu *MenuArea(int id);
		
	void Sort();
	void NewUser();
	void NewGroup();
	wxArrayString *GetColumn(int column);
	wxString GetValue(wxArrayString *ptr, int record);

	
	void OnActivate(wxListEvent &event);
	void OnSelected(wxListEvent &event);
	void OnContextMenu(wxContextMenuEvent &event);
	void OnColClick(wxListEvent &event);
	void OnEdit(wxCommandEvent &event);
	void OnDelete(wxCommandEvent &event);
	void OnNew(wxCommandEvent &event);
	void OnProperties(wxCommandEvent &event);
	void OnChangePassword(wxCommandEvent &event);
	void OnRight(wxCommandEvent &event);
	void OnChangeGroup(wxCommandEvent &event);
	
	wxString OnGetItemText(long item, long column) const;
	//wxListItemAttr *OnGetItemAttr(long item) const;
	int OnGetItemColumnImage(long item, long column) const; 
	int OnGetItemImage(long item) const;

public:
	
		
	CListCtrl( wxWindow *Parent, int style );
	~CListCtrl();

	void SetControlType(int id, void *ptr);
	void _AddColumn(int id,wxString field_name);
	void InitColumns();
	void Clear();
	void Select();
	void Read(wxString query);
	void SetColumnWithId(int id);
	void SetColumnImage(int col, int image);

	DECLARE_EVENT_TABLE();

	enum
	{
		ID_LIST,
		ID_DELETE,
		ID_EDIT,
		ID_NEW,
		ID_PROPERTIES,
		ID_CHANGE_PASSWORD,
		ID_GROUP,
		ID_RIGHT,
		
	};

};



#endif