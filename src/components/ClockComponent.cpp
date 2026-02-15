#include "components/ClockComponent.hpp"
#include "components/AComponent.hpp"
#include "Tristate.hpp"

nts::ClockComponent::ClockComponent() : AComponent(), _interiorState(nts::Undefined), _tick(0)
{
}

nts::ClockComponent::~ClockComponent()
{
}

void nts::ClockComponent::store(nts::Tristate state)
{
    _interiorState = state;
}

void nts::ClockComponent::simulate(std::size_t tick)
{
    for (; _tick < tick; _tick++) {
        _state = _interiorState;
        for (auto pin : _pins) {
            pin.second.first.setState(pin.second.first.compute(pin.second.second));
        }
        if (_interiorState != Undefined)
            _interiorState = static_cast<nts::Tristate>(!static_cast<bool>(_state));
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
