#ifndef DATUM_H
#define DATUM_H

#include <string>
#include <stdexcept>

typedef enum { D_INT = 0, D_BOOL, D_CODEBLOCK } datumty;

class Datum {
    public:
        Datum(const Datum &d);
        Datum(int i);
        explicit Datum(bool b);
        Datum(const char *s);
        Datum(std::string s);

        bool isInt();
        bool isBool();
        bool isCodeBlock();

        Datum &operator=(Datum &d);
        bool operator==(Datum &d);
        bool operator<(Datum &d);

        int getInt();
        bool getBool();
        std::string getCodeBlock();
        std::string toString();

    private:
        datumty ty;

        int idata;
        bool bdata;
        std::string sdata;
};

#endif
