#include "components/InputComponent.hpp"
#include "components/AComponent.hpp"

nts::InputComponent::InputComponent() : AComponent(), _internalState(nts::Undefined)
{
}

nts::InputComponent::~InputComponent()
{
}

void nts::InputComponent::simulate(std::size_t tick)
{
    _state = _internalState;
    AComponent::simulate(tick);
}

void nts::InputComponent::setInternalState(nts::Tristate state)
{
    _internalState = state;
}

nts::Tristate nts::InputComponent::compute(std::size_t pin)
{
    switch (pin) {
        case 1:
            return _state;
        default:
            _state = Undefined;
            return _state;
    }
}
