
#include "components/advanced/4017.hpp"
#include "Tristate.hpp"
#include <cstddef>

// cp0 is in_0, pin 14
// cp1 is in_1, pin 13
// MR is in_r, pin 15

/*
3 = 0
2 = 1
4 = 2
7 = 3
10 = 4
1 = 5
5 = 6
6 = 7
9 = 8
11 = 9
12 -> q rev
*/

nts::Component4017::Component4017()
{
    _state = Undefined;
    _currentIndex = -1;
}

nts::Component4017::~Component4017()
{
}

void nts::Component4017::simulate(std::size_t tick)
{
    static_cast<void>(tick);
    Tristate reset = getLink(15);
    Tristate cp0 = _pins.at(14).first.getState();
    Tristate cp1 = _pins.at(13).first.getState();

    if (cp0 == Undefined)
        _pins.at(14).first.setState(_pins.at(14).first.compute(_pins.at(14).second));
    if (cp1 == Undefined)
        _pins.at(13).first.setState(_pins.at(13).first.compute(_pins.at(13).second));
    if (reset == True)
        _currentIndex = 0;
    for (auto pin: _pins) {
        if ((pin.first == 14 && cp0 == False && pin.second.first.compute(pin.second.second) == True)
            || (pin.first == 15 && cp1 == True && pin.second.first.compute(pin.second.second) == False)) {
            if (_currentIndex == 9)
                _currentIndex = 0;
            else
                _currentIndex += 1;
        }
        if (_currentIndex == -1)
            continue;
        else
            pin.second.first.setState(pin.second.first.compute(pin.second.second));
    }
}

nts::Tristate nts::Component4017::compute(std::size_t pin)
{
    switch (pin) {
        case 1:
            if (_currentIndex == 5)
                _state = True;
            else
                _state = False;
            return _state;
        case 2:
            if (_currentIndex == 1)
                _state = True;
            else
                _state = False;
            return _state;
        case 3:
            if (_currentIndex == 0)
                _state = True;
            else
                _state = False;
            return _state;
        case 4:
            if (_currentIndex == 2)
                _state = True;
            else
                _state = False;
            return _state;
        case 5:
            if (_currentIndex == 6)
                _state = True;
            else
                _state = False;
            return _state;
        case 6:
            if (_currentIndex == 7)
                _state = True;
            else
                _state = False;
            return _state;
        case 7:
            if (_currentIndex == 3)
                _state = True;
            else
                _state = False;
            return _state;
        case 9:
            if (_currentIndex == 8)
                _state = True;
            else
                _state = False;
            return _state;
        case 10:
            if (_currentIndex == 4)
                _state = True;
            else
                _state = False;
            return _state;
        case 11:
            if (_currentIndex == 9)
                _state = True;
            else
                _state = False;
            return _state;
        case 12:
            if (_currentIndex >= 5)
                _state = False;
            else
                _state = True;
            return _state;
    }
    return getLink(pin);
}
