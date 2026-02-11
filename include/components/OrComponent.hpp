#pragma once

#include "AComponent.hpp"

namespace nts {
    class OrComponent : public AComponent {
        public:
            OrComponent();
            ~OrComponent();

            nts::Tristate compute(std::size_t pin) override;
    };
}
