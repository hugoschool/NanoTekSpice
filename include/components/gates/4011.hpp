#pragma once

#include "../AComponent.hpp"
#include "components/NandComponent.hpp"
#include <array>
#include <memory>

namespace nts {
    class Component4011 : public AComponent {
        public:
            Component4011();
            ~Component4011();

            nts::Tristate compute(std::size_t pin) override;

        private:
            std::array<std::unique_ptr<nts::NandComponent>, 4> _component_array;
    };
}
