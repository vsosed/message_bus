#pragma once

#include <cstdint>
#include <list>
#include <map>
#include <set>
#include <memory>
#include <chrono>
#include <future>

#include "bus_addr.h"
#include "bus_message_base.h"
#include "bus_client.h"

namespace bus {

    using AddrSet = std::set<BusClientBase*>;
    
    AddrSet getClientsByGroupAddr( const MsgAddress addr );

    //BusClientBase* getClientByAddr( const MsgAddress addr );

    bool join( const MsgAddress addr, BusClientBase& client );

    void leave( BusClientBase& client);

    bool leave( const MsgAddress addr, BusClientBase& client );

    bool send(const MsgAddress destination, BusMessageBase::UPtr message);

    /*template <typename CmdType, typename AddrType, typename... Args>
    inline void send( const AddrType to, Args&&... args ) const {
        auto cmd = std::make_unique<CmdType>( std::forward<Args>( args )... );
        send( to, std::move( cmd ) );
    }

    template <typename CmdType, typename AddrType, typename... Args>
    inline auto asyncSend( const AddrType to, Args&&... args ) const {
        auto cmd = std::make_unique<CmdType>( std::forward<Args>( args )... );
        auto future = cmd->getFuture();
        send( to, std::move( cmd ) );
        return future;
    }

    template <typename CmdType, typename AddrType, typename DelayType, typename... Args>
    auto waitToResp( const AddrType to, const DelayType timeout, Args&&... args ) const {
        auto result = asyncSend<CmdType>( to, std::forward<Args>( args )... );
        auto statusOfResult = result.wait_for( timeout );
        if( statusOfResult != std::future_status::ready ) {
            return CmdType::createExecTimeoutErrorResult();
        }
        return result.get();
    }

    template <typename CmdType, typename AddrType, typename... Args>
    auto waitResp( const AddrType to, Args&&... args ) const {
        auto result = asyncSend<CmdType>( to, std::forward<Args>( args )... );
        result.wait();
        return result.get();
    }*/

    /*bool sendFromNowhere(const MsgAddress to, std::unique_ptr<IBusCommand>&& msg);

    bool sendFromNowhere( const char* to, std::unique_ptr<IBusCommand>&& msg );

    template <typename CmdType, typename AddrType, typename... Args>
    inline bool sendFromNowhere( const AddrType to, Args&&... args ) {
        auto cmd = std::make_unique<CmdType>( std::forward<Args>( args )... );
        return cmd && sendFromNowhere( to, std::move( cmd ) );
    }

    template <typename CmdType, typename AddrType, typename... Args>
    inline auto sendFromNowhereAsync( const AddrType to, Args&&... args ) {
        auto cmd = std::make_unique<CmdType>( std::forward<Args>( args )... );
        auto future = cmd->getFuture();
        sendFromNowhere( to, std::move( cmd ) );
        return future;
    }

    template <typename CmdType, typename AddrType, typename DelayType, typename... Args>
    auto waitToResp( const AddrType to, const DelayType timeout, Args&&... args ) {
        auto cmd = std::make_unique<CmdType>( std::forward<Args>( args )... );
        auto result = cmd->getFuture();
        if( !sendFromNowhere( to, std::move( cmd ) ) ) {
            return CmdType::createExecTimeoutErrorResult();
        }

        const auto statusOfResult = result.wait_for( timeout );
        return statusOfResult == std::future_status::ready ? result.get() : CmdType::createExecTimeoutErrorResult();
    }

    template <typename CmdType, typename AddrType, typename... Args>
    auto waitResp( const AddrType to, Args&&... args ) {
        auto cmd = std::make_unique<CmdType>( std::forward<Args>( args )... );
        auto result = cmd->getFuture();
        if( sendFromNowhere( to, std::move( cmd ) ) ) {
            result.wait();
        }
        return result.get();
    }*/

}  // namespace bus
