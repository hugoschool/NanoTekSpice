#pragma once

#include "Circuit.hpp"
#include "Factory.hpp"
#include "components/IComponent.hpp"
#include <fstream>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#define COMMENT_SYMBOL "#"
#define STATEMENT_SYMBOL "."
#define CHIPSETS_STATEMENT ".chipsets:"
#define LINKS_STATEMENT ".links:"

namespace nts {
    class Parser {
        public:
            class IComponentContainer {
                public:
                    IComponentContainer();
                    ~IComponentContainer();

                    void addToCircuit(nts::Circuit &);
                    std::optional<std::shared_ptr<nts::IComponent>> find(const std::string &);
                    bool empty() const;

                    void addInput(std::pair<std::string, std::shared_ptr<IComponent>> &pair);
                    void addOutput(std::pair<std::string, std::shared_ptr<IComponent>> &pair);
                    void addRest(std::pair<std::string, std::shared_ptr<IComponent>> &pair);

                private:
                    std::vector<std::pair<std::string, std::shared_ptr<nts::IComponent>>> _inputs;
                    std::vector<std::pair<std::string, std::shared_ptr<nts::IComponent>>> _outputs;
                    std::vector<std::pair<std::string, std::shared_ptr<nts::IComponent>>> _rest;
            };

            Parser();
            ~Parser();

            nts::Parser::IComponentContainer getContainer() const;
            void setFileName(const std::string);
            void parse();

        private:
            nts::Factory _factory;

            std::string _fileName;
            std::ifstream _fileStream;

            IComponentContainer _container;

            std::string _line;
            bool _lineIsStatement;

            std::optional<std::shared_ptr<nts::IComponent>> findComponentByName(const std::string &name);

            bool open();
            void parseSection(std::stringstream &, const std::string);
            void parseChipsetLine(const std::string &);
            std::pair<std::size_t, std::shared_ptr<nts::IComponent>> parseLinkPart(std::string &);
            void parseLinkLine(const std::string &);

            std::string &getline(std::stringstream &ss);
            void removeComments(std::string &);
            void removeWhitespaces(std::string &);
    };
}
