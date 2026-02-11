#pragma once

#include "AComponent.hpp"

namespace nts {
    class OutputComponent : public AComponent {
        public:
            OutputComponent();
            ~OutputComponent();

            nts::Tristate compute(std::size_t pin) override;
    };
}
