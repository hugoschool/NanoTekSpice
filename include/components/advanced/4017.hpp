#pragma once

#include "components/AComponent.hpp"

namespace nts {
    class Component4017 : public nts::AComponent {
        public:
            Component4017();
            ~Component4017();

            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t tick) override;
        private:
            int _currentIndex;
    };
}
