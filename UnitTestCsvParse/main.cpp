//
//  main.cpp
//  UnitTestCsvParse
//
//  Created by 佃佳典 on 2023/09/25.
//

#include <iostream>
#include <list>
#include "CsvParse.h"

int main(int argc, const char * argv[]) {
    
    FILE* fp = fopen("家計簿.csv", "r");
    if(fp != NULL)
    {
        fclose(fp);
    }
    else
    {
        printf("file not exist 家計簿.csv");
    }
    
    std::list<std::list<std::string>> csv;
    std::string text("");
    Parse(csv, text);
    return 0;
}
