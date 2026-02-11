#pragma once

#include "AComponent.hpp"

namespace nts {
    class InputComponent : public AComponent {
        public:
            InputComponent();
            ~InputComponent();

            void store(nts::Tristate);
            nts::Tristate compute(std::size_t pin) override;
        private:
            nts::Tristate _state;
    };
}
