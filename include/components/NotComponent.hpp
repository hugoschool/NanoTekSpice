#pragma once

#include "AComponent.hpp"

namespace nts {
    class NotComponent : public AComponent {
        public:
            NotComponent();
            ~NotComponent();

            nts::Tristate compute(std::size_t pin) override;
    };
}
