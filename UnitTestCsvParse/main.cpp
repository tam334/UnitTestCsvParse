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

int main(int argc, const char * argv[]) {
    
    std::ifstream ifs("家計簿.csv");
    if(ifs)
    {
        std::string text("");
        while(ifs)
        {
            std::string line;
            std::getline(ifs, line);
            text += line;
        }
        std::list<std::list<std::string>> csv;
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
