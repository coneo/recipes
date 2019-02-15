#pragma once

#include "event_queue.h"

class EventQueueMgr
{
public:
    void postEvent(stEvent* evt, int len, long time, int delay);

    void loop();

    // 事件处理
    virtual void parseEvent(stEvent* evt, int len) = 0;

private:
    void swap();

private:
    // 前端队列，生产事件
    EventQueue _front_queue;

    // 后端队列，消耗事件
    EventQueue _back_queue;
};

inline void EventQueueMgr::postEvent(stEvent* evt, int len, long time, int delay)
{
    _front_queue.put(evt, len, time, delay);
}

inline void EventQueueMgr::swap()
{
    stEvent* evt = nullptr;
    int evtlen = 0;
    while (!_front_queue.empty())
    {
        _back_queue.copyfront(_front_queue);
        _front_queue.popfront();
    }
}

inline void EventQueueMgr::loop()
{
    if (_front_queue.empty())
        return ;

    stEvent* evt = nullptr;
    int evtlen = 0;

    swap();
    while (_back_queue.ready())
    {
        _back_queue.getfront(evt, evtlen);
        parseEvent(evt, evtlen);
        _back_queue.erase();
    }
}
