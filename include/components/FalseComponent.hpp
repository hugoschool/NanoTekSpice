#pragma once

#include "AComponent.hpp"

namespace nts {
    class FalseComponent : public AComponent {
        public:
            FalseComponent();
            ~FalseComponent();

            nts::Tristate compute(std::size_t pin) override;
    };
}
