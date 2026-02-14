#include "components/NandComponent.hpp"
#include "components/gates/4011.hpp"
#include "components/gates/AGatesComponent.hpp"

nts::Component4011::Component4011() : AGatesComponent<nts::NandComponent>()
{
}

nts::Component4011::~Component4011()
{
}
