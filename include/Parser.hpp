#pragma once

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
            Parser();
            ~Parser();

            void setFileName(const std::string);

            void parse();
            std::vector<std::pair<std::string, std::shared_ptr<nts::IComponent>>> getChipsets() const;

        private:
            nts::Factory _factory;

            std::string _fileName;
            std::ifstream _fileStream;

            std::vector<std::pair<std::string, std::shared_ptr<nts::IComponent>>> _chipsets;

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
    };
}
