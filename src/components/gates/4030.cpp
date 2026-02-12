#include "components/XorComponent.hpp"
#include "components/gates/4030.hpp"
#include "Tristate.hpp"

nts::Component4030::Component4030()
{
    bool invert = false;
    std::size_t pin = 1;

    for (std::size_t i = 0; i < _component_array.size(); i++) {
        _component_array[i] = std::make_shared<nts::XorComponent>();
        if (pin == 7)
            pin++;
        if (invert) {
            for (int j = 3; j > 0; j--) {
                if (j == 3)
                    setLink(pin, *_component_array[i], j);
                _component_array[i]->setLink(j, *this, pin);
                pin++;
            }
            invert = false;
        } else {
            for (int j = 1; j < 4; j++) {
                if (j == 3)
                    setLink(pin, *_component_array[i], j);
                _component_array[i]->setLink(j, *this, pin);
                pin++;
            }
            invert = true;
        }
    }
}

nts::Component4030::~Component4030()
{
}

nts::Tristate nts::Component4030::compute(std::size_t pin)
{
    switch (pin) {
        case 7: case 14:
            return nts::Undefined;
        default:
            break;
    }
    return getLink(pin);
}
