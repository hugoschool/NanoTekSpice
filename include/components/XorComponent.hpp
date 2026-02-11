#pragma once

#include "AComponent.hpp"

namespace nts {
    class XorComponent : public AComponent {
        public:
            XorComponent();
            ~XorComponent();

            nts::Tristate compute(std::size_t pin) override;
    };
}
