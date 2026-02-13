#include "components/NorComponent.hpp"
#include "Tristate.hpp"
#include "components/AComponent.hpp"

nts::NorComponent::NorComponent() : AComponent()
{
}

nts::NorComponent::~NorComponent()
{
}

nts::Tristate nts::NorComponent::compute(std::size_t pin)
{
    switch (pin) {
        case 3: {
            nts::Tristate a = getLink(1);
            nts::Tristate b = getLink(2);

            if (a == nts::True || b == nts::True) {
                _state = False;
                return _state;
            }

            if (a == nts::Undefined || b == nts::Undefined) {
                _state = Undefined;
                return _state;
            }
            _state = static_cast<nts::Tristate>(!(a || b));
            return _state;
        }
        default:
            _state = getLink(pin);
            return _state;
    }
}
