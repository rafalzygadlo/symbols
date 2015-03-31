#include "conf.h"
#include "options.h"

wxColor m_BGColor;
wxColor m_FGColor;

//SET
void SetFGColor(wxColor v)			{	m_FGColor = v;			}
void SetBGColor(wxColor v)			{	m_BGColor = v;			}

//GET
wxColor GetBGColor()				{	return m_BGColor;		}
wxColor GetFGColor()				{	return m_FGColor;		}