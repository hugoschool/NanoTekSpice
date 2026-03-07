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
// [2]: https://www.youtube.com/watch?v=7RWaDvTeG7Y&t=248s

nts::Component4094::Component4094() : AComponent(), _pinOutputMap({
    {4, 0},
    {5, 1},
    {6, 2},
    {7, 3},
    {14, 4},
    {13, 5},
    {12, 6},
    {11, 7},
}), _shiftContainer(), _hasShifted(false), _serialOutputs()
{
    _previousClock = getLink(3);
}

nts::Component4094::~Component4094()
{
}

void nts::Component4094::simulate(std::size_t tick)
{
    AComponent::simulate(tick);
    _hasShifted = false;
    _previousClock = getLink(3);
}

void nts::Component4094::setStateFromShiftContainer(std::size_t pin)
{
    try {
        const std::size_t index = _pinOutputMap.at(pin);
        _state = _shiftContainer[index];
    } catch (const std::out_of_range &) {
        _state = Undefined;
    }
}

nts::Tristate nts::Component4094::compute(std::size_t pin)
{
    nts::Tristate clock = getLink(3);
    nts::Tristate enable = getLink(15);
    nts::Tristate strobe = getLink(1);
    nts::Tristate data = getLink(2);

    if (_previousClock == False && clock == True && !_hasShifted) {
        // Take the last shift nb and put it in QS
        _serialOutputs[0] = _shiftContainer[_shiftContainer.max_size() - 1];

        _shiftContainer.add(data);
        _hasShifted = true;
    }
    if (_previousClock == True && clock == False) {
        // Take the last shift nb and put it in QS2
        _serialOutputs[1] = _shiftContainer[_shiftContainer.max_size() - 1];
    }
    if (_pinOutputMap.contains(pin)) {
        if (enable == False) {
            _shiftContainer.fill(nts::Undefined);
            return Undefined;
        }
        if (strobe == False) {
            setStateFromShiftContainer(pin);
            return _state;
        }
        setStateFromShiftContainer(pin);
        return _state;
    }
    if (pin == 9 || pin == 10) {
        std::size_t serialIndex = pin == 9 ? 0 : 1;

        _state = _serialOutputs[serialIndex];
    }
    return _state;
}
