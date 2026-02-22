#include "components/advanced/4013.hpp"
#include "components/advanced/FlipFlop.hpp"
#include <memory>

nts::Component4013::Component4013()
{
    _array[0] = std::make_unique<nts::FlipFlop>();
    _array[1] = std::make_unique<nts::FlipFlop>();

    _array[0]->setLink(1, *this, 5);
    _array[0]->setLink(2, *this, 6);
    _array[0]->setLink(3, *this, 4);
    _array[0]->setLink(4, *this, 3);
    _array[0]->setLink(5, *this, 1);
    _array[0]->setLink(6, *this, 2);

    _array[1]->setLink(5, *this, 13);
    _array[1]->setLink(6, *this, 12);
    _array[1]->setLink(1, *this, 9);
    _array[1]->setLink(2, *this, 8);
    _array[1]->setLink(3, *this, 10);
    _array[1]->setLink(4, *this, 11);
}

nts::Component4013::~Component4013()
{
}

void nts::Component4013::simulate(std::size_t tick)
{
    AComponent::simulate(tick);
    _array[0]->simulate(tick);
    _array[1]->simulate(tick);
}

nts::Tristate nts::Component4013::compute(std::size_t pin)
{
    switch (pin) {
        case 1:
            _state = _array[0]->compute(5);
            return _state;
        case 2:
            _array[0]->compute(6);
            _state = _array[0]->getReverseState();
            return _state;
        case 13:
            _state = _array[1]->compute(5);
            return _state;
        case 12:
            _array[1]->compute(6);
            _state = _array[1]->getReverseState();
            return _state;
        default:
            break;
    }
    return getLink(pin);
}
