#include "conf.h"
#include "ticker.h"
#include "dll.h"

CTicker::CTicker(void *parent, int id)
#ifdef THREAD
#ifdef THREAD_JOINABLE
	:wxThread(wxTHREAD_JOINABLE) // (slow)
#endif
#endif
#ifdef TIMER
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
	_Working = true;
	if (this->Create() == wxTHREAD_NO_ERROR )
    {
		this->SetPriority(WXTHREAD_DEFAULT_PRIORITY);
        this->Run();
    }

}

void CTicker::Stop()
{
	_Stop = true;
	if(!IsDetached())
	{
		if(IsRunning())
			Wait();
	}
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

void CTicker::OnExit()
{
	_Working = false;
	fprintf(stderr,"Thread End\n");
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
		case TICK_DLL:			((CMapPlugin*)Parent)->OnTick();	break;
		case TICK_SYMBOL:		((CSymbol*)Parent)->OnTick();			break;
		
	}

}

bool CTicker::GetExit()
{
	return Exit;
}