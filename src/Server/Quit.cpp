//
// Created by chaed on 19. 2. 6.
//

#include "Quit.h"
#include  <ace/OS.h>

using namespace server;

Quit::Quit(ACE_Reactor* reactor)
        : ACE_Event_Handler(reactor)
{
    this->reactor()->register_handler(0, this);
}

Quit::~Quit(void)
{
}

int
Quit::handle_signal(int signum, siginfo_t* /*= 0*/, ucontext_t* /*= 0*/)
{
    this->reactor()->notify(this);
    ACE_OS::sleep(2);
    return 0;
}

int
Quit::handle_exception(ACE_HANDLE fd/* = ACE_INVALID_HANDLE*/)
{
    this->reactor()->end_reactor_event_loop();
    return -1;
}

int
Quit::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask)
{
    ACE_Reactor_Mask m = ACE_Event_Handler::ALL_EVENTS_MASK | ACE_Event_Handler::DONT_CALL;
    this->reactor()->remove_handler(this, m);
    delete this;
    return 0;
}