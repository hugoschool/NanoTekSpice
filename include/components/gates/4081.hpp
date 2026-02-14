#pragma once

#include "components/AndComponent.hpp"
#include "components/gates/AGatesComponent.hpp"

namespace nts {
    class Component4081 : public AGatesComponent<nts::AndComponent> {
        public:
            Component4081();
            ~Component4081();
    };
}
