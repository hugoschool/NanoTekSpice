#include "Parser.hpp"
#include "Exception.hpp"
#include "components/IComponent.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <array>

nts::Parser::Parser(): _factory(), _fileName(), _fileStream(), _line(), _lineIsStatement(false)
{
}

nts::Parser::~Parser()
{
    if (_fileStream.is_open())
        _fileStream.close();
}

void nts::Parser::setFileName(const std::string fileName)
{
    _fileName = fileName;
}

bool nts::Parser::open()
{
    if (_fileName.empty())
        return false;

    if (!_fileStream.is_open()) {
        _fileStream.open(_fileName);
        return _fileStream.is_open();
    } else {
        return true;
    }
}

nts::Parser::IComponentContainer::IComponentContainer()
{
}

nts::Parser::IComponentContainer::~IComponentContainer()
{
}

void nts::Parser::IComponentContainer::addToCircuit(nts::Circuit &circuit)
{
    for (const auto &pair : _rest) {
        circuit.addComponent(pair.first, pair.second);
    }
    for (const auto &pair : _inputs) {
        circuit.addInput(pair.first, pair.second);
    }
    for (const auto &pair : _outputs) {
        circuit.addOutput(pair.first, pair.second);
    }
}

bool nts::Parser::IComponentContainer::empty() const
{
    return _inputs.empty() && _outputs.empty() && _rest.empty();
}

void nts::Parser::IComponentContainer::addInput(std::pair<std::string, std::shared_ptr<IComponent>> &pair)
{
    _inputs.push_back(pair);
}

void nts::Parser::IComponentContainer::addOutput(std::pair<std::string, std::shared_ptr<IComponent>> &pair)
{
    _outputs.push_back(pair);
}

void nts::Parser::IComponentContainer::addRest(std::pair<std::string, std::shared_ptr<IComponent>> &pair)
{
    _rest.push_back(pair);
}

std::optional<std::shared_ptr<nts::IComponent>> nts::Parser::IComponentContainer::find(const std::string &name)
{
    const std::array<std::vector<std::pair<std::string, std::shared_ptr<nts::IComponent>>>, 3> _containers({
        _rest,
        _inputs,
        _outputs
    });

    for (const auto &container : _containers) {
        for (const std::pair<std::string, std::shared_ptr<nts::IComponent>> &pair : container) {
            if (pair.first == name)
                return pair.second;
        }
    }
    return std::nullopt;
}

nts::Parser::IComponentContainer nts::Parser::getContainer() const
{
    return _container;
}

// Trim left then trim right
// could be factored out into utils if needed
void nts::Parser::removeWhitespaces(std::string &str)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}

void nts::Parser::removeComments(std::string &str)
{
    str = str.substr(0, str.find(COMMENT_SYMBOL));
}

std::string &nts::Parser::getline(std::stringstream &ss)
{
    std::getline(ss, _line);
    removeComments(_line);
    removeWhitespaces(_line);
    return _line;
}

void nts::Parser::parse()
{
    if (!open()) {
        throw nts::Exception("Couldn't open file");
    }

    std::stringstream ss;
    ss << _fileStream.rdbuf();

    if (ss.str().empty()) {
        throw nts::Exception("File is empty");
    }

    while (!ss.eof()) {
        if (!_lineIsStatement)
            _line = getline(ss);
        if (_line.starts_with(STATEMENT_SYMBOL)) {
            parseSection(ss, _line);
        } else if (!_line.empty() && !std::all_of(_line.begin(),_line.end(),isspace)) {
            throw nts::Exception("Line is not a statement");
        }
    }

    if (_container.empty()) {
        throw nts::Exception("Chipsets cannot be empty");
    }
}

void nts::Parser::parseChipsetLine(const std::string &line)
{
    std::stringstream ss(line);
    std::string type;
    std::string name;

    ss >> type;
    ss >> name;

    if (ss.fail()) {
        throw nts::Exception("Too few arguments when parsing chipset");
    }

    // checks if the stringstream is empty or not
    char empty;
    ss >> empty;
    if (!ss.fail()) {
        throw nts::Exception("Too many arguments when parsing chipset");
    }

    if (_container.find(name).has_value()) {
        throw nts::Exception("Component " + name + " already exists");
    }

    std::pair<std::string, std::shared_ptr<nts::IComponent>> pair = std::make_pair(name, _factory.createComponent(type));

    if (type == "input" || type == "clock") {
        _container.addInput(pair);
    } else if (type == "output") {
        _container.addOutput(pair);
    } else {
        _container.addRest(pair);
    }
}

std::pair<std::size_t, std::shared_ptr<nts::IComponent>> nts::Parser::parseLinkPart(std::string &str)
{
    // replacing ":" with " " to extract with ss
    if (str.find(":") == str.npos) {
        throw nts::Exception("Incorrect link");
    }
    str.at(str.find(":")) = ' ';

    std::stringstream ss(str);
    std::string name;
    std::size_t pin;

    ss >> name;
    ss >> pin;

    if (ss.fail()) {
        throw nts::Exception("Error when parsing link");
    }

    std::optional<std::shared_ptr<nts::IComponent>> ptr = _container.find(name);

    if (ptr.has_value()) {
        return {pin, *ptr};
    } else {
        throw nts::Exception("Couldn't find chipset " + name + " from link");
    }
}

void nts::Parser::parseLinkLine(const std::string &line)
{
    std::stringstream ss(line);
    std::string first;
    std::string second;

    ss >> first;
    ss >> second;

    if (ss.fail()) {
        throw nts::Exception("Too few arguments when parsing links");
    }

    // checks if the stringstream is empty or not
    char empty;
    ss >> empty;
    if (!ss.fail()) {
        throw nts::Exception("Too many arguments when parsing links");
    }

    std::pair<std::size_t, std::shared_ptr<nts::IComponent>> firstPart = parseLinkPart(first);
    std::pair<std::size_t, std::shared_ptr<nts::IComponent>> secondPart = parseLinkPart(second);

    firstPart.second->setLink(firstPart.first, *secondPart.second, secondPart.first);
    secondPart.second->setLink(secondPart.first, *firstPart.second, firstPart.first);
}

void nts::Parser::parseSection(std::stringstream &ss, const std::string statement) {
    std::string line;
    size_t i = 0;

    for (; !ss.eof(); i++) {
        line = getline(ss);
        if (line.empty())
            continue;
        if (line.starts_with(STATEMENT_SYMBOL)) {
            _lineIsStatement = true;
            break;
        }

        if (statement == CHIPSETS_STATEMENT)
            parseChipsetLine(line);
        else if (statement == LINKS_STATEMENT)
            parseLinkLine(line);
        else
            throw nts::Exception("Statement " + statement + " unknown.");
    }
    if (i == 0) {
        throw nts::Exception("Incorrect statement");
    }
}
