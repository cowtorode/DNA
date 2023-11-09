//
// Created by cory on 11/8/23.
//

#ifndef DNA_STRINGUTIL_H
#define DNA_STRINGUTIL_H

#include <string>

class StringUtil {
public:
    static void toUpperReference(std::string &s);

    static std::string toUpper(std::string s);

    static std::string toBinaryString(const std::string &s);
};


#endif //DNA_STRINGUTIL_H
