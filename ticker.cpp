#include "conf.h"
#include "ticker.h"
#include "dll.h"

CTicker::CTicker(void *parent, int id)
#ifdef THREAD
	:wxThread(wxTHREAD_JOINABLE)
#endif
#ifdef TICKER
	:wxTimer()
#endif
{
	Exit = false;
	Parent = parent;
	Id = id;
}

CTicker::~CTicker()
{

}

#ifdef THREAD
void CTicker::Start(int sleep)
{
	
	_Sleep = sleep;
	_Stop = false;

	if (this->Create() == wxTHREAD_NO_ERROR )
    {
		this->SetPriority(WXTHREAD_DEFAULT_PRIORITY);
        this->Run();
    }

}

void CTicker::Stop()
{
	_Stop = true;
	if(IsRunning())
		Wait();
}
void *CTicker::Entry()
{
	while(1)
	{
		SendSignal();	
		Sleep(_Sleep);
		if(_Stop)
			break;
	}

	return 0;
}
#endif

#ifdef TIMER
void CTicker::Notify()
{
	SendSignal();
}
#endif

void CTicker::SendSignal()
{
	
	switch(Id)
	{
		case TICK_COMMAND:			((CMapPlugin*)Parent)->OnTickCommand();	break;
		case TICK_SYMBOL_BLINK:		((CSymbol*)Parent)->OnBlink();			break;
		case TICK_SYMBOL_COMMAND:	((CSymbol*)Parent)->OnCommand();			break;
	}

}

bool CTicker::GetExit()
{
	return Exit;
}