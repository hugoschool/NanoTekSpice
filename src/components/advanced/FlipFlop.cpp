#include "components/advanced/FlipFlop.hpp"
#include "Tristate.hpp"
#include "components/AComponent.hpp"
#include <cstddef>

// Pin 1: Data
// Pin 2: Set
// Pin 3: Reset
// Pin 4: Clock
// Pin 5: Output Q
// Pin 6: Output /Q (Qbis)
//
// Notes:
// According to schema[1], the "set" pin is the same as data
// and the "reset" pin is the reverse of the data type.
//
// [1]: https://www.electronics-tutorials.ws/sequential/seq_4.html

// Important:
// This FlipFlop component is weird and acts weirdly on its own.
// This is due to the /Q (Qbis) setting the state in a weird way.
// Check out the Component4013 for a good example on how to use this component.

nts::FlipFlop::FlipFlop() : AComponent(), _reversedState(nts::Undefined)
{
    _previousClock = getLink(4);
}

nts::FlipFlop::~FlipFlop()
{
}

void nts::FlipFlop::simulate(std::size_t tick)
{
    AComponent::simulate(tick);
    _previousClock = getLink(4);
}

nts::Tristate nts::FlipFlop::getReverseState()
{
    if (_state == nts::Undefined)
        return nts::Undefined;
    _reversedState = static_cast<nts::Tristate>(!static_cast<bool>(_state));
    return _reversedState;
}

nts::Tristate nts::FlipFlop::compute(std::size_t pin)
{
    nts::Tristate data = getLink(1);
    nts::Tristate set = getLink(2);
    nts::Tristate reset = getLink(3);
    nts::Tristate clock = getLink(4);

    switch (pin) {
        case 5:
            if (set == nts::True && reset == nts::True)
                _state = nts::True;
            if (set == nts::False && reset == nts::True)
                _state = nts::False;
            if (set == nts::True && reset == nts::False)
                _state = nts::True;
            if (_previousClock == nts::True && clock == nts::False &&
                set == nts::False && reset == nts::False)
                _state = _state;
            if (_previousClock == nts::False && clock == nts::True) {
                if (data == nts::True && set == nts::False && reset == nts::False)
                    _state = nts::True;
                else if (data == nts::False && set == nts::False && reset == nts::False)
                    _state = nts::False;
            }
            return _state;
        case 6:
            if (set == nts::True && reset == nts::True)
                return nts::True;
            compute(5);
            return getReverseState();
    }
    return _state;
}
