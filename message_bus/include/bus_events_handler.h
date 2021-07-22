#pragma once

#include "MsgAddress.h"

#include <string>

namespace bus {

struct EventsHandler {
    MsgAddress m_addr{ MsgAddressInvalid };
    std::string m_handlerName;
};

}  // namespace bus
