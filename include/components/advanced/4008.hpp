#pragma once

#include "components/AComponent.hpp"
#include "components/advanced/FullBitAdder.hpp"
#include <array>
#include <memory>

namespace nts {
    class Component4008 : public AComponent {
        public:
            Component4008();
            ~Component4008();

            nts::Tristate compute(std::size_t pin) override;

        private:
            std::array<std::unique_ptr<nts::FullBitAdder>, 4> _component_array;
    };
}
