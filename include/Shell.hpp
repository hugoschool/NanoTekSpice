#pragma once

#include "Circuit.hpp"
#include <optional>
#include <vector>

namespace nts {
    class Shell {
        public:
            Shell(std::vector<nts::Circuit> &, std::size_t &);
            ~Shell();

            void loop();

        private:
            std::vector<nts::Circuit> &_circuits;
            std::size_t _circuitIndex;

            std::size_t &_tick;

            void commandDisplay();
            void commandSimulate(bool add = true);
            void commandLoop();
            void commandInputValue(std::string &);

            std::optional<nts::Tristate> strToTristate(const std::string &str);

    };
}
