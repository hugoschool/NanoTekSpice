#include "components/NotComponent.hpp"
#include "components/AComponent.hpp"

nts::NotComponent::NotComponent() : AComponent()
{
}

nts::NotComponent::~NotComponent()
{
}

nts::Tristate nts::NotComponent::compute(std::size_t pin)
{
    switch (pin) {
        case 2:
            _state = static_cast<nts::Tristate>(!static_cast<bool>(getLink(1)));
            return _state;
        default:
            _state = getLink(pin);
            return _state;
    }
}
