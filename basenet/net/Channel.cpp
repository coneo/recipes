#include "Channel.h"

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop* loop, int fd)
    : mLoop(loop),
      mFd(fd),
      mEvents(0),
      mREvents(0),
      mIndex(-1)
{
}

void Channel::update()
{
    mLoop->updateChannel(this);
}

void Channel::handleEvent()
{
    if (mREvents & POLLNVAL)
    {
	std::cout << "Channel::handleEvent() POLLNVAL" << std::endl;
    }

    if (mREvents & (POLLERR | POLLNVAL))
    {
	if (mErrorCallback) mErrorCallback();
    }
    if (mREvents & (POLLIN | POLLPRI | POLLRDHUP))
    {
	if (mReadCallback) mReadCallback();
    }
    if (mREvents & POLLOUT)
    {
	if (mWriteCallback) mWriteCallback();
    }
}
