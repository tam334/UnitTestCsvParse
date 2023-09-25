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
    std::list<std::list<std::string>> csv;
    std::string text("");
    Parse(csv, text);
    return 0;
}
