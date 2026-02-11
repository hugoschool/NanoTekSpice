#pragma once

#include "../AComponent.hpp"
#include "components/XorComponent.hpp"
#include <array>
#include <memory>

namespace nts {
    class Component4030 : public AComponent {
        public:
            Component4030();
            ~Component4030();

            nts::Tristate compute(std::size_t pin) override;

        private:
            std::array<std::unique_ptr<nts::XorComponent>, 4> _component_array;
    };
}
