#include "components/advanced/4512.hpp"
#include "Tristate.hpp"

nts::Component4512::Component4512()
{
}

nts::Component4512::~Component4512()
{
}

nts::Tristate nts::Component4512::decide_state()
{
    nts::Tristate a = getLink(11);
    nts::Tristate b = getLink(12);
    nts::Tristate c = getLink(13);
    nts::Tristate inhibit = getLink(10);
    nts::Tristate enable = getLink(15);

    if (enable == True)
        return Undefined;
    if (inhibit == True && enable == False)
        return False;
    if (a == False && b == False && c == False && inhibit == False && enable == False)
        return getLink(1);
    if (a == True && b == False && c == False && inhibit == False && enable == False)
        return getLink(2);
    if (a == False && b == True && c == False && inhibit == False && enable == False)
        return getLink(3);
    if (a == True && b == True && c == False && inhibit == False && enable == False)
        return getLink(4);
    if (a == False && b == False && c == True && inhibit == False && enable == False)
        return getLink(5);
    if (a == True && b == False && c == True && inhibit == False && enable == False)
        return getLink(6);
    if (a == False && b == True && c == True && inhibit == False && enable == False)
        return getLink(7);
    if (a == True && b == True && c == True && inhibit == False && enable == False)
        return getLink(9);
    return Undefined;
}

nts::Tristate nts::Component4512::compute(std::size_t pin)
{
    if (pin == 14) {
        _state = decide_state();
        return _state;
    }
    _state = getLink(pin);
    return _state;
}

