#include "Circuit.hpp"
#include "Exception.hpp"
#include "Tristate.hpp"
#include "components/ClockComponent.hpp"
#include "components/IComponent.hpp"
#include "components/InputComponent.hpp"
#include "components/OutputComponent.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <unordered_map>

nts::Circuit::Circuit() : IComponent(), _components()
{
}

nts::Circuit::~Circuit()
{
}

void nts::Circuit::add(std::string name, std::shared_ptr<IComponent> component)
{
    _components.insert_or_assign(name, std::move(component));
}

std::shared_ptr<nts::IComponent> nts::Circuit::find(const std::string &name)
{
    std::unordered_map<std::string, std::shared_ptr<nts::IComponent>>::iterator value = _components.find(name);

    if (value == _components.end()) {
        throw nts::Exception("Component not found");
    }

    return value->second;
}

void nts::Circuit::simulate(std::size_t tick)
{
    for (std::pair<const std::string, std::shared_ptr<nts::IComponent>> &pair : _components) {
        pair.second->simulate(tick);
    }
}

void nts::Circuit::display(std::size_t &tick)
{
    std::cout << "tick: " << tick << std::endl;

    // TODO: sort in alphabetical order
    // TODO: unsure about all of this
    std::cout << "input(s):" << std::endl;
    for (std::pair<const std::string, std::shared_ptr<nts::IComponent>> &pair : _components) {
        if (dynamic_cast<InputComponent *>(pair.second.get())
            || dynamic_cast<ClockComponent *>(pair.second.get())) {
            std::cout << "  " << pair.first << ": " << pair.second->getState() << std::endl;
        }
    }

    std::cout << "output(s):" << std::endl;
    for (std::pair<const std::string, std::shared_ptr<nts::IComponent>> &pair : _components) {
        if (dynamic_cast<OutputComponent *>(pair.second.get())) {
            std::cout << "  " << pair.first << ": " << pair.second->getState() << std::endl;
        }
    }
}

nts::Tristate nts::Circuit::getState() const
{
    return Undefined;
}

void nts::Circuit::setState(nts::Tristate state)
{
    static_cast<void>(state);
}

nts::Tristate nts::Circuit::compute(std::size_t pin)
{
    static_cast<void>(pin);
    return nts::Undefined;
}

void nts::Circuit::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    static_cast<void>(pin);
    static_cast<void>(other);
    static_cast<void>(otherPin);
}
