#pragma once

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>

namespace walle
{
class EventLoop;

class Channel : boost::noncopyable
{
public:
    typedef boost::function<void()> EventCallback;

    Channel(EventLoop* loop, int fd);

    void handleEvent();

    //�����¼��ص�
    void setReadCallback(const EventCallback& cb)
    { mReadCallback = cb; }
    void setWriteCallback(const EventCallback& cb)
    { mWriteCallback = cb; }
    void setErrorCallbck(const EventCallback& cb)
    { mErrorCallback = cb; }

    int fd() const { return mFd; }
    int events() const { return mEvents;}
    void setREvents(int revt){ mREvents = revt;}
    bool isNoneEvent() const { return mEvents == kNoneEvent;}
    void enableReading() { mEvents |= kReadEvent; update();}

    int index() { return mIndex;}
    void setIndex(int idx) { mIndex = idx;}

    EventLoop* ownerLoop() { return mLoop;}

private:
    void update();	//�����¼���Ϣ

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop* mLoop;
    const int mFd;	//�����Ψһfd
    int mEvents;	//��ע���¼�
    int mREvents;	//��ǰ��¼�
    int mIndex;		//Poller��

    EventCallback mReadCallback;
    EventCallback mWriteCallback;
    EventCallback mErrorCallback;
};

}//namespace walle
