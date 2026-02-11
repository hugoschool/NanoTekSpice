#include "components/XorComponent.hpp"
#include "components/AComponent.hpp"

nts::XorComponent::XorComponent() : AComponent()
{
}

nts::XorComponent::~XorComponent()
{
}

nts::Tristate nts::XorComponent::compute(std::size_t pin)
{
    switch (pin) {
        case 3: {
            nts::Tristate a = getLink(1);
            nts::Tristate b = getLink(2);
            return static_cast<nts::Tristate>(a ^ b);
        }
        default:
            return nts::Undefined;
    }
}
