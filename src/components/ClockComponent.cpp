#include "components/ClockComponent.hpp"
#include "components/AComponent.hpp"
#include "Tristate.hpp"

nts::ClockComponent::ClockComponent() : AComponent(), _interiorState(nts::Undefined), _tick(0)
{
}

nts::ClockComponent::~ClockComponent()
{
}

void nts::ClockComponent::setInternalState(nts::Tristate state)
{
    _interiorState = state;
}

void nts::ClockComponent::simulate(std::size_t tick)
{
    for (; _tick < tick; _tick++) {
        _state = _interiorState;
        AComponent::simulate(tick);
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
