#pragma once

#include <iostream>

namespace nts {
    enum Tristate {
        Undefined = (-true),
        True = true,
        False = false
    };
}

std::ostream &operator<<(std::ostream &s, nts::Tristate v);
