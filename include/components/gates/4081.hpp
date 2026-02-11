#pragma once

#include "components/AComponent.hpp"
#include "components/AndComponent.hpp"
#include <array>
#include <memory>

namespace nts {
    class Component4081 : public AComponent {
        public:
            Component4081();
            ~Component4081();

            nts::Tristate compute(std::size_t pin) override;

        private:
            std::array<std::unique_ptr<nts::AndComponent>, 4> _component_array;
    };
}
