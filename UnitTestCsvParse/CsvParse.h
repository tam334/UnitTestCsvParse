#pragma once

#include <list>

namespace CsvParse
{
    void Parse(std::list<std::list<std::string>>& dst, std::string const& text);

    int ParseCSV(std::list<std::list<std::string>>& dst,
                 std::string const& csv,
                 int currentIndex);
    int ParseRow(std::list<std::list<std::string>>& dst,
                 std::string const& csv,
                 int currentIndex);
    std::string ParseColumn(std::list<std::list<std::string>>& dst,
                            std::string const& csv,
                            int& currentIndex);
    std::string ParseToken(std::list<std::list<std::string>>& dst,
                           std::string const& csv,
                           int& currentIndex);
    std::string ParseAnyString(std::list<std::list<std::string>>& dst,
                               std::string const& csv,
                               int& currentIndex);
    int ParseNewLine(std::string const& csv, int currentIndex);
    bool CheckNextChar(std::string const& csv, int currentIndex, char next);
}
