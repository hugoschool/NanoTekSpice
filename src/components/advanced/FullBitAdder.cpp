#include "components/advanced/FullBitAdder.hpp"
#include "components/AndComponent.hpp"
#include "components/OrComponent.hpp"
#include "components/XorComponent.hpp"
#include <memory>

/*
First pin is A
Second pin is B
Third pin is C in
Fourth pin is C out
Fifth pin is S
for reference : https://en.wikipedia.org/wiki/Adder_(electronics) (good simulations)
*/

nts::FullBitAdder::FullBitAdder()
{
    for (std::size_t i = 0; i < _and_components.size(); i++)
        _and_components[i] = std::make_unique<AndComponent>();
    for (std::size_t i = 0; i < _xor_components.size(); i++)
        _xor_components[i] = std::make_unique<XorComponent>();
    _or_component = std::make_unique<OrComponent>();

    _xor_components[0]->setLink(1, *this, 1);
    _xor_components[0]->setLink(2, *this, 2);
    _and_components[0]->setLink(1, *this, 1);
    _and_components[0]->setLink(2, *this, 2);
    _xor_components[1]->setLink(1, *_xor_components[0], 3);
    _xor_components[1]->setLink(2, *this, 3);
    _and_components[1]->setLink(1, *_xor_components[0], 3);
    _and_components[1]->setLink(2, *this, 3);
    _or_component->setLink(1, *_and_components[0], 2);
    _or_component->setLink(2, *_and_components[1], 1);
    _or_component->setLink(3, *this, 4);
    _xor_components[1]->setLink(3, *this, 5);
}

nts::FullBitAdder::~FullBitAdder()
{
}

nts::Tristate nts::FullBitAdder::compute(std::size_t pin)
{
    switch (pin) {
        case 4:
            _state = _or_component->compute(3);
            return _state;
        case 5:
            _state = _xor_components[1]->compute(3);
            return _state;
        default:
            _state = getLink(pin);
            return _state;
    }
}
