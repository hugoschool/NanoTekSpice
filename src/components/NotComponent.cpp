#include "components/NotComponent.hpp"
#include "Tristate.hpp"
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
        case 2: {
            nts::Tristate linkState = getLink(1);

            if (linkState == Undefined) {
                _state = Undefined;
            } else {
                _state = static_cast<nts::Tristate>(!static_cast<bool>(linkState));
            }
            return _state;
        }
        default:
            _state = getLink(pin);
            return _state;
    }
}
