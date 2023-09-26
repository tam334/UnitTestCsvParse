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
int GetCharIndex(int row, int column)
{
    return 0;
}

namespace {
    //テスト
    TEST(NextCharTest, OK) {
        EXPECT_TRUE(CheckNextChar(text, GetCharIndex(1, 3), ','));
        EXPECT_FALSE(CheckNextChar(text, GetCharIndex(2, 9), '2'));
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
        
        RUN_ALL_TESTS();
        
        Parse(csv, text);
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


