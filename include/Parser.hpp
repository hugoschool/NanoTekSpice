#pragma once

#include "Factory.hpp"
#include "components/IComponent.hpp"
#include <fstream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#define COMMENT_SYMBOL "#"
#define CHIPSETS_STATEMENT ".chipsets:"
#define LINKS_STATEMENT ".links:"

namespace nts {
    class Parser {
        public:
            Parser(const std::string);
            ~Parser();

            void parse();
            std::vector<std::pair<std::string, std::shared_ptr<nts::IComponent>>> getChipsets();

        private:
            nts::Factory _factory;

            const std::string _fileName;
            std::ifstream _fileStream;

            std::vector<std::pair<std::string, std::shared_ptr<nts::IComponent>>> _chipsets;

            bool open();
            void parseSection(const std::string &, const char *, std::function<void(nts::Parser *, const std::string &)>);
            void parseChipsetLine(const std::string &);
            std::pair<std::size_t, std::shared_ptr<nts::IComponent>> parseLinkPart(std::string &);
            void parseLinkLine(const std::string &);

            void removeComments(std::string &);
    };
}
