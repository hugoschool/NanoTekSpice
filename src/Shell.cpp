#include "Shell.hpp"
#include "Exception.hpp"
#include "Tristate.hpp"
#include "components/ClockComponent.hpp"
#include "components/IComponent.hpp"
#include "components/InputComponent.hpp"
#include <cstddef>
#include <iostream>
#include <optional>
#include <sstream>

nts::Shell::Shell(std::vector<nts::Circuit> &circuits, std::size_t &tick)
    : _circuits(circuits), _circuitIndex(0), _tick(tick)
{
}

nts::Shell::~Shell()
{
}

std::optional<nts::Tristate> nts::Shell::strToTristate(const std::string &str)
{
    if (str == "0")
        return nts::False;
    if (str == "1")
        return nts::True;
    if (str == "U")
        return nts::Undefined;
    return std::nullopt;
}

void nts::Shell::commandDisplay()
{
    _circuits[_circuitIndex].display(_tick);
}

void nts::Shell::commandSimulate()
{
    _tick += 1;
    _circuits[_circuitIndex].simulate(_tick);
}

void nts::Shell::commandInputValue(std::string &line)
{
    line.at(line.find("=")) = ' ';

    std::stringstream ss(line);
    std::string input;
    std::string valueStr;

    ss >> input;
    ss >> valueStr;

    if (ss.fail()) {
        std::cerr << "Incorrect statement" << std::endl;
        return;
    }

    std::optional<nts::Tristate> tristate = strToTristate(valueStr);
    if (!tristate.has_value()) {
        std::cerr << "Invalid tristate" << std::endl;
        return;
    }

    try {
        std::shared_ptr<nts::IComponent> ptr = _circuits[_circuitIndex].find(input);

        // TODO: simplify this too
        if (dynamic_cast<nts::InputComponent *>(ptr.get()) || dynamic_cast<nts::ClockComponent *>(ptr.get())) {
            dynamic_cast<nts::InputComponent *>(ptr.get())->store(tristate.value());
        } else {
            std::cerr << "Component is not an input or a clock" << std::endl;
        }
    } catch (const nts::Exception &err) {
        std::cerr << err.what() << std::endl;
    }
}

// TODO: there's probably something to simplify here
void nts::Shell::loop()
{
    std::string line;

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line))
            break;

        if (line == "exit") {
            break;
        } else if (line == "display") {
            commandDisplay();
        } else if (line == "simulate") {
            commandSimulate();
        } else if (line == "loop") {
            while (true) {
                commandSimulate();
                commandDisplay();
            }
        } else if (line.find("=") != line.npos) {
            commandInputValue(line);
        } else if (!line.empty()) {
            std::cerr << "Unknown command" << std::endl;
        }
    }
}
