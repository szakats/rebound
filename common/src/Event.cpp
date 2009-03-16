#include "common.h"

#include "Event.h"
#define eventScheduler EventScheduler::Instance()

void QuitEvent::Call()
{
    eventScheduler._quitEvent = true;
    delete this;
}

void QuitEvent::Quit(uint32 delay)
{
    static QuitEvent *event = new QuitEvent(delay);
}

PeriodicEvent::PeriodicEvent(uint32 delay, uint32 period)
{
    typedef EventScheduler::EventQueueType::value_type eventPair;
    eventScheduler._eventQueue.insert(eventPair(eventScheduler._now + delay, this));
    _delay = delay, _period = period;
}

void PeriodicEvent::_CallMe(EventScheduler::EventQueueType::iterator itr)
{
    eventScheduler._eventQueue.erase(itr);
    typedef EventScheduler::EventQueueType::value_type eventPair;
    eventScheduler._eventQueue.insert(eventPair(eventScheduler._now + _period, this));
    Call();
}

PeriodicEvent::~PeriodicEvent()
{

}

SingleEvent::SingleEvent(uint32 delay)
{
    typedef EventScheduler::EventQueueType::value_type eventPair;
    eventScheduler._eventQueue.insert(eventPair(eventScheduler._now + delay, this));
    _delay = delay;
}

void SingleEvent::_CallMe(EventScheduler::EventQueueType::iterator itr)
{
    eventScheduler._eventQueue.erase(itr);
    Call();
}