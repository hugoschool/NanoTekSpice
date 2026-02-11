#include "NanoTekSpice.hpp"
#include "Circuit.hpp"
#include "Exception.hpp"

nts::NanoTekSpice::NanoTekSpice() : _parser(), _tick(0), _circuits()
{
}

nts::NanoTekSpice::~NanoTekSpice()
{
}

void nts::NanoTekSpice::addCircuit(const std::string fileName)
{
    _parser.setFileName(fileName);
    _parser.parse();

    const std::vector<std::pair<std::string, std::shared_ptr<nts::IComponent>>> chipsets = _parser.getChipsets();
    nts::Circuit circuit;

    for (const std::pair<std::string, std::shared_ptr<nts::IComponent>> &pair : chipsets) {
        circuit.add(pair.first, pair.second);
    }
    _circuits.push_back(circuit);
}

void nts::NanoTekSpice::loop()
{
    if (_circuits.empty())
        throw nts::Exception("No circuits found");
}
