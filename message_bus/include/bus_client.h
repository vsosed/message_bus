#pragma once

#include "bus_message_base.h"

#include <list>
#include <mutex>
#include <chrono>

namespace bus {

class BusClientBase : public MessageHandlerBase {
protected:
    BusClientBase();

public:
    ~BusClientBase() override {
        leaveBus();
    }

    void leaveBus();
    
    inline auto addr() const {
        return m_addr;
    }

    void putMessage(BusMessageBase* message);

    bool pumpMessages();

    //void tryReceive( std::chrono::milliseconds delay );

    //bool tryReceiveSingleMessage( std::chrono::milliseconds delay );

private:
    virtual void receive( const MsgAddress from, BusMessageBase& msg ) {
        msg.accept( from, *this );
    }

private:
    const MsgAddress m_addr;
    
    std::mutex                 m_queueMutex;
    std::list<BusMessageBase*> m_queue;
};

}  // namespace bus
