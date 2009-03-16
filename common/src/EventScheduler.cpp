#include "common.h"

#include "Event.h"

EventScheduler::EventScheduler()
{
    _quitEvent = false;
    _now = GetTickCount();
}

void EventScheduler::Run()
{
    while(!_quitEvent && !_eventQueue.empty())
    {
        EventQueueType::iterator itr = _eventQueue.begin();
        // todo: uint32 may overflow
        if(itr->first > _now) Sleep(itr->first - _now);
        _now = itr->first;
        // itr may be invalidated by _CallMe
        itr->second->_CallMe(itr);
        // we don't know how long _CallMe takes
        _now = GetTickCount();
    }
}
