/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** main.cpp
*/

#include "Parser.hpp"
#include "Exception.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Incorrect number of arguments" << std::endl;
        return 84;
    }

    nts::Parser parser(argv[1]);

    try {
        parser.parse();
    } catch (const nts::Exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
