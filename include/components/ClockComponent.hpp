#pragma once

#include "AComponent.hpp"

namespace nts {
    class ClockComponent : public AComponent {
        public:
            ClockComponent();
            ~ClockComponent();

            void setInternalState(nts::Tristate) override;
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;

        private:
            nts::Tristate _interiorState;
            std::size_t _tick;
    };
}
