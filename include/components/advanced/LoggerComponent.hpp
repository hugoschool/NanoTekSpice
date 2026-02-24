#pragma once

#include "Tristate.hpp"
#include "components/AComponent.hpp"
#include <fstream>

namespace nts {
    class LoggerComponent : public AComponent {
        public:
            LoggerComponent();
            ~LoggerComponent();

            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t tick) override;

        private:
            nts::Tristate _previousClock;
            std::ofstream _file;
    };
}
