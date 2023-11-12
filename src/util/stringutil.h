//
// Name: stringutil.h
// Author: Cory Torode
// Date: 11/8/23
//

#ifndef DNA_STRINGUTIL_H
#define DNA_STRINGUTIL_H

#include <string>

class StringUtil {
public:
    static void toUpperReference(std::string &s);

    static std::string toUpper(std::string s);

    static std::string toBinaryString(const std::string &s);

    static void replaceReference(std::string &s, char from, char to);

    static std::string replace(std::string s, char from, char to);
};


#endif //DNA_STRINGUTIL_H
