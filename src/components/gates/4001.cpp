#include "components/NorComponent.hpp"
#include "components/gates/4001.hpp"
#include "Tristate.hpp"

nts::Component4001::Component4001()
{
    bool invert = false;
    std::size_t pin = 1;

    for (std::size_t i = 0; i < _component_array.size(); i++) {
        _component_array[i] = std::make_shared<nts::NorComponent>();
        if (pin == 7)
            pin++;
        if (invert) {
            for (int j = 3; j > 0; j--) {
                setLink(pin, *_component_array[i], j);
                pin++;
            }
            invert = false;
        } else {
            for (int j = 1; j < 4; j++) {
                setLink(pin, *_component_array[i], j);
                pin++;
            }
            invert = true;
        }
    }
}

nts::Component4001::~Component4001()
{
}

nts::Tristate nts::Component4001::compute(std::size_t pin)
{
    switch (pin) {
        case 7: case 14:
            return nts::Undefined;
        default:
            break;
    }
    return getLink(pin);
}
