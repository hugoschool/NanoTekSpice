#pragma once

#include "components/IComponent.hpp"
#include <cstddef>
#include <unordered_map>

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
        protected:
            std::unordered_map<std::size_t, std::pair<IComponent &, std::size_t>> _pins;
            Tristate _state;
    };
}
