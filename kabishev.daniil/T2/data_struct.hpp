#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>

namespace kabishev {

    struct DataStruct {
        char key1;
        unsigned long long key2; // Изменили тип с pair на unsigned long long
        std::string key3;
    };

    std::istream& operator>>(std::istream& in, DataStruct& input);
    std::ostream& operator<<(std::ostream& out, const DataStruct& src);

    bool compareDataStruct(const DataStruct& a, const DataStruct& b);

}

#endif
