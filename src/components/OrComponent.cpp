#include "components/OrComponent.hpp"
#include "components/AComponent.hpp"

nts::OrComponent::OrComponent() : AComponent()
{
}

nts::OrComponent::~OrComponent()
{
}

nts::Tristate nts::OrComponent::compute(std::size_t pin)
{
    switch (pin) {
        case 3: {
            nts::Tristate a = getLink(1);
            nts::Tristate b = getLink(2);
            return static_cast<nts::Tristate>(a || b);
        }
        default:
            return getLink(pin);
    }
}
