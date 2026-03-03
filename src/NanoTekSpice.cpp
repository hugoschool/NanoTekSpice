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

    const nts::Parser::IComponentContainer chipsets = _parser.getChipsets();
    for (const auto &pair : chipsets) {
        circuit.addComponent(pair.first, pair.second);
    }

    const nts::Parser::IComponentContainer inputs = _parser.getInputs();
    for (const auto &pair : inputs) {
        circuit.addInput(pair.first, pair.second);
    }

    const nts::Parser::IComponentContainer outputs = _parser.getOutputs();
    for (const auto &pair : outputs) {
        circuit.addOutput(pair.first, pair.second);
    }
    _circuits.push_back(circuit);
}

void nts::NanoTekSpice::loop()
{
    if (_circuits.empty())
        throw nts::Exception("No circuits found");

    _shell.loop();
}
