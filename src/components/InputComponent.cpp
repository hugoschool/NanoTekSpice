#include "components/InputComponent.hpp"
#include "components/AComponent.hpp"

nts::InputComponent::InputComponent() : AComponent(), _state(nts::Undefined)
{
}

nts::InputComponent::~InputComponent()
{
}

void nts::InputComponent::store(nts::Tristate state)
{
    _state = state;
}

nts::Tristate nts::InputComponent::compute(std::size_t pin)
{
    switch (pin) {
        case 1:
            return _state;
        default:
            return nts::Undefined;
    }
}
