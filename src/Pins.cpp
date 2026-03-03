#include "Pins.hpp"
#include "Tristate.hpp"
#include "components/IComponent.hpp"
#include <stdexcept>
#include <tuple>

nts::Pins::Pins() : _map()
{
}

nts::Pins::~Pins()
{
}

void nts::Pins::setPin(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    pinContent content = std::make_tuple(std::ref(other), otherPin, nts::Undefined, NOT_COMPUTED);

    _map.insert_or_assign(pin, content);
}

void nts::Pins::resetComputeState()
{
    for (auto &pin : _map) {
        std::get<3>(pin.second) = NOT_COMPUTED;
    }
}

void nts::Pins::simulate(std::size_t) {
    resetComputeState();
    for (auto pin : _map) {
        nts::IComponent &component = std::get<0>(pin.second);
        std::size_t componentPin = std::get<1>(pin.second);
        nts::Tristate state = component.compute(componentPin);

        component.setState(state);
        component.setPinState(componentPin, state);
    }
}

nts::Tristate nts::Pins::getLink(std::size_t pin)
{
    try {
        nts::Pins::pinContent &content = _map.at(pin);
        nts::IComponent &component = std::get<0>(content);

        if (std::get<3>(content) == COMPUTED)
            return std::get<2>(content);

        std::get<3>(content) = COMPUTED;
        nts::Tristate value = component.compute(std::get<1>(content));
        setPinState(pin, value);
        return value;
    } catch (const std::out_of_range &) {
        return nts::Undefined;
    }
}

void nts::Pins::setPinState(std::size_t pin, nts::Tristate state)
{
    try {
        pinContent &content = _map.at(pin);
        std::get<2>(content) = state;
        std::get<3>(content) = COMPUTED;
    } catch (const std::out_of_range &) {}
}
