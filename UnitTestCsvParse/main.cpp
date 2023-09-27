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
std::string text;

//行と文字数から文字位置を取得するヘルパー
int GetCharIndex(std::string const& text, int row, int column)
{
    int currentline = 1;
    int currentindex = 0;
    while(currentindex < text.length() && currentline < row)
    {
        if(text[currentindex] == '\r')
        {
            currentline++;
        }
        currentindex++;
    }
    int c = 1;
    while(currentindex < text.length() && text.at(currentindex) != '\r')
    {
        if(c == column)
        {
            std::cout << "GetCharIndex char : " << text.at(currentindex) << std::endl;
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

namespace {
    //テスト
    TEST(NextCharTest, Normal) {
        EXPECT_TRUE(CsvParse::CheckNextChar(text, GetCharIndex(text, 1, 3), ','));
        EXPECT_FALSE(CsvParse::CheckNextChar(text, GetCharIndex(text, 2, 9), '2'));
        EXPECT_TRUE(CsvParse::CheckNextChar(text, GetCharIndex(text, 7, 10), 'x'));
    }

TEST(ParseAnyStringTest, Normal){
    int index = GetCharIndex(text, 7, 2);
    EXPECT_EQ("ゲーセン,iidx", CsvParse::ParseAnyString(csv, text, index));
}
}

int main(int argc, const char * argv[]) {
    
    std::ifstream ifs("家計簿.csv");
    if(ifs)
    {
        text = "";
        while(ifs)
        {
            std::string line;
            std::getline(ifs, line);
            text += line;
        }
        
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
    }
    else
    {
        printf("file not exist 家計簿.csv");
    }
    
    
    return 0;
}


