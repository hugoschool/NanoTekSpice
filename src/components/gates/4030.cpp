#include "components/XorComponent.hpp"
#include "components/gates/4030.hpp"
#include "components/gates/AGatesComponent.hpp"

nts::Component4030::Component4030() : AGatesComponent<nts::XorComponent>()
{
}

nts::Component4030::~Component4030()
{
}
