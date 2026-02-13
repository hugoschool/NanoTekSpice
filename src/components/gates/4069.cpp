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
                _component_array[i]->setLink(j, *this, pin);
                pin++;
            }
        } else {
            for (int j = 1; j < 3; j++) {
                _component_array[i]->setLink(j, *this, pin);
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
        case 2:
            _state = _component_array[0]->compute(2);
            break;
        case 4:
            _state = _component_array[1]->compute(2);
            break;
        case 6:
            _state = _component_array[2]->compute(2);
            break;
        case 8:
            _state = _component_array[3]->compute(2);
            break;
        case 10:
            _state = _component_array[4]->compute(2);
            break;
        case 12:
            _state = _component_array[5]->compute(2);
            break;
        default:
            _state = getLink(pin);
            break;
    }
    return _state;
}
