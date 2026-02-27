#include "components/advanced/LoggerComponent.hpp"
#include "Tristate.hpp"
#include "components/AComponent.hpp"
#include <fstream>
#include <array>

// Pin 1: Input (bit 1)
// Pin 2: Input (bit 2)
// Pin 3: Input (bit 4)
// Pin 4: Input (bit 8)
// Pin 5: Input (bit 16)
// Pin 6: Input (bit 32)
// Pin 7: Input (bit 64)
// Pin 8: Input (bit 128)
// Pin 9: Clock
// Pin 10: Inhibit (Input)

nts::LoggerComponent::LoggerComponent() : AComponent(), _file()
{
    _previousClock = getLink(9);
    _file.open("./log.bin", std::ios_base::app);
}

nts::LoggerComponent::~LoggerComponent()
{
    if (_file.is_open())
        _file.close();
}

void nts::LoggerComponent::simulate(std::size_t tick)
{
    AComponent::simulate(tick);
    _previousClock = getLink(9);
}

nts::Tristate nts::LoggerComponent::compute(std::size_t)
{
    std::array<std::pair<nts::Tristate, std::uint8_t>, 8> inputs({
        {getLink(1), 0b00000001},
        {getLink(2), 0b00000010},
        {getLink(3), 0b00000100},
        {getLink(4), 0b00001000},
        {getLink(5), 0b00010000},
        {getLink(6), 0b00100000},
        {getLink(7), 0b01000000},
        {getLink(8), 0b10000000},
    });
    nts::Tristate clock = getLink(9);
    nts::Tristate inhibit = getLink(10);

    if (inhibit != nts::False || _file.fail() || !_file.is_open()) {
        _previousClock = clock;
        return nts::Undefined;
    }
    if (_previousClock == nts::False && clock == nts::True) {
        std::uint8_t byte = 0;
        bool isUndefined = false;

        for (std::size_t i = 0; i < inputs.size(); i++) {
            if (inputs[i].first == nts::Undefined) {
                isUndefined = true;
                break;
            }
            if (inputs[i].first == nts::True) {
                byte = byte | inputs[i].second;
            }
        }
        if (isUndefined == false)
            _file << byte;
    }
    _previousClock = clock;
    return nts::Undefined;
}
