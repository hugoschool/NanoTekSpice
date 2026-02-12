#pragma once

#include "Circuit.hpp"
#include "Parser.hpp"
#include "Shell.hpp"
#include <cstddef>
#include <string>
#include <vector>

namespace nts {
    class NanoTekSpice {
        public:
            NanoTekSpice();
            ~NanoTekSpice();

            void addCircuit(const std::string);
            void loop();

        private:
            nts::Parser _parser;

            // Tick is shared between all circuits
            std::size_t _tick;

            std::vector<nts::Circuit> _circuits;

            nts::Shell _shell;
    };
}
