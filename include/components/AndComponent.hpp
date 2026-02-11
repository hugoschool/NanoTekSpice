#pragma once

#include "AComponent.hpp"

namespace nts {
    class AndComponent : public AComponent {
        public:
            AndComponent();
            ~AndComponent();

            nts::Tristate compute(std::size_t pin) override;
    };
}
