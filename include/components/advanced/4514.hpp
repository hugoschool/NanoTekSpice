#pragma once

#include "components/AComponent.hpp"
#include <array>

namespace nts {
    class Component4514 : public AComponent {
        public:
            Component4514();
            ~Component4514();

            nts::Tristate compute(std::size_t pin) override;

        private:
            std::array<std::pair<std::size_t, uint8_t>, 16> _outputPins;

            uint8_t defineBinaryVal();
    };
}