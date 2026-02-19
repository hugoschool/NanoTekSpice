#pragma once

#include "components/AComponent.hpp"

namespace nts {
    class Component4013 : public AComponent {
        public:
            Component4013();
            ~Component4013();

            nts::Tristate compute(std::size_t pin) override;
    };
}
