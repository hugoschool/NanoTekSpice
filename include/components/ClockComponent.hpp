#pragma once

#include "AComponent.hpp"

namespace nts {
    class ClockComponent : public AComponent {
        public:
            ClockComponent();
            ~ClockComponent();

            void store(nts::Tristate);
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;

        private:
            nts::Tristate _interiorState;
            std::size_t _tick;
    };
}
