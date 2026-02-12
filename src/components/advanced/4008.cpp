#include "components/advanced/FullBitAdder.hpp"
#include "components/advanced/4008.hpp"
#include "Tristate.hpp"
#include <cstddef>

/*
Its basically 4 FullBitAdders linked together, the C out of the first 3 being the C in of the others
See link in FullBitAdder.cpp for more explanations
*/

nts::Component4008::Component4008()
{
    std::size_t pin = 2;

    for (std::size_t i = _component_array.size(); i > 0; i--)
        _component_array[i - 1] = std::make_shared<nts::FullBitAdder>();
    for (std::size_t i = _component_array.size(); i > 0; i--) {
        if (pin == 8)
            break;
        if (i >= 2)
            for (int j = 1; j < 3; j++) {
                std::cout << "pin " << pin << " linked with pin x of component : " << j << " on component : " << i - 2 << std::endl;
                _component_array[i - 2]->setLink(j, *this, pin);
                pin++;
            }
    }
    _component_array[3]->setLink(1, *this, 1);
    _component_array[3]->setLink(2, *this, 15);
    _component_array[0]->setLink(3, *this, 9);
    _component_array[1]->setLink(3, *_component_array[0], 4);
    _component_array[2]->setLink(3, *_component_array[1], 4);
    _component_array[3]->setLink(3, *_component_array[2], 4);
    _component_array[0]->setLink(5, *this, 10);
    setLink(10, *_component_array[0], 5);
    _component_array[1]->setLink(5, *this, 11);
    setLink(11, *_component_array[1], 5);
    _component_array[2]->setLink(5, *this, 12);
    setLink(12, *_component_array[2], 5);
    _component_array[3]->setLink(5, *this, 13);
    setLink(13, *_component_array[3], 5);
    _component_array[3]->setLink(4, *this, 14);
    setLink(14, *_component_array[3], 4);
}

nts::Component4008::~Component4008()
{
}

nts::Tristate nts::Component4008::compute(std::size_t pin)
{
    switch (pin) {
        case 8: case 16:
            return nts::Undefined;
        default:
            break;
    }
    return getLink(pin);
}
