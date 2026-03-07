#pragma once

#include "Tristate.hpp"
#include "components/AComponent.hpp"
#include "utils/ShiftContainer.hpp"
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
            const std::unordered_map<std::size_t, std::size_t> _pinOutputMap;
            nts::ShiftContainer<8> _shiftContainer;
            bool _hasShifted;
            std::array<nts::Tristate, 2> _serialOutputs;

            void setStateFromShiftContainer(std::size_t pin);
    };
}
