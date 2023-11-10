//
// Created by cory on 11/8/23.
//

#include "stringutil.h"

void StringUtil::toUpperReference(std::string &s) {
    for (char &c : s) {
        c = toupper(c);
    }
}

std::string StringUtil::toUpper(std::string s) {
    toUpperReference(s);
    return s;
}

std::string StringUtil::toBinaryString(const std::string &s) {
    // create new building of the final size
    std::string result(s.length() * 8, '\0');

    // iterate through each character of the building
    for (int i = 0; i < s.length(); i++) {
        char curr = s[i];
        // checks bit by bit the 1s and 0s of the char
        for (int j = 0; j < 8; j++) {
            bool bit = ((curr & (1 << j)) != 0); // 0 or 1, still needs converted to char
            result[8 * i + 7 - j] = bit + '0'; // + '0' converts bool value to char
        }
    }
    return result;
}

StringUtil::StringBuilder::StringBuilder(unsigned long length) : building(length, '\0'),
                                                                 firstNull(0) {
}

void StringUtil::StringBuilder::append(const std::string &s) {
    for (char c : s) {
        append(c);
    }
}

void StringUtil::StringBuilder::append(const char &c) {
    building[firstNull++] = c;
}
