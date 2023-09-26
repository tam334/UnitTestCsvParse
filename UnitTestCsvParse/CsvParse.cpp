#include <string>
#include <memory>
#include <list>

#include "CSVParse.h"

//! 以下の構文木に基づきパース
//! Csv = 行 {改行 行}* [改行]
//! 行 = カラム {, カラム}*
//! カラム = (トークン) | (" 任意の文字列 ")
//! トークン = ,"\r\nを除いた文字列

/// <summary>
/// CSVを解析し、二次元配列形式で出力
/// </summary>
/// <param name="text">
/// テキスト形式のCSV
/// </param>
void Parse(std::list<std::list<std::string>>& dst, std::string const& text)
{
    int currentIndex = 0;
    ParseCSV(dst, text, currentIndex);
}

/// <summary>
/// Csvのパーズ本体
/// </summary>
/// <param name="currentIndex">
/// 現在の解析位置、呼び出し先の関数内で変更されるので要素数1の配列で渡す
/// </param>
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

/// <summary>
/// 行のパーズ
/// </summary>
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

/// <summary>
/// 任意の文字列のパーズ
/// </summary>
/// <return>
/// 文字列
/// </return>
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

/// <summary>
/// 改行のパーズ
/// </summary>
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

/// <summary>
/// トークンのパーズ
/// </summary>
/// <return>
/// 文字列
/// </return>
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

/// <summary>
/// 行のパーズ
/// </summary>
/// <return>
/// 配列、0:進めた後のindex 1:文字列
/// </return>
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

    return csv.substr(currentIndex - adv - 1, adv - 1);
}

/// <summary>
/// 次の文字が終端でなく、nextであるか
/// </summary>
bool CheckNextChar(std::string const& csv, int currentIndex, char next)
{
    return csv.length() > currentIndex && csv[currentIndex] == next;
}
