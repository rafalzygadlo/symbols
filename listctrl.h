#ifndef __LIST
#define __LIST

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "dialog.h"
#include "symbol.h"

class CDisplayPlugin;
class CDialog;
class CDialogPanel;
class CSymbol;
class CListCtrl: public wxListCtrl
{
	CListCtrl *m_ThisPtr;
	wxArrayPtrVoid *m_List;
	wxFont m_Font;
	int m_Count;
	void *m_DB;
	wxArrayPtrVoid m_ColumnArray;
	wxArrayPtrVoid m_DataArray;
	wxArrayInt m_ColumnIds;
	wxArrayInt m_Ids;
	wxArrayString m_ColumnFields;
	int m_FieldCount;
	wxMenu *m_Menu;
	int m_ControlType;
	CDialogPanel *m_Control;
	int m_SelectedItem;
	int m_ColumnWithId,m_ColumnWithName;
	wxImageList *m_ImageListSmall;
	wxArrayInt m_Checked;
	wxListItemAttr *m_ListAttr;
	
	wxMenu *Menu(int id, int id_module);
	wxMenu *MenuSymbol(int id, int id_module);
	wxMenu *MenuSBMS(int id, int id_module);
	wxMenu *MenuSymbolItem(int id, int id_module);
	wxMenu *MenuBaseStation(int id, int id_module);

	void Sort();
	void NewUser();
	void NewGroup();
	wxArrayString *_GetColumn(int column);
	wxArrayString *_GetDataColumn(int column);
	wxArrayString GetRow(int row);
	wxString GetValue(wxArrayString *ptr, int record);
	bool IsChecked(long id);
	void SetChecked(long id, bool checked);

	void SetSBMSAttr(long item, wxListItemAttr *v);
	void SetSymbolAttr(long item, wxListItemAttr *v);

	void SetFontBold(bool v);
	
	void OnActivate(wxListEvent &event);
	void OnSelected(wxListEvent &event);
	void OnContextMenu(wxContextMenuEvent &event);
	void OnColClick(wxListEvent &event);
	void OnEdit(wxCommandEvent &event);
	void OnDelete(wxCommandEvent &event);
	void OnAddToGroup(wxCommandEvent &event);
	void OnNew(wxCommandEvent &event);
	void OnProperties(wxCommandEvent &event);
	void OnChangePassword(wxCommandEvent &event);
	void OnRight(wxCommandEvent &event);
	void OnChangeGroup(wxCommandEvent &event);
	void OnMouseEvent(wxMouseEvent& event);
	void OnPaint(wxPaintEvent &event);
	
	
	wxString OnGetItemText(long item, long column) const;
	wxListItemAttr *OnGetItemAttr(long item) const;
	//int OnGetItemColumnImage(long item, long column) const; 
	int OnGetItemImage(long item) const;

public:
	
		
	CListCtrl(void *db, wxWindow *Parent, int style );
	~CListCtrl();

	void SetControlType(int id, CDialogPanel *control);
	void _AddColumn(int id,wxString field_name);
	void InitColumns();
	void Clear();
	void Select();
	void Read(wxString query);
	void SetColumnWithId(int id);
	void SetColumnWithName(int id);
	void SetColumnImage(int col, int image);
	void SetList(wxArrayPtrVoid *ptr);
	void SetSelection(CSymbol *ptr);

	DECLARE_EVENT_TABLE();

	enum
	{
		ID_LIST = 2100,
		ID_DELETE,
		ID_EDIT,
		ID_NEW,
		ID_PROPERTIES,
		ID_CHANGE_PASSWORD,
		ID_GROUP,
		ID_RIGHT,
		ID_ADD_TO_GROUP,
		ID_ADD_TO_SYMBOL,
	};

};



#endif