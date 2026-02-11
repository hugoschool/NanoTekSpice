#include "components/AComponent.hpp"
#include "components/IComponent.hpp"
#include <cstddef>
#include <stdexcept>
#include <utility>

nts::AComponent::AComponent() : IComponent()
{
}

nts::AComponent::~AComponent()
{
}

void nts::AComponent::simulate(std::size_t tick)
{
    static_cast<void>(tick);
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

        return component.compute(pair.second);
    } catch (const std::out_of_range &) {
        return nts::Undefined;
    }
}
