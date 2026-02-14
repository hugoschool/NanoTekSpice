#pragma once

#include "components/NandComponent.hpp"
#include "components/gates/AGatesComponent.hpp"

namespace nts {
    class Component4011 : public AGatesComponent<nts::NandComponent> {
        public:
            Component4011();
            ~Component4011();
    };
}
