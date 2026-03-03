#include "components/advanced/4040.hpp"
#include "Tristate.hpp"
#include "components/AComponent.hpp"
#include <bitset>
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
//
// [1]: https://lacavernedelucan.com/comptez-vos-impulsions-avec-le-cmos-4040/

nts::Component4040::Component4040() : AComponent(), _clockCycle(0), _pinToIndexMap({
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
})
{
    _previousClock = getLink(10);
}

nts::Component4040::~Component4040()
{
}

void nts::Component4040::simulate(std::size_t tick)
{
    _pins.resetComputeState();
    nts::Tristate clock = getLink(10);
    nts::Tristate reset = getLink(11);

    if (reset == True)
        _clockCycle = 0;
    else if (reset == False && _previousClock == nts::True && clock == nts::False)
        _clockCycle++;
    AComponent::simulate(tick);
    _previousClock = clock;
}

nts::Tristate nts::Component4040::compute(std::size_t pin)
{
    const std::bitset<12> bits(_clockCycle);

    switch (pin) {
        case 9: case 7: case 6: case 5: case 3: case 2:
        case 4: case 13: case 12: case 14: case 15: case 1: {
            _state = bits[_pinToIndexMap.at(pin)] == 1 ? True : False;
            break;
        }
        default:
            _state = nts::False;
            break;
    }
    return _state;
}
