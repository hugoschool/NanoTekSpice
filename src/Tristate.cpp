#include "Tristate.hpp"
#include <iostream>

std::ostream &operator<<(std::ostream &s, nts::Tristate v)
{
    if (v == nts::Undefined)
        return s << std::string("U");
    return s << std::to_string(v);
}
