#ifndef __REBOUND_EVENT_H__
#define __REBOUND_EVENT_H__

#include "EventScheduler.h"

class Event
{
    friend class EventScheduler;
    public:
        virtual void Call() = 0;
        virtual ~Event() {}
    protected:
        virtual void _CallMe(EventScheduler::EventQueueType::iterator itr) = 0;
};

class PeriodicEvent : public Event
{
    public:
        PeriodicEvent(uint32 delay, uint32 period);
        ~PeriodicEvent();
    private:
        uint32 _delay, _period;
        void _CallMe(EventScheduler::EventQueueType::iterator itr);
};

class SingleEvent : public Event
{
    public:
        SingleEvent(uint32 delay);
    private:
        uint32 _delay;
        void _CallMe(EventScheduler::EventQueueType::iterator itr);
};

class Updatable
{
    public:
        virtual void Update() = 0;
};

class UpdateEvent : public PeriodicEvent
{
    public:
        UpdateEvent(uint32 delay, uint32 period, Updatable * updatable) : PeriodicEvent(delay, period), m_updatable(updatable) {}
        void Call() { m_updatable->Update(); }
    private:
        Updatable *m_updatable;
};

class QuitEvent : public SingleEvent
{
    public:
        static void Quit(uint32 delay);
        void Call();
    private:
        QuitEvent(uint32 delay) : SingleEvent(delay) {}
};

#endif // __REBOUND_EVENT_H__