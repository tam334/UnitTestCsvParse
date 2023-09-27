#pragma once

#include <list>

namespace CsvParse
{
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
    void Parse(std::list<std::list<std::string>>& dst, std::string const& text);

    /// <summary>
    /// Csvのパーズ本体
    /// </summary>
    /// <param name="currentIndex">
    /// 現在の解析位置
    /// </param>
    int ParseCSV(std::list<std::list<std::string>>& dst,
                 std::string const& csv,
                 int currentIndex);
    /// <summary>
    /// 行のパーズ
    /// </summary>
    int ParseRow(std::list<std::list<std::string>>& dst,
                 std::string const& csv,
                 int currentIndex);
    
    /// <summary>
    /// 行の項目(トークンか""で囲まれた任意の文字列)のパーズ
    /// </summary>
    /// <return>
    /// 行の文字列
    /// </return>
    std::string ParseColumn(std::list<std::list<std::string>>& dst,
                            std::string const& csv,
                            int& currentIndex);
    /// <summary>
    /// トークンのパーズ
    /// </summary>
    /// <return>
    /// 文字列
    /// </return>
    std::string ParseToken(std::list<std::list<std::string>>& dst,
                           std::string const& csv,
                           int& currentIndex);
    
    /// <summary>
    /// ,などを含む任意の文字列のパーズ
    /// </summary>
    /// <return>
    /// 文字列
    /// </return>
    std::string ParseAnyString(std::list<std::list<std::string>>& dst,
                               std::string const& csv,
                               int& currentIndex);
    /// <summary>
    /// 改行のパーズ
    /// </summary>
    int ParseNewLine(std::string const& csv, int currentIndex);
    /// <summary>
    /// 次の文字が終端でなく、nextであるか
    /// </summary>
    bool CheckNextChar(std::string const& csv, int currentIndex, char next);
}
