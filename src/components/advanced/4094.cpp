#include "components/advanced/4094.hpp"
#include "Tristate.hpp"
#include <stdexcept>

// Pin 4    = Q1 (out_0)
// Pin 5    = Q2 (out_1)
// Pin 6    = Q3 (out_2)
// Pin 7    = Q4 (out_3)
// Pin 14   = Q5 (out_4)
// Pin 13   = Q6 (out_5)
// Pin 12   = Q7 (out_6)
// Pin 11   = Q8 (out_7)
//
// Pin 9    = QS (out_qs)
// Pin 10   = QE / QS2 (out_qe) [1]
//
// Pin 15   = Enable (input)
// Pin 1    = Strobe (input)
// Pin 2    = Data (input)
// Pin 3    = Clock
//
// [1]: https://www.onsemi.com/pdf/datasheet/mc74hc4094a-d.pdf

nts::Component4094::Component4094() : AComponent(), _pinOutputArray({
    {4, 1},
    {5, 2},
    {6, 3},
    {7, 4},
    {14, 5},
    {13, 6},
    {12, 7},
    {11, 8},
}), _storedMap()
{
    _previousClock = getLink(3);
}

nts::Component4094::~Component4094()
{
}

void nts::Component4094::simulate(std::size_t tick)
{
    AComponent::simulate(tick);
    _previousClock = getLink(3);
}

// 4 is used as an error return value as it will just try to get Q1
std::size_t nts::Component4094::getPreviousPin(std::size_t pin)
{
    try {
        std::pair<std::size_t, std::size_t> pair = _pinOutputArray.at(pin);

        if (pair.second == 1)
            return 4;

        for (std::size_t i = 0; i < _pinOutputArray.size(); i++) {
            if (_pinOutputArray[i].second == pair.second - 1)
                return _pinOutputArray[i].first;
        }
        return 4;
    } catch (const std::out_of_range &) {
        return 4;
    }
}

nts::Tristate nts::Component4094::storePin(std::size_t pin, nts::Tristate state)
{
    _storedMap[pin] = state;
    return state;
}

nts::Tristate nts::Component4094::getStoredPin(std::size_t pin)
{
    try {
        return _storedMap.at(pin);
    } catch (const std::out_of_range &) {
        return Undefined;
    }
}

nts::Tristate nts::Component4094::compute(std::size_t pin)
{
    nts::Tristate clock = getLink(3);
    nts::Tristate enable = getLink(15);
    nts::Tristate strobe = getLink(1);
    nts::Tristate data = getLink(2);

    switch (pin) {
        case 4: case 5: case 6: case 7: case 14: case 13: case 12: case 11:
            if (enable == False) {
                _state = storePin(pin, Undefined);
                break;
            }
            if (_previousClock == False && clock == True) {
                if (strobe == True && data != Undefined && pin == 4) {
                    _state = storePin(pin, data);
                    break;
                } else if (strobe == True && data != Undefined) {
                    _state = storePin(pin, getLink(getPreviousPin(pin)));
                    break;
                } else if (strobe == False) {
                    _state = getStoredPin(pin);
                    break;
                }
            }
            if (_previousClock == True && clock == False) {
                if (enable == True && strobe == True && data == True) {
                    _state = getStoredPin(pin);
                    break;
                } else {
                    _state = getStoredPin(pin);
                    break;
                }
            }
            break;
        // QS1
        case 9:
            if (_previousClock == False && clock == True) {
                _state = storePin(pin, getLink(12));
                break;
            } else if (_previousClock == True && clock == False) {
                _state = getStoredPin(pin);
                break;
            }
            break;
        // QS2
        case 10:
            if (_previousClock == True && clock == False) {
                if (enable == False || (enable == True && strobe == True && data == True)) {
                    _state = storePin(pin, getLink(12));
                    break;
                }
            } else if (_previousClock == False && clock == True) {
                _state = getStoredPin(pin);
                break;
            }
            break;
        default:
            _state = getStoredPin(pin);
            break;
    }
    return _state;
}
