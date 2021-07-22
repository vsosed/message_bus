#include "bus.h"

#include <algorithm>
#include <functional>
#include <shared_mutex>


namespace bus {

    using AddrToGroup  = std::map<MsgAddress, AddrSet>;
    using AddrToClient = std::map<MsgAddress, BusClientBase*>;

    namespace {
        std::shared_mutex g_addrToGroupMutex;
        AddrToGroup       g_addrToGroup;
    } // unnamed namespace


    bool join( const MsgAddress addr, BusClientBase& client) {
        std::unique_lock lock(g_addrToGroupMutex);

        auto& group = g_addrToGroup[addr];
        group.emplace( &client );
        return true;
    }

    void leave( BusClientBase& client ) {
        std::unique_lock lock(g_addrToGroupMutex);
        for (auto& pair : g_addrToGroup) {
            pair.second.erase(&client);
        }
    }

    bool leave(const MsgAddress addr, BusClientBase& client) {
        std::unique_lock lock(g_addrToGroupMutex);

        auto& group = g_addrToGroup[addr];
        group.erase( &client );

        return true;
    }

    AddrSet getClientsByGroupAddr(const MsgAddress addr) {
        std::shared_lock lock(g_addrToGroupMutex);

        auto itr = g_addrToGroup.find( addr );
        return g_addrToGroup.end() != itr ? itr->second : AddrSet{};
    }

    bool sendToClients(const MsgAddress destination, BusMessageBase::UPtr message) {
        auto raw = message.release();
        
        auto clients = getClientsByGroupAddr(destination);
        for (auto client : clients) {
            client->putMessage(raw);
        }
        
        message->unref();

        return true;
    }

    bool send(const MsgAddress destination, BusMessageBase::UPtr message) {
        return message ? sendToClients(destination, std::move(message)) : false;
    }

    /*bool sendFromNowhere(const MsgAddress to, std::unique_ptr<IBusCommand>&& msg) {
        if( MsgAddressInvalid == to || !msg ) {
            constexpr auto depth = 100;
            esp_backtrace_print( depth );
            return false;
        }

        msg->setFromTo( MsgAddressInvalid, to );
        IBusClient::sendToClients( to, std::move( msg ) );
        return true;
    }

    bool sendFromNowhere( const char* to, std::unique_ptr<IBusCommand>&& msg ) {
        msg->isGroup = true;
        return sendFromNowhere( Bus::get().nameToAddr( to ), std::move( msg ) );
    }*/

}  // namespace bus
