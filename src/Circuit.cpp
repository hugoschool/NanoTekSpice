#include "Circuit.hpp"
#include "Exception.hpp"
#include "Tristate.hpp"
#include "components/IComponent.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <utility>

nts::Circuit::Circuit() : IComponent(), _components()
{
}

nts::Circuit::~Circuit()
{
}

void nts::Circuit::addComponent(std::string name, std::shared_ptr<IComponent> component)
{
    _components.insert_or_assign(name, component);
}

void nts::Circuit::addInput(std::string name, std::shared_ptr<IComponent> component)
{
    _inputs.insert_or_assign(name, component);
    addComponent(name, component);
}

void nts::Circuit::addOutput(std::string name, std::shared_ptr<IComponent> component)
{
    _outputs.insert_or_assign(name, component);
    addComponent(name, component);
}

std::shared_ptr<nts::IComponent> nts::Circuit::find(const std::string &name)
{
    auto value = _components.find(name);

    if (value == _components.end()) {
        throw nts::Exception("Component not found");
    }
    return value->second;
}

std::shared_ptr<nts::IComponent> nts::Circuit::findInput(const std::string &name)
{
    auto value = _inputs.find(name);

    if (value == _inputs.end()) {
        throw nts::Exception("Couldn't find input");
    }
    return value->second;
}

void nts::Circuit::simulate(std::size_t tick)
{
    for (std::pair<const std::string, std::shared_ptr<nts::IComponent>> &input : _inputs) {
        input.second->simulate(tick);
    }
    for (std::pair<const std::string, std::shared_ptr<nts::IComponent>> &pair : _components) {
        // Make sure we don't recompute an input
        try {
            _inputs.at(pair.first);
            continue;
        } catch (const std::out_of_range &) {
            pair.second->simulate(tick);
        }
    }
}

void nts::Circuit::display(std::size_t &tick)
{
    std::cout << "tick: " << tick << std::endl;

    std::cout << "input(s):" << std::endl;
    for (const auto &pair : _inputs) {
        std::cout << "  " << pair.first << ": " << pair.second->getState() << std::endl;
    }

    std::cout << "output(s):" << std::endl;
    for (const auto &pair : _outputs) {
        std::cout << "  " << pair.first << ": " << pair.second->getState() << std::endl;
    }
}

nts::Tristate nts::Circuit::getState() const
{
    return Undefined;
}

void nts::Circuit::setState(nts::Tristate)
{
}

nts::Tristate nts::Circuit::compute(std::size_t)
{
    return nts::Undefined;
}

void nts::Circuit::setLink(std::size_t, nts::IComponent &, std::size_t)
{
}

void nts::Circuit::setInternalState(nts::Tristate)
{
}
