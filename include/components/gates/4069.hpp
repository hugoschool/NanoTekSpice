#pragma once

#include "../AComponent.hpp"
#include "components/NotComponent.hpp"
#include <array>
#include <memory>

namespace nts {
    class Component4069 : public AComponent {
        public:
            Component4069();
            ~Component4069();

            nts::Tristate compute(std::size_t pin) override;

        private:
            std::array<std::unique_ptr<nts::NotComponent>, 6> _component_array;
    };
}
