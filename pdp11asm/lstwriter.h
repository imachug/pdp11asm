// PDP11 Assembler (c) 15-01-2015 vinxru

#pragma once
#include <string>
#include "output.h"
#include "parser.h"
#include "fstools.h"

class LstWriter
{
public:
    class Remark
    {
    public:
        size_t addr;
        unsigned type;
        std::string text;
    };

    std::string buffer;
    size_t prev_writePtr;
    const char* prev_sigCursor;
    Output* out;
    Parser* p;
    bool hexMode;
    std::vector<Remark> remarks;

    inline LstWriter() { hexMode=false; prev_writePtr=0; prev_sigCursor=0; out=0; p=0; }
    void beforeCompileLine();
    void afterCompileLine3();
    void afterCompileLine2();

    void writeFile(const std::string& fileName);

    void appendBuffer(const char* data, size_t size);
    inline void appendBuffer(const char* data) { appendBuffer(data, strlen(data)); }

    void remark(size_t addr, unsigned type, const std::string& text);
};
