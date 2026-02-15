#include "components/ClockComponent.hpp"
#include "components/AComponent.hpp"
#include "Tristate.hpp"
#include <optional>

nts::ClockComponent::ClockComponent() : AComponent(), _new_state(), _tick(0)
{
}

nts::ClockComponent::~ClockComponent()
{
}

void nts::ClockComponent::store(nts::Tristate state)
{
    _new_state = std::make_optional(state);
}

void nts::ClockComponent::simulate(std::size_t tick)
{
    if (_new_state.has_value()) {
        _state = _new_state.value();
        _new_state = std::nullopt;
    }
    for (; _tick < tick; _tick++) {
        for (auto pin : _pins) {
            pin.second.first.setState(pin.second.first.compute(pin.second.second));
        }
        if (_state != Undefined)
            _state = static_cast<nts::Tristate>(!static_cast<bool>(_state));
    }
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

// This is a work around.
//
// Essentially, the simulate function will correctly set the state of the pins but on the very last
// loop of the simulate tick, it changes the state again.
// You can observe/understand this behavior better when commenting out these next few lines
//
// What we are pretty much doing is setting the interior state to a value
// and we are showing the opposite value as the input.
nts::Tristate nts::ClockComponent::getState() const
{
    if (_state == Undefined)
        return Undefined;
    return static_cast<nts::Tristate>(!static_cast<bool>(_state));
}
