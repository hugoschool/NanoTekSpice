/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** main.cpp
*/

#include "NanoTekSpice.hpp"
#include "Exception.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Incorrect number of arguments" << std::endl;
        return 84;
    }

    try {
        nts::NanoTekSpice nts;
        nts.addCircuit(argv[1]);
        nts.loop();
    } catch (const nts::Exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
