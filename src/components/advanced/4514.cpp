#include "components/advanced/4514.hpp"
#include "Tristate.hpp"
#include <array>

nts::Component4514::Component4514(): _outputPins({
    {11, 0},
    {9, 1},
    {10, 2},
    {8, 3},
    {7, 4},
    {6, 5},
    {5, 6},
    {4, 7},
    {18, 8},
    {17, 9},
    {20, 10},
    {19, 11},
    {14, 12},
    {13, 13},
    {16, 14},
    {15, 15},
})
{
}

nts::Component4514::~Component4514()
{
}

std::optional<uint8_t> nts::Component4514::defineBinaryVal(std::array<std::pair<nts::Tristate, std::uint8_t>, 4> &vals)
{
    uint8_t binary_val = 0;

    std::size_t nullIndex = 0;
    for (auto val: vals) {
        if (val.first == nts::Undefined) {
            nullIndex++;
        }
    }
    if (nullIndex == vals.size())
        return std::nullopt;

    for (std::size_t i = 0; i < vals.size(); i++) {
        if (vals[i].first == True) {
            binary_val |= vals[i].second;
        }
    }
    return binary_val;
}

nts::Tristate nts::Component4514::compute(std::size_t pin)
{
    if (pin == 12 || pin == 24)
        return nts::Undefined;
    if (getLink(23) == True) {
        _state = False;
        return _state;
    }
    std::array<std::pair<nts::Tristate, std::uint8_t>, 4> vals({
        {getLink(2), 0b00000001},
        {getLink(3), 0b00000010},
        {getLink(21), 0b00000100},
        {getLink(22), 0b00001000},
    });
    if (pin > 3 && pin < 21) {
        for (auto pair: _outputPins) {
            if (!defineBinaryVal(vals).has_value()) {
                _state = Undefined;
                return _state;
            }
            if (pin == pair.first && defineBinaryVal(vals) == pair.second) {
                _state = True;
                break;
            } else {
                _state = False;
            }
        }
        return _state;
    }
    _state = getLink(pin);
    return _state;
}
