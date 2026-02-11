#pragma once

#include "AComponent.hpp"

namespace nts {
    class NandComponent : public AComponent {
        public:
            NandComponent();
            ~NandComponent();

            nts::Tristate compute(std::size_t pin) override;
    };
}
