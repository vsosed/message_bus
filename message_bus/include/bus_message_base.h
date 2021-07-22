#pragma once

#include "message_handler_base.h"

#include <list>
#include <atomic>
#include <memory>
//#include <future>

namespace bus {

class BusMessageBase {
    friend class BusClientBase;

    using Counter = std::atomic<int>;

public:
    using UPtr = std::unique_ptr<BusMessageBase>;

    BusMessageBase(const MsgAddress _from)
    : m_from{ _from } {}

    BusMessageBase(const BusMessageBase&) = delete;
    BusMessageBase& operator= (const BusMessageBase&) = delete;
    
    virtual ~BusMessageBase() = default;

    virtual void accept( const MsgAddress from, MessageHandlerBase& handler ) = 0;

    inline void unref() {
        if (0 == (--m_refCtr)) {
            delete this;
        }
    }

    inline void ref() {
        m_refCtr += 1;
    }

private:
    MsgAddress m_from;
    Counter m_refCtr = 1;
};


template<typename MsgHandlerType>
struct BusMessageImpl : public BusMessageBase {
    void accept(const MsgAddress from, MessageHandlerBase& handler) override {
        handler.handle(from, *this);
    }
};

/*template <typename ResponceType>
class BusCommandWithDefaultInitializedResponse : public IBusCommand {
public:
    ~BusCommandWithDefaultInitializedResponse() {
        if( !isResponceWasSet() ) {
            setResponce( {} );
        }
    }

    inline auto getFuture() {
        return m_promise.get_future();
    }

    inline void setResponce( ResponceType&& responce ) {
        m_promise.set_value( std::move( responce ) );
        m_isResponceWasSet = true;
    }

    template <typename... Args>
    inline void setResponce( Args&&... args ) {
        setResponce( ResponceType( std::forward<Args>( args )... ) );
        m_isResponceWasSet = true;
    }

    inline bool isResponceWasSet() const {
        return m_isResponceWasSet;
    }

private:
    std::promise<ResponceType> m_promise;
    bool m_isResponceWasSet = false;
};

template <typename ResponseType, const ResponseType& responceWasntSet>
class BusCommandResp : public BusCommandWithDefaultInitializedResponse<ResponseType> {
public:
    ~BusCommandResp() {
        if( !BusCommandWithDefaultInitializedResponse<ResponseType>::isResponceWasSet() ) {
            BusCommandWithDefaultInitializedResponse<ResponseType>::setResponce( responceWasntSet );
        }
    }
};*/

}  // namespace bus
