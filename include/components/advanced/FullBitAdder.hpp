#pragma once

#include "components/AComponent.hpp"
#include "components/AndComponent.hpp"
#include "components/OrComponent.hpp"
#include "components/XorComponent.hpp"
#include <memory>
#include <array>

namespace nts {
    class FullBitAdder : public AComponent {
        public:
            FullBitAdder();
            ~FullBitAdder();

            nts::Tristate compute(std::size_t pin) override;
        private:
            std::array<std::shared_ptr<nts::AndComponent>, 2> _and_components;
            std::array<std::shared_ptr<nts::XorComponent>, 2> _xor_components;
            std::unique_ptr<nts::OrComponent> _or_component;
    };
}
