#pragma once

#include "Tristate.hpp"
#include "components/AComponent.hpp"
#include <array>
#include <unordered_map>

namespace nts {
    class Component4094 : public nts::AComponent {
        public:
            Component4094();
            ~Component4094();

            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t tick) override;

        private:
            nts::Tristate _previousClock;

            std::size_t getPreviousPin(std::size_t pin);

            // 1st arg is pin, 2nd is output
            std::array<std::pair<std::size_t, std::size_t>, 8> _pinOutputArray;

            std::unordered_map<std::size_t, nts::Tristate> _storedMap;
            nts::Tristate storePin(std::size_t pin, nts::Tristate state);
            nts::Tristate getStoredPin(std::size_t pin);

    };
}
