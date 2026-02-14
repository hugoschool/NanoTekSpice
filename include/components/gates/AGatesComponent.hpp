#pragma once

#include "components/AComponent.hpp"
#include <cstddef>
#include <array>
#include <memory>

namespace nts {
    template<typename T>
    class AGatesComponent : public AComponent {
        public:
            AGatesComponent() {
                bool invert = false;
                std::size_t pin = 1;

                for (std::size_t i = 0; i < _component_array.size(); i++) {
                    _component_array[i] = std::make_shared<T>();
                    if (pin == 7)
                        pin++;
                    if (invert) {
                        for (int j = 3; j > 0; j--) {
                            _component_array[i]->setLink(j, *this, pin);
                            pin++;
                        }
                        invert = false;
                    } else {
                        for (int j = 1; j < 4; j++) {
                            _component_array[i]->setLink(j, *this, pin);
                            pin++;
                        }
                        invert = true;
                    }
                }
            };

            ~AGatesComponent() {};

            nts::Tristate compute(std::size_t pin) override {
                switch (pin) {
                    case 7: case 14:
                        return nts::Undefined;
                    case 3:
                        _state = _component_array[0]->compute(3);
                        break;
                    case 4:
                        _state = _component_array[1]->compute(3);
                        break;
                    case 10:
                        _state = _component_array[2]->compute(3);
                        break;
                    case 11:
                        _state = _component_array[3]->compute(3);
                        break;
                    default:
                        _state = getLink(pin);
                        break;
                }
                return _state;
            };

        protected:
            std::array<std::shared_ptr<T>, 4> _component_array;
    };
}
