#include "components/AComponent.hpp"
#include "Tristate.hpp"
#include "components/IComponent.hpp"
#include <cstddef>
#include <stdexcept>
#include <utility>

nts::AComponent::AComponent() : IComponent(), _state(nts::Undefined)
{
}

nts::AComponent::~AComponent()
{
}

void nts::AComponent::simulate(std::size_t)
{
    for (auto pin : _pins) {
        pin.second.first.setState(pin.second.first.compute(pin.second.second));
    }
}

void nts::AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    std::pair<nts::IComponent &, std::size_t> pair = std::make_pair(std::ref(other), otherPin);

    _pins.insert_or_assign(pin, pair);
}

nts::Tristate nts::AComponent::getLink(std::size_t pin)
{
    try {
        std::pair<nts::IComponent &, std::size_t> pair = _pins.at(pin);
        nts::IComponent &component = pair.first;

        if (&component == this)
            return getState();
        return component.compute(pair.second);
    } catch (const std::out_of_range &) {
        return nts::Undefined;
    }
}

void nts::AComponent::setState(nts::Tristate state)
{
    _state = state;
}

nts::Tristate nts::AComponent::getState() const
{
    return _state;
}
