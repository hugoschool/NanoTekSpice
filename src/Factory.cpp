#include "Factory.hpp"
#include "components/AndComponent.hpp"
#include "components/ClockComponent.hpp"
#include "components/FalseComponent.hpp"
#include "components/IComponent.hpp"
#include "components/InputComponent.hpp"
#include "components/NotComponent.hpp"
#include "components/OrComponent.hpp"
#include "components/OutputComponent.hpp"
#include "components/TrueComponent.hpp"
#include "components/XorComponent.hpp"
#include <array>
#include <functional>
#include <memory>
#include <utility>

nts::Factory::Factory() : _components({{
    {"and", []() -> std::unique_ptr<nts::IComponent>{return std::make_unique<nts::AndComponent>();}},
    {"clock", []() -> std::unique_ptr<nts::IComponent>{return std::make_unique<nts::ClockComponent>();}},
    {"false", []() -> std::unique_ptr<nts::IComponent>{return std::make_unique<nts::FalseComponent>();}},
    {"input", []() -> std::unique_ptr<nts::IComponent>{return std::make_unique<nts::InputComponent>();}},
    {"not", []() -> std::unique_ptr<nts::IComponent>{return std::make_unique<nts::NotComponent>();}},
    {"or", []() -> std::unique_ptr<nts::IComponent>{return std::make_unique<nts::OrComponent>();}},
    {"output", []() -> std::unique_ptr<nts::IComponent>{return std::make_unique<nts::OutputComponent>();}},
    {"true", []() -> std::unique_ptr<nts::IComponent>{return std::make_unique<nts::TrueComponent>();}},
    {"xor", []() -> std::unique_ptr<nts::IComponent>{return std::make_unique<nts::XorComponent>();}},
}})
{
}

nts::Factory::~Factory()
{
}

std::unique_ptr<nts::IComponent> nts::Factory::createComponent(const std::string &type)
{
    // TODO: throw exception

    for (const std::pair<std::string, std::function<std::unique_ptr<nts::IComponent>()>> &pair : _components) {
        if (type == pair.first)
            return pair.second();
    };
}
