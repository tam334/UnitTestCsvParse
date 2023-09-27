#pragma once

#include <list>

namespace CsvParse
{
    /// <summary>
    /// CSVを解析し、二次元配列形式で出力 \n
    //! 以下の構文木に基づきパース \n
    //! Csv = 行 {改行 行}* [改行] \n
    //! 行 = カラム {, カラム}* \n
    //! カラム = (トークン) | (" 任意の文字列 ") \n
    //! トークン = ,"\r\\nを除いた文字列 \n
    /// </summary>
    /// @param text
    ///  テキスト形式のCSV
    /// @param [in,out] dst
    ///  格納先の二次元配列
    void Parse(std::list<std::list<std::string>>& dst, std::string const& text);

    /// <summary>
    /// Csvのパーズ本体
    /// </summary>
    /// @param text
    ///  テキスト形式のCSV
    /// @param [in,out] dst
    ///  格納先の二次元配列
    /// @param currentIndex
    ///  現在の解析位置
    /// @return 解析後の解析位置
    int ParseCSV(std::list<std::list<std::string>>& dst,
                 std::string const& csv,
                 int currentIndex);
    /// <summary>
    /// 行のパーズ
    /// </summary>
    /// @param text
    ///  テキスト形式のCSV
    /// @param [in,out] dst
    ///  格納先の二次元配列
    /// @param currentIndex
    ///  現在の解析位置
    /// @return 解析後の解析位置
    int ParseRow(std::list<std::list<std::string>>& dst,
                 std::string const& csv,
                 int currentIndex);
    
    /// <summary>
    /// 行の項目(トークンか""で囲まれた任意の文字列)のパーズ
    /// </summary>
    /// @param text
    ///  テキスト形式のCSV
    /// @param [in,out] dst
    ///  格納先の二次元配列
    /// @param [in,out] currentIndex
    ///  現在の解析位置
    /// <return>
    /// 行の文字列
    /// </return>
    std::string ParseColumn(std::list<std::list<std::string>>& dst,
                            std::string const& csv,
                            int& currentIndex);
    /// <summary>
    /// トークンのパーズ
    /// </summary>
    /// @param text
    ///  テキスト形式のCSV
    /// @param [in,out] dst
    ///  格納先の二次元配列
    /// @param [in,out] currentIndex
    ///  現在の解析位置
    /// @return トークンの文字列
    std::string ParseToken(std::list<std::list<std::string>>& dst,
                           std::string const& csv,
                           int& currentIndex);
    
    /// <summary>
    /// ,などを含む任意の文字列のパーズ
    /// </summary>
    /// @param text
    ///  テキスト形式のCSV
    /// @param [in,out] dst
    ///  格納先の二次元配列
    /// @param [in,out] currentIndex
    ///  現在の解析位置
    /// @return 該当する文字列
    std::string ParseAnyString(std::list<std::list<std::string>>& dst,
                               std::string const& csv,
                               int& currentIndex);
    /// <summary>
    /// 改行のパーズ
    /// </summary>
    /// @param text
    ///  テキスト形式のCSV
    /// @param [in,out] dst
    ///  格納先の二次元配列
    /// @param currentIndex
    ///  現在の解析位置
    /// @return 解析後の解析位置
    int ParseNewLine(std::string const& csv, int currentIndex);
    /// <summary>
    /// 次の文字が終端でなく、nextであるか
    /// </summary>
    bool CheckNextChar(std::string const& csv, int currentIndex, char next);
}
