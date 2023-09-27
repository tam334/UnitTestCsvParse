//
//  main.cpp
//  UnitTestCsvParse
//
//  Created by 佃佳典 on 2023/09/25.
//

#include <iostream>
#include <fstream>
#include <list>
#include "CsvParse.h"

#include "gtest/gtest.h"

std::list<std::list<std::string>> csv;

//行と文字数から文字位置を取得するヘルパー
//行と文字数はutf8の文字準拠、Atom等のテキストエディタのステータスバーなどで確認する
int GetCharIndex(std::string const& text, int row, int column)
{
    int currentline = 1;
    int currentindex = 0;
    while(currentindex < text.length() && currentline < row)
    {
        if(text[currentindex] == '\r' ||
           text[currentindex] == '\n')
        {
            if(currentindex + 1 < text.length() &&
               text[currentindex + 1] == '\n')
            {
                currentindex++;
            }
            currentline++;
        }
        currentindex++;
    }
    int c = 1;
    while(currentindex < text.length())
    {
        if(c == column)
        {
            return currentindex;
        }
        c++;
        if((text.at(currentindex) & 0x80) == 0)
        {
            currentindex += 1;
        }
        else if((text.at(currentindex) & 0xE0) == 0xC0)
        {
            currentindex += 2;
        }
        else if((text.at(currentindex) & 0xF0) == 0xE0)
        {
            currentindex += 3;
        }
        else if((text.at(currentindex) & 0xF8) == 0xF0)
        {
            currentindex += 4;
        }
    }
    return 0;
}

std::string ReadFileAll(std::string filename)
{
    std::string text("");
    std::ifstream ifs(filename);
    if(ifs)
    {
        text = "";
        while(ifs)
        {
            if(text != "")
            {
                text += '\n';
            }
            std::string line;
            std::getline(ifs, line);
            text += line;
        }
    }
    return text;
}

namespace {
    TEST(GetCharIndexTest, Normal)
    {
        {
            std::string text = ReadFileAll("家計簿LF.csv");
            EXPECT_EQ(GetCharIndex(text, 1, 3), 6);
            EXPECT_EQ(GetCharIndex(text, 2, 3), 25);
        }
        {
            std::string text = ReadFileAll("家計簿.csv");
            EXPECT_EQ(GetCharIndex(text, 1, 3), 6);
            EXPECT_EQ(GetCharIndex(text, 2, 3), 26);
        }
    }

    //テスト
    TEST(NextCharTest, Normal) {
        {
            std::string text = ReadFileAll("家計簿LF.csv");
            EXPECT_TRUE(CsvParse::CheckNextChar(text, GetCharIndex(text, 1, 3), ','));
            EXPECT_FALSE(CsvParse::CheckNextChar(text, GetCharIndex(text, 2, 9), '2'));
            EXPECT_TRUE(CsvParse::CheckNextChar(text, GetCharIndex(text, 7, 10), 'x'));
        }
        {
            std::string text = ReadFileAll("家計簿.csv");
            EXPECT_TRUE(CsvParse::CheckNextChar(text, GetCharIndex(text, 1, 3), ','));
            EXPECT_FALSE(CsvParse::CheckNextChar(text, GetCharIndex(text, 2, 9), '2'));
            EXPECT_TRUE(CsvParse::CheckNextChar(text, GetCharIndex(text, 7, 10), 'x'));
        }
    }

    TEST(ParseAnyStringTest, Normal){
        {
            std::string text = ReadFileAll("家計簿LF.csv");
            int index = GetCharIndex(text, 7, 2);
            EXPECT_EQ("ゲーセン,iidx", CsvParse::ParseAnyString(csv, text, index));
        }
        {
            std::string text = ReadFileAll("家計簿.csv");
            int index = GetCharIndex(text, 7, 2);
            EXPECT_EQ("ゲーセン,iidx", CsvParse::ParseAnyString(csv, text, index));
        }
    }

    TEST(ParseNewLineTest, Normal)
    {
        {
            std::string text = ReadFileAll("家計簿LF.csv");
            EXPECT_EQ(CsvParse::ParseNewLine(text, GetCharIndex(text, 1, 11)), GetCharIndex(text, 2, 1));
            EXPECT_EQ(CsvParse::ParseNewLine(text, GetCharIndex(text, 2, 1)), GetCharIndex(text, 2, 1));
        }
        {
            std::string text = ReadFileAll("家計簿.csv");
            EXPECT_EQ(CsvParse::ParseNewLine(text, GetCharIndex(text, 1, 11)), GetCharIndex(text, 2, 1));
            EXPECT_EQ(CsvParse::ParseNewLine(text, GetCharIndex(text, 2, 1)), GetCharIndex(text, 2, 1));
        }
    }

    TEST(ParseTokenTest, Normal)
    {
        {
            std::string text = ReadFileAll("家計簿LF.csv");
            int index = GetCharIndex(text, 4, 1);
            EXPECT_EQ(CsvParse::ParseToken(csv, text, index), "乾電池");
            index = GetCharIndex(text, 5, 12);
            EXPECT_EQ(CsvParse::ParseToken(csv, text, index), "5159");
        }
        {
            std::string text = ReadFileAll("家計簿.csv");
            int index = GetCharIndex(text, 4, 1);
            EXPECT_EQ(CsvParse::ParseToken(csv, text, index), "乾電池");
            index = GetCharIndex(text, 5, 12);
            EXPECT_EQ(CsvParse::ParseToken(csv, text, index), "5159");
        }
    }
}

int main(int argc, const char * argv[]) {
    
    std::string text = ReadFileAll("家計簿LF.csv");
        
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
    csv.clear();
    
    CsvParse::Parse(csv, text);
    for(std::list<std::list<std::string>>::iterator r = csv.begin();
        r != csv.end();
        ++r)
    {
        for(std::list<std::string>::iterator c = r->begin();
            c != r->end();
            ++c)
        {
            std::cout << *c << std::endl;
        }
    }
    
    
    return 0;
}


