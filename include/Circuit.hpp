#pragma once

#include "components/IComponent.hpp"
#include <unordered_map>
#include <memory>
#include <string>

namespace nts {
    class Circuit : public IComponent {
        public:
            Circuit();
            ~Circuit();

            nts::Tristate compute(std::size_t pin) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
            void simulate(std::size_t tick = 1) override final;
            void display();
            void add(std::string, std::shared_ptr<IComponent>);
            std::shared_ptr<IComponent> find(const std::string &);
        private:
            std::unordered_map<std::string, std::shared_ptr<IComponent>> _components;
            // TODO: global tick
            std::size_t _tick;
    };
}
