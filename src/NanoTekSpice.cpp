#include "NanoTekSpice.hpp"
#include "Circuit.hpp"
#include "Exception.hpp"
#include "Parser.hpp"

nts::NanoTekSpice::NanoTekSpice() : _parser(), _tick(0), _circuits(), _shell(_circuits, _tick)
{
}

nts::NanoTekSpice::~NanoTekSpice()
{
}

void nts::NanoTekSpice::addCircuit(const std::string fileName)
{
    _parser.setFileName(fileName);
    _parser.parse();

    nts::Circuit circuit;

    _parser.getContainer().addToCircuit(circuit);
    _circuits.push_back(circuit);
}

void nts::NanoTekSpice::loop()
{
    if (_circuits.empty())
        throw nts::Exception("No circuits found");

    _shell.loop();
}
