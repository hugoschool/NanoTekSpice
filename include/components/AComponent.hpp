#pragma once

#include "Pins.hpp"
#include "components/IComponent.hpp"
#include <cstddef>

namespace nts {
    class AComponent : public IComponent {
        public:
            AComponent();
            ~AComponent();

            void simulate(std::size_t tick) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
            nts::Tristate getLink(std::size_t pin);
            void setState(Tristate state) override;
            Tristate getState() const override;

            void setPinState(std::size_t pin, nts::Tristate state) override;

        protected:
            Pins _pins;
            Tristate _state;
    };
}
