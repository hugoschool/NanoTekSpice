#pragma once

#include "AComponent.hpp"
#include <optional>

namespace nts {
    class ClockComponent : public AComponent {
        public:
            ClockComponent();
            ~ClockComponent();

            void store(nts::Tristate);
            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;
        private:
            // Sort of workaround for the cl=0 which directly set after simulate
            std::optional<nts::Tristate> _new_state;

            nts::Tristate _state;
    };
}
