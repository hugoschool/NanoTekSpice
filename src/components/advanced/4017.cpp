
#include "components/advanced/4017.hpp"
#include "Tristate.hpp"
#include "components/AComponent.hpp"
#include <array>
#include <cstddef>

// Pin 14 = CP0
// Pin 13 = CP1
// Pin 15 = MR
//
// Pin 3    = Output 0
// Pin 2    = Output 1
// Pin 4    = Output 2
// Pin 7    = Output 3
// Pin 10   = Output 4
// Pin 1    = Output 5
// Pin 5    = Output 6
// Pin 6    = Output 7
// Pin 9    = Output 8
// Pin 11   = Output 9
// Pin 12   = q rev

nts::Component4017::Component4017() : AComponent(), _currentIndex(-1)
{
    _previousClock = getLink(14);
    _previousInverseClock = getLink(13);
}

nts::Component4017::~Component4017()
{
}

void nts::Component4017::increaseIndex()
{
    if (_currentIndex == 9)
        _currentIndex = 0;
    else
        _currentIndex++;
}

void nts::Component4017::simulate(std::size_t tick)
{
    nts::Tristate clock = getLink(14);
    nts::Tristate inverseClock = getLink(13);
    nts::Tristate reset = getLink(15);

    if (reset == True) {
        _currentIndex = 0;
        AComponent::simulate(tick);
        return;
    }

    if ((_previousClock == nts::Undefined && clock != nts::Undefined)
        || (_previousInverseClock == nts::Undefined && inverseClock != nts::Undefined))
        _currentIndex = 0;
    if ((_previousClock == nts::False && clock == nts::True)
        || (_previousInverseClock == nts::True && inverseClock == nts::False)) {
        increaseIndex();
    }

    AComponent::simulate(tick);
    _previousClock = clock;
    _previousInverseClock = inverseClock;
}

nts::Tristate nts::Component4017::compute(std::size_t pin)
{
    std::array<std::pair<std::size_t, int>, 10> _array({
        {3, 0},
        {2, 1},
        {4, 2},
        {7, 3},
        {10, 4},
        {1, 5},
        {5, 6},
        {6, 7},
        {9, 8},
        {11, 9},
    });

    for (std::size_t i = 0; i < _array.size(); i++) {
        if (pin != _array[i].first)
            continue;
        if (_currentIndex == -1) {
            _state = nts::Undefined;
            return _state;
        } else if (_currentIndex == _array[i].second)
            _state = nts::True;
        else
            _state = nts::False;
        return _state;
    }
    if (pin == 12)  {
        if (_currentIndex == -1) {
            _state = nts::Undefined;
            return _state;
        } else if (_currentIndex >= 5)
            _state = nts::False;
        else
            _state = nts::True;
        return _state;
    }
    return getLink(pin);
}
