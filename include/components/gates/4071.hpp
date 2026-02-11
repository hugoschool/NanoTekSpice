#pragma once

#include "../AComponent.hpp"
#include "components/OrComponent.hpp"
#include <array>
#include <memory>

namespace nts {
    class Component4071 : public AComponent {
        public:
            Component4071();
            ~Component4071();

            nts::Tristate compute(std::size_t pin) override;

        private:
            std::array<std::unique_ptr<nts::OrComponent>, 4> _component_array;
    };
}
