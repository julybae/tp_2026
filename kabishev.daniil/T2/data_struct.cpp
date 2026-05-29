#include "data_struct.hpp"
#include "iofmtguard.hpp"

namespace kabishev {

struct DelimiterIO {
    char exp;
};

struct CharLitIO {
    char& ref;
};

struct HexUllIO {
    unsigned long long& ref;
};

struct StringIO {
    std::string& ref;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    char c = 0;
    in >> c;
    if (c != dest.exp) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, CharLitIO&& dest) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    in >> DelimiterIO{'\''} >> dest.ref >> DelimiterIO{'\''};
    return in;
}

std::istream& operator>>(std::istream& in, HexUllIO&& dest) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    return in >> std::hex >> dest.ref; // Автоматически парсит 0x / 0X префиксы
}

std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, DataStruct& input) {
    std::istream::sentry guard(in);
    if (!guard) return in;

    DataStruct temp{};
    in >> DelimiterIO{'('};

    for (int i = 0; i < 3; ++i) {
        std::string label;
        in >> DelimiterIO{':'} >> label;
        if (label == "key1") {
            in >> CharLitIO{temp.key1};
        } else if (label == "key2") {
            in >> HexUllIO{temp.key2};
        } else if (label == "key3") {
            in >> StringIO{temp.key3};
        } else {
            in.setstate(std::ios::failbit);
        }
    }

    // Вот тут обрабатываем то самое финальное двоеточие перед скобкой из логов тестов
    in >> DelimiterIO{':'} >> DelimiterIO{')'};

    if (in) {
        input = temp;
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry guard(out);
    if (!guard) return out;

    iofmtguard fmtguard(out); // Защищаем флаги потока вывода
    out << "(:key1 '" << src.key1 << "'"
        << ":key2 0x" << std::uppercase << std::hex << src.key2 // Вывод букв HEX в верхнем регистре
        << ":key3 \"" << src.key3 << "\":)";
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    return a.key2 < b.key2; // Сортируем просто по значению ULL числа
}

}
