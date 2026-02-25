#pragma once

#include "Tristate.hpp"
#include "components/AComponent.hpp"

namespace nts {
    class Component4512 : public AComponent {
        public:
            Component4512();
            ~Component4512();

            nts::Tristate compute(std::size_t pin) override;
        private:
            nts::Tristate decide_state();
    };
}