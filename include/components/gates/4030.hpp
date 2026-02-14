#pragma once

#include "components/XorComponent.hpp"
#include "components/gates/AGatesComponent.hpp"

namespace nts {
    class Component4030 : public AGatesComponent<nts::XorComponent> {
        public:
            Component4030();
            ~Component4030();
    };
}
