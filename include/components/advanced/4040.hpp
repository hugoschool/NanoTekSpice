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
            const std::unordered_map<std::size_t, std::size_t> _pinToIndexMap;
    };
}
