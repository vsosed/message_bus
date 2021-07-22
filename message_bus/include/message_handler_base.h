#pragma once

#include "bus_addr.h"

namespace bus {

    struct MessageHandlerBase {
        virtual ~MessageHandlerBase() = default;
    };

} // namespace bus
