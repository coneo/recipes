#ifndef _EVENT_H
#define _EVENT_H

#pragma pack(1)

enum EvtType
{
    EvtType_None                = 0,
    EvtType_PlayerDie           = 1,    // 角色死亡
    EvtType_Max,
};

struct stEvent
{
    stEvent() = delete;
    stEvent(int type_): evttype(type_)
    {
    }

    // 事件类型
    int evttype = 0;
};

struct DieEvt : public stEvent
{
    DieEvt():stEvent(EvtType_PlayerDie)
    {
    }
};

#endif // _EVENT_H
