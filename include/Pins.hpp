#pragma once

#include "Tristate.hpp"
#include "components/IComponent.hpp"
#include <cstddef>
#include <tuple>
#include <unordered_map>
namespace nts {
    class Pins {
        public:
            // First element is the other component it is linked to
            // Second is the other pin it is linked to
            // Third is the state of that other component
            // Fourth is whether it has been computed in that last simulation or not.
            using pinContent = std::tuple<nts::IComponent &, std::size_t, nts::Tristate, bool>;

            Pins();
            ~Pins();

            void resetComputeState();
            void simulate(std::size_t);
            void setPin(std::size_t, nts::IComponent &, std::size_t);
            void setPinState(std::size_t, nts::Tristate);
            nts::Tristate getLink(std::size_t pin);

            std::unordered_map<std::size_t, pinContent> _map;
    };
}
