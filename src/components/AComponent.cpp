#include "components/AComponent.hpp"
#include "Pins.hpp"
#include "Tristate.hpp"
#include "components/IComponent.hpp"
#include <cstddef>

nts::AComponent::AComponent() : IComponent(), _state(nts::Undefined)
{
}

nts::AComponent::~AComponent()
{
}

void nts::AComponent::simulate(std::size_t tick)
{
    _pins.simulate(tick);
}

void nts::AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    _pins.setPin(pin, other, otherPin);
}

nts::Tristate nts::AComponent::getLink(std::size_t pin)
{
    return _pins.getLink(pin);
}

void nts::AComponent::setPinState(std::size_t pin, nts::Tristate state)
{
    _pins.setPinState(pin, state);
}

void nts::AComponent::setState(nts::Tristate state)
{
    _state = state;
}

nts::Tristate nts::AComponent::getState() const
{
    return _state;
}
