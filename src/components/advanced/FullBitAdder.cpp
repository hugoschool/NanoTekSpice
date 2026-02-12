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
        _and_components[i] = std::make_shared<AndComponent>();
    for (std::size_t i = 0; i < _xor_components.size(); i++)
        _xor_components[i] = std::make_shared<XorComponent>();
    _or_component = std::make_shared<OrComponent>();

    _xor_components[0]->setLink(1, *this, 1);
    _xor_components[0]->setLink(2, *this, 2);
    _and_components[0]->setLink(1, *this, 3);
    _and_components[1]->setLink(1, *this, 1);
    _and_components[1]->setLink(2, *this, 2);
    _xor_components[1]->setLink(1, *_xor_components[0], 3);
    _xor_components[1]->setLink(2, *this, 3);
    _and_components[0]->setLink(2, *_xor_components[0], 3);
    _or_component->setLink(1, *_and_components[0], 3);
    _or_component->setLink(3, *_and_components[1], 3);
    this->setLink(4, *_or_component, 3);
    this->setLink(5, *_xor_components[1], 3);
}

nts::FullBitAdder::~FullBitAdder()
{
}

nts::Tristate nts::FullBitAdder::compute(std::size_t pin)
{
    return getLink(pin);
}
