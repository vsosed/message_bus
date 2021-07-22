#include "bus_client.h"
#include "bus.h"


namespace bus {

BusClientBase::BusClientBase() {
    bus::join( addr(), *this );
}

void BusClientBase::leaveBus() {
    bus::leave( *this );

    m_queueMutex.lock();
    for( auto msgPtr : m_queue) {
        msgPtr->unref();
    }
}

void BusClientBase::putMessage(BusMessageBase* message) {
    std::lock_guard lock(m_queueMutex);
    m_queue.push_back(message);
}

bool BusClientBase::pumpMessages() {
    decltype(m_queue) messages;
    {
        std::lock_guard lock(m_queueMutex);
        messages = std::move(m_queue);
    }

    for (auto msgPtr : m_queue) {
        receive(msgPtr->m_from, *msgPtr);
        msgPtr->unref();
    }

    return false;
}

/*void BusClientBase::tryReceive(TickType_t waitTime) {
    BusMsg* raw;
    while( pdTRUE == xQueueReceive( queue(), (void*)&raw, (portTickType)waitTime ) ) {
        receive( raw->from, raw->to, *raw );
        raw->unref();
    }
}*/

/*bool BusClientBase::tryReceiveSingleMessage(TickType_t waitTime) {
    BusMsg* raw;
    if( pdTRUE != xQueueReceive( queue(), (void*)&raw, (portTickType)waitTime ) ) {
        return false;
    }

    receive( raw->from, raw->to, *raw );
    raw->unref();
    return true;
}*/

}  // namespace bus
