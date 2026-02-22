#pragma once

#include "components/AComponent.hpp"
#include "components/advanced/FlipFlop.hpp"
#include <array>
#include <memory>

namespace nts {
    class Component4013 : public AComponent {
        public:
            Component4013();
            ~Component4013();

            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t tick) override;

        private:
            std::array<std::unique_ptr<nts::FlipFlop>, 2> _array;
    };
}
