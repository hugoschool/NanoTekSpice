#include "components/advanced/4013.hpp"
#include "Tristate.hpp"
#include "components/AComponent.hpp"
#include <cstddef>

nts::Component4013::Component4013() : AComponent()
{
}

nts::Component4013::~Component4013()
{
}

nts::Tristate nts::Component4013::compute(std::size_t pin)
{
    // This can all be simplified into one component SingleFlipFlop
    nts::Tristate clock_1 = getLink(3);
    nts::Tristate in_1_reset = getLink(4);
    nts::Tristate in_1_data = getLink(5);
    nts::Tristate in_1_set = getLink(6);

    nts::Tristate clock_2 = getLink(11);
    nts::Tristate in_2_reset = getLink(10);
    nts::Tristate in_2_data = getLink(9);
    nts::Tristate in_2_set = getLink(8);

    switch (pin) {
        // Q 1 output
        case 1:
            if (in_1_reset == nts::True && in_1_set == nts::True) {
                _state = nts::True;
                return _state;
            }
            if (in_1_reset == nts::True) {
                _state = nts::False;
                return _state;
            }
            if (in_1_set == nts::True) {
                _state = nts::True;
                return _state;
            }
            if (clock_1 == nts::True && in_1_data == nts::True) {
                _state = nts::True;
                return _state;
            }
            if (clock_1 == nts::True && in_1_data == nts::False) {
                _state = nts::False;
                return _state;
            }
            if (clock_1 == nts::False && in_1_reset == nts::False && in_1_set == nts::False) {
                _state = getLink(1);
                return _state;
            }
            return _state;
        // /Q 1 output
        case 2:
            if (in_1_reset == nts::True && in_1_set == nts::True) {
                _state = nts::True;
                return _state;
            }
            if (in_1_reset == nts::True) {
                _state = nts::True;
                return _state;
            }
            if (in_1_set == nts::True) {
                _state = nts::False;
                return _state;
            }
            if (clock_1 == nts::True && in_1_data == nts::True) {
                _state = nts::False;
                return _state;
            }
            if (clock_1 == nts::True && in_1_data == nts::False) {
                _state = nts::True;
                return _state;
            }
            if (clock_1 == nts::False && in_1_reset == nts::False && in_1_set == nts::False) {
                _state = getLink(2);
                return _state;
            }
            return _state;
        // Q 2 output
        case 13:
            if (in_2_reset == nts::True && in_2_set == nts::True) {
                _state = nts::True;
                return _state;
            }
            if (in_2_reset == nts::True) {
                _state = nts::False;
                return _state;
            }
            if (in_2_set == nts::True) {
                _state = nts::True;
                return _state;
            }
            if (clock_2 == nts::True && in_2_data == nts::True) {
                _state = nts::True;
                return _state;
            }
            if (clock_2 == nts::True && in_2_data == nts::False) {
                _state = nts::False;
                return _state;
            }
            if (clock_2 == nts::False && in_2_reset == nts::False && in_2_set == nts::False) {
                _state = getLink(13);
                return _state;
            }
            return _state;
        // /Q 2 output
        case 12:
            if (in_2_reset == nts::True && in_2_set == nts::True) {
                _state = nts::True;
                return _state;
            }
            if (in_2_reset == nts::True) {
                _state = nts::True;
                return _state;
            }
            if (in_2_set == nts::True) {
                _state = nts::False;
                return _state;
            }
            if (clock_2 == nts::True && in_2_data == nts::True) {
                _state = nts::False;
                return _state;
            }
            if (clock_2 == nts::True && in_2_data == nts::False) {
                _state = nts::True;
                return _state;
            }
            if (clock_2 == nts::False && in_2_reset == nts::False && in_2_set == nts::False) {
                _state = getLink(12);
                return _state;
            }
            return _state;
        default:
            _state = getLink(pin);
            break;
    }
    return _state;
}
