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
    _state = getLink(pin);
    return _state;
}
