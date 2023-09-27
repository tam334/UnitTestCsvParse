#include <string>
#include <memory>
#include <list>

#include "CSVParse.h"

namespace CsvParse
{
    void Parse(std::list<std::list<std::string>>& dst, std::string const& text)
    {
        int currentIndex = 0;
        ParseCSV(dst, text, currentIndex);
    }

    
    int ParseCSV(std::list<std::list<std::string>>& dst,
                 std::string const& csv,
                 int currentIndex)
    {
        currentIndex = ParseRow(dst, csv, currentIndex);
        while (CheckNextChar(csv, currentIndex, '\r'))
        {
            currentIndex = ParseNewLine(csv, currentIndex);
            currentIndex = ParseRow(dst, csv, currentIndex);
        }
        if (CheckNextChar(csv, currentIndex, '\r'))
        {
            currentIndex = ParseNewLine(csv, currentIndex);
        }
        return currentIndex;
    }

    int ParseRow(std::list<std::list<std::string>>& dst,
                 std::string const& csv,
                 int currentIndex)
    {
        std::unique_ptr<std::list<std::string>> columns(new std::list<std::string>());
        
        columns->push_back(ParseColumn(dst, csv, currentIndex));
        while (CheckNextChar(csv, currentIndex, ','))
        {
            currentIndex++;
            columns->push_back(ParseColumn(dst, csv, currentIndex));
        }
        
        if(columns->size() > 0)
        {
            dst.push_back(*columns.get());
        }
        return currentIndex;
    }

    std::string ParseColumn(std::list<std::list<std::string>>& dst,
                            std::string const& csv,
                            int& currentIndex)
    {
        if(CheckNextChar(csv, currentIndex, '"'))
        {
            return ParseAnyString(dst, csv, currentIndex);
        }
        else
        {
            return ParseToken(dst, csv, currentIndex);
        }
    }

    int ParseNewLine(std::string const& csv, int currentIndex)
    {
        if (CheckNextChar(csv, currentIndex, '\r'))
        {
            currentIndex++;
        }
        if (CheckNextChar(csv, currentIndex, '\n'))
        {
            currentIndex++;
        }
        return currentIndex;
    }

    
    std::string ParseToken(std::list<std::list<std::string>>& dst,
                           std::string const& csv,
                           int& currentIndex)
    {
        int adv = 0;
        for (adv = 0; adv + currentIndex < csv.length(); adv++)
        {
            if (CheckNextChar(csv, currentIndex + adv, ',') ||
                CheckNextChar(csv, currentIndex + adv, '\r'))
            {
                break;
            }
        }
        currentIndex += adv;
        
        return csv.substr(currentIndex - adv, adv);
    }

    
    std::string ParseAnyString(std::list<std::list<std::string>>& dst,
                               std::string const& csv,
                               int& currentIndex)
    {
        if (CheckNextChar(csv, currentIndex, '"'))
        {
            currentIndex++;
        }
        int adv = 0;
        for(adv = 0; adv + currentIndex < csv.length(); adv++)
        {
            if(CheckNextChar(csv, currentIndex + adv, '"'))
            {
                if(CheckNextChar(csv, currentIndex + adv + 1, '"'))
                {
                    adv += 1;
                }
                else
                {
                    break;
                }
            }
        }
        currentIndex += adv + 1;
        
        return csv.substr(currentIndex - adv - 1, adv);
    }

    bool CheckNextChar(std::string const& csv, int currentIndex, char next)
    {
        return csv.length() > currentIndex && csv[currentIndex] == next;
    }
}
