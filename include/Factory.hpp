#pragma once

#include "components/IComponent.hpp"
#include <array>
#include <functional>
#include <memory>

namespace nts {
    class Factory {
        public:
            Factory();
            ~Factory();

            std::unique_ptr<nts::IComponent> createComponent(const std::string &type);
        private:
            const std::array<std::pair<std::string, std::function<std::unique_ptr<nts::IComponent>()>>, 9> _components;
    };
}
