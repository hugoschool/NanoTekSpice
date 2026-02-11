#include "components/OutputComponent.hpp"
#include "components/AComponent.hpp"

nts::OutputComponent::OutputComponent() : AComponent()
{
}

nts::OutputComponent::~OutputComponent()
{
}

nts::Tristate nts::OutputComponent::compute(std::size_t pin)
{
    switch (pin) {
        case 2: {
            return getLink(1);
        }
        default:
            return nts::Undefined;
    }
}
