#pragma once

#include "components/NorComponent.hpp"
#include "components/gates/AGatesComponent.hpp"

namespace nts {
    class Component4001 : public AGatesComponent<nts::NorComponent> {
        public:
            Component4001();
            ~Component4001();
    };
}
