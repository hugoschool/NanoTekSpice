#pragma once

#include "Tristate.hpp"
#include "components/AComponent.hpp"

namespace nts {
    class Component4040 : public nts::AComponent {
        public:
            Component4040();
            ~Component4040();

            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t tick) override;

        private:
            nts::Tristate _previousClock;
            std::size_t _clockCycle;
            std::unordered_map<std::size_t, nts::Tristate> _storedMap;

            nts::Tristate storePin(std::size_t pin, nts::Tristate state);
            nts::Tristate getStoredPin(std::size_t pin);
            bool isPowerOfTwo(std::size_t nb);
    };
}
