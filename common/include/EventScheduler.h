
#ifndef __REBOUND_EVENTSCHEDULER_H__
#define __REBOUND_EVENTSCHEDULER_H__

#include "Singleton.h"

class Event;

class EventScheduler : public Singleton<EventScheduler>
{
    friend class Event;
    friend class PeriodicEvent;
    friend class SingleEvent;
    friend class QuitEvent;

    public:
        EventScheduler();
        void Run();

    private:
        typedef std::multimap<uint32, Event*> EventQueueType;
        EventQueueType _eventQueue;
        bool _quitEvent;
        uint32 _now;
};

#endif // __REBOUND_EVENTSCHEDULER_H__