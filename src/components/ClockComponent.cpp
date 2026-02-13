#include "components/ClockComponent.hpp"
#include "components/AComponent.hpp"
#include "Tristate.hpp"
#include <optional>

nts::ClockComponent::ClockComponent() : AComponent(), _new_state(), _state(nts::Undefined)
{
}

nts::ClockComponent::~ClockComponent()
{
}

void nts::ClockComponent::store(nts::Tristate state)
{
    _new_state = std::make_optional(state);
}

void nts::ClockComponent::simulate(std::size_t)
{
    // TODO: figure out what the ticks are used for
    if (_new_state.has_value()) {
        _state = _new_state.value();
        _new_state = std::nullopt;
        return;
    }
    _state = static_cast<nts::Tristate>(!static_cast<bool>(_state));
}

nts::Tristate nts::ClockComponent::compute(std::size_t pin)
{
    switch (pin) {
        case 1:
            return _state;
        default:
            return nts::Undefined;
    }
}
