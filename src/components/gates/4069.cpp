#include "components/NotComponent.hpp"
#include "components/gates/4069.hpp"
#include "Tristate.hpp"

nts::Component4069::Component4069()
{
    bool invert = false;
    std::size_t pin = 1;

    for (std::size_t i = 0; i < _component_array.size(); i++) {
        _component_array[i] = std::make_shared<nts::NotComponent>();
        if (pin == 7) {
            pin++;
            invert = true;
        }
        if (invert) {
            for (int j = 2; j > 0; j--) {
                setLink(pin, *_component_array[i], j);
                pin++;
            }
        } else {
            for (int j = 1; j < 3; j++) {
                setLink(pin, *_component_array[i], j);
                pin++;
            }
        }
    }
}

nts::Component4069::~Component4069()
{
}

nts::Tristate nts::Component4069::compute(std::size_t pin)
{
    switch (pin) {
        case 7: case 14:
            return nts::Undefined;
        default:
            break;
    }
    return getLink(pin);
}
