#pragma once

#include "../AComponent.hpp"
#include "components/NorComponent.hpp"
#include <array>
#include <memory>

namespace nts {
    class Component4001 : public AComponent {
        public:
            Component4001();
            ~Component4001();

            nts::Tristate compute(std::size_t pin) override;

        private:
            std::array<std::unique_ptr<nts::NorComponent>, 4> _component_array;
    };
}
