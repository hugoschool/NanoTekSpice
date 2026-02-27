#include "components/advanced/4040.hpp"
#include "Tristate.hpp"
#include "components/AComponent.hpp"
#include <cmath>
#include <cstddef>
#include <unordered_map>

// Pin 9    = Q1 (out_00)
// Pin 7    = Q2 (out_01)
// Pin 6    = Q3 (out_02)
// Pin 5    = Q4 (out_03)
// Pin 3    = Q5 (out_04)
// Pin 2    = Q6 (out_05)
// Pin 4    = Q7 (out_06)
// Pin 13   = Q8 (out_07)
// Pin 12   = Q9 (out_08)
// Pin 14   = Q10 (out_09)
// Pin 15   = Q11 (out_10)
// Pin 1    = Q12 (out_11)
//
// Pin 10   = Clock
// Pin 11   = Reset

nts::Component4040::Component4040() : AComponent(), _clockCycle(0), _storedMap()
{
    _previousClock = getLink(10);
}

nts::Component4040::~Component4040()
{
}

void nts::Component4040::simulate(std::size_t tick)
{
    nts::Tristate clock = getLink(10);
    nts::Tristate reset = getLink(11);

    if (reset == True)
        _clockCycle = 0;
    else if (reset == False && _previousClock == nts::True && clock == nts::False)
        _clockCycle++;
    AComponent::simulate(tick);
    _previousClock = clock;
}

bool nts::Component4040::isPowerOfTwo(std::size_t nb)
{
    float log = std::log2(nb);

    return std::ceil(log) == std::floor(log);
}

nts::Tristate nts::Component4040::storePin(std::size_t pin, nts::Tristate state)
{
    _storedMap[pin] = state;
    return state;
}

nts::Tristate nts::Component4040::getStoredPin(std::size_t pin)
{
    try {
        return _storedMap.at(pin);
    } catch (const std::out_of_range &) {
        return False;
    }
}

nts::Tristate nts::Component4040::compute(std::size_t pin)
{
    nts::Tristate clock = getLink(10);
    std::unordered_map<std::size_t, std::size_t> _map({
        {9, 0},
        {7, 1},
        {6, 2},
        {5, 3},
        {3, 4},
        {2, 5},
        {4, 6},
        {13, 7},
        {12, 8},
        {14, 9},
        {15, 10},
        {1, 11},
    });

    switch (pin) {
        case 9: case 7: case 6: case 5: case 3: case 2:
        case 4: case 13: case 12: case 14: case 15: case 1: {
            // Correponds to 2 ** pin nb
            // Ex: 2 ** pin 9 = 2 ** 1 = 2
            std::size_t powerTwoPin = std::pow(2, _map[pin]);

            if (_previousClock == nts::True && clock == nts::False) {
                if (_clockCycle == powerTwoPin) {
                    _state = storePin(pin, nts::True);
                } else if (_clockCycle > powerTwoPin) {
                    if (isPowerOfTwo(_clockCycle + 1))
                        _state = storePin(pin, nts::True);
                    else
                        _state = storePin(pin, nts::False);
                } else
                    _state = storePin(pin, nts::False);
            } else
                _state = getStoredPin(pin);
            break;
        }
        default:
            _state = nts::False;
            break;
    }
    return _state;
}
