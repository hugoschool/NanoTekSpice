#pragma once

#include "AComponent.hpp"

namespace nts {
    class NorComponent : public AComponent {
        public:
            NorComponent();
            ~NorComponent();

            nts::Tristate compute(std::size_t pin) override;
    };
}
