#include <iostream>
#include <stdio.h>
#include "event_queue_mgr.h"

int inde;
class Entry : public EventQueueMgr
{
    void parseEvent(stEvent* evt, int len) override
    {
        printf("dealevt:%d\n", evt->evttype);
        std::cout << "deal evt:" << evt->evttype << ":" << inde++ << std::endl;
    }
};

int main()
{
    Entry mgr;

    int msecs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    DieEvt evt;
    mgr.postEvent(&evt, sizeof(evt), msecs, 0);
    mgr.postEvent(&evt, sizeof(evt), msecs, 1);
    mgr.postEvent(&evt, sizeof(evt), msecs, 2);

//    while (true)
    {
        mgr.loop();
    }
}
