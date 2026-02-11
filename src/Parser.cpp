#include "Parser.hpp"
#include "Exception.hpp"
#include "components/IComponent.hpp"
#include <iostream>
#include <sstream>
#include <string>

nts::Parser::Parser(const std::string fileName): _factory(), _fileName(fileName), _fileStream()
{
}

nts::Parser::~Parser()
{
    if (_fileStream.is_open())
        _fileStream.close();
}

bool nts::Parser::open()
{
    if (!_fileStream.is_open()) {
        _fileStream.open(_fileName);
        return _fileStream.is_open();
    } else {
        return true;
    }
}

std::vector<std::pair<std::string, std::shared_ptr<nts::IComponent>>> nts::Parser::getChipsets()
{
    return _chipsets;
}

void nts::Parser::removeComments(std::string &str)
{
}

void nts::Parser::parse()
{
    if (!open()) {
        throw nts::Exception("Couldn't open file");
    }

    std::stringstream ss;
    ss << _fileStream.rdbuf();

    std::string fullContent = ss.str();

    removeComments(fullContent);
    parseSection(fullContent, CHIPSETS_STATEMENT, &Parser::parseChipsetLine);
    parseSection(fullContent, LINKS_STATEMENT, &Parser::parseLinkLine);
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

    _chipsets.push_back({name, _factory.createComponent(type)});
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

    for (const std::pair<std::string, std::shared_ptr<nts::IComponent>> &pair : _chipsets) {
        if (pair.first == name) {
            return {pin, pair.second};
        }
    }

    throw nts::Exception("Couldn't find chipset " + name + " from link");
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
}

void nts::Parser::parseSection(
    const std::string &str,
    const char *statementConst,
    std::function<void(nts::Parser *, const std::string &)> func
) {
    std::string::size_type statement = str.find(statementConst);

    if (statement != str.npos) {
        std::stringstream ss(str.substr(statement));
        std::string line;

        // void out the CHIPSETS_STATEMENT cuz useless
        std::getline(ss, line);

        while (std::getline(ss, line)) {
            if (line.empty() || line.starts_with("."))
                break;
            func(this, line);
        }
    } else {
        throw nts::Exception(std::string("Couldn't find ", statementConst));
    }
}
