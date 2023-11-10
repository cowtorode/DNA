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

    /*
     * More efficiently builds strings by avoiding concatenation resizing
     */
    class StringBuilder {
        std::string building;

        // position of the first null character
        unsigned long firstNull;
    public:
        explicit StringBuilder(unsigned long length);

        void append(const std::string &s);

        void append(char c);

        inline std::string get() { return building; }
    };
};


#endif //DNA_STRINGUTIL_H
