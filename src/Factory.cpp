#include "Factory.hpp"
#include "Exception.hpp"
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
    {"and", []() -> std::shared_ptr<nts::IComponent>{return std::make_shared<nts::AndComponent>();}},
    {"clock", []() -> std::shared_ptr<nts::IComponent>{return std::make_shared<nts::ClockComponent>();}},
    {"false", []() -> std::shared_ptr<nts::IComponent>{return std::make_shared<nts::FalseComponent>();}},
    {"input", []() -> std::shared_ptr<nts::IComponent>{return std::make_shared<nts::InputComponent>();}},
    {"not", []() -> std::shared_ptr<nts::IComponent>{return std::make_shared<nts::NotComponent>();}},
    {"or", []() -> std::shared_ptr<nts::IComponent>{return std::make_shared<nts::OrComponent>();}},
    {"output", []() -> std::shared_ptr<nts::IComponent>{return std::make_shared<nts::OutputComponent>();}},
    {"true", []() -> std::shared_ptr<nts::IComponent>{return std::make_shared<nts::TrueComponent>();}},
    {"xor", []() -> std::shared_ptr<nts::IComponent>{return std::make_shared<nts::XorComponent>();}},
}})
{
}

nts::Factory::~Factory()
{
}

std::shared_ptr<nts::IComponent> nts::Factory::createComponent(const std::string &type)
{
    for (const std::pair<std::string, std::function<std::shared_ptr<nts::IComponent>()>> &pair : _components) {
        if (type == pair.first)
            return pair.second();
    };

    throw nts::Exception("Type unknown");
}
