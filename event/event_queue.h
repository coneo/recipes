#pragma once

#include <list>
#include <chrono>
#include "event.h"

class EventQueue
{
public:
    struct Evt
    {
        int settime = 0;
        int delay = 0;
        int len = 0;
        char data[0];
    };

    void put(stEvent* evt, int len, long time, int delay);

    bool empty() { return _evts.empty(); }

    bool ready();

    void getfront(stEvent*& retevt, int& retlen);

    void popfront();

    void erase();

    void copyfront(EventQueue& queue);

    Evt* front(){ return _evts.front(); }

private:
    std::list<Evt*> _evts;
};

inline void EventQueue::put(stEvent* evt, int len, long time, int delay)
{
    Evt* nevt = (Evt*)new char[len + sizeof(Evt)];
    nevt->settime = time;
    nevt->delay = delay;
    nevt->len = len;
    bcopy(evt, nevt->data, len);
    _evts.push_back(nevt);
}

inline bool EventQueue::ready()
{
    if (_evts.empty()) return false;

    Evt* evt = _evts.front();
    int msecs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    if (msecs >= evt->settime + evt->delay)
        return true;
    return false;
}

inline void EventQueue::getfront(stEvent*& retevt, int& retlen)
{
    if (_evts.empty()) return ;

    Evt* evt = _evts.front();
    retevt = (stEvent*)(evt->data);
    retlen = evt->len;
}

inline void EventQueue::popfront()
{
    _evts.pop_front();
}

inline void EventQueue::erase()
{
    if (_evts.empty()) return ;

    char* evt = (char*)(_evts.front());
    _evts.pop_front();
    if (evt) delete [] evt;
}

inline void EventQueue::copyfront(EventQueue& from)
{
    if (from.empty()) return ;

    Evt* evt = from.front();
    _evts.push_back(evt);
}
