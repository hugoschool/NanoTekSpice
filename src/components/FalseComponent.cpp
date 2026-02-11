#include "components/FalseComponent.hpp"
#include "components/AComponent.hpp"
#include "Tristate.hpp"

nts::FalseComponent::FalseComponent() : AComponent()
{
}

nts::FalseComponent::~FalseComponent()
{
}

nts::Tristate nts::FalseComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return nts::Undefined;
    return nts::False;
}
