#include "Tristate.hpp"
#include <algorithm>
#include <array>
#include <cstddef>

namespace nts {
    template<std::size_t T>
    class ShiftContainer {
        public:
            ShiftContainer<T>() : _container()
            {
                _container.fill(nts::False);
            };

            ~ShiftContainer<T>()
            {
            };

            void shift()
            {
                std::rotate(_container.rbegin(), _container.rbegin() + 1, _container.rend());
            }

            void add(nts::Tristate state)
            {
                shift();
                _container[0] = state;
            }

            std::size_t size() const
            {
                return _container.size();
            }

            std::size_t max_size() const
            {
                return _container.max_size();
            }

            void fill(nts::Tristate state)
            {
                _container.fill(state);
            }

            nts::Tristate &operator[](std::size_t index)
            {
                return _container[index];
            }
        private:
            std::array<nts::Tristate, T> _container;
    };
}
