#include "Exception.hpp"

nts::Exception::Exception(const std::string str) : _str(str)
{
}

nts::Exception::~Exception()
{
}

const char *nts::Exception::what() const noexcept
{
    return _str.c_str();
}
