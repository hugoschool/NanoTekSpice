#pragma once

#include "components/AComponent.hpp"

namespace nts {
    class FlipFlop : public AComponent {
        public:
            FlipFlop();
            ~FlipFlop();

            nts::Tristate compute(std::size_t pin) override;
            nts::Tristate computeReverse();
            void simulate(std::size_t tick) override;
            nts::Tristate getReverseState();

        private:
            nts::Tristate _previousClock;
            nts::Tristate _reversedState;
    };
}
