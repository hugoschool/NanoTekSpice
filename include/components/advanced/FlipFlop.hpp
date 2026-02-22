#pragma once

#include "components/AComponent.hpp"

namespace nts {
    class FlipFlop : public AComponent {
        public:
            FlipFlop();
            ~FlipFlop();

            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t tick) override;

        private:
            nts::Tristate _previousClock;
            nts::Tristate _reversedState;
            nts::Tristate getReverseState();
    };
}
