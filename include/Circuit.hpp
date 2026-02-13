#pragma once

#include "components/IComponent.hpp"
#include <map>
#include <unordered_map>
#include <memory>
#include <string>

namespace nts {
    class Circuit : public IComponent {
        public:
            Circuit();
            ~Circuit();

            nts::Tristate compute(std::size_t pin) override;
            nts::Tristate getState() const override;
            void setState(Tristate state) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
            void simulate(std::size_t tick) override final;
            void display(std::size_t &tick);
            void add(std::string, std::shared_ptr<IComponent>);
            std::shared_ptr<IComponent> find(const std::string &);
        private:
            std::unordered_map<std::string, std::shared_ptr<IComponent>> _components;

            std::map<std::string, std::shared_ptr<IComponent>> _inputs;
            std::map<std::string, std::shared_ptr<IComponent>> _outputs;
    };
}
