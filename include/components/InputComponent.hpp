#pragma once

#include "AComponent.hpp"

namespace nts {
    class InputComponent : public AComponent {
        public:
            InputComponent();
            ~InputComponent();

            void setInternalState(nts::Tristate) override;
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;
        private:
            nts::Tristate _internalState;
    };
}
