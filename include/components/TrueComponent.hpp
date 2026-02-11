#pragma once

#include "AComponent.hpp"

namespace nts {
    class TrueComponent : public AComponent {
        public:
            TrueComponent();
            ~TrueComponent();

            nts::Tristate compute(std::size_t pin) override;
    };
}
