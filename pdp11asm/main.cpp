// PDP11 Assembler (c) 15-01-2015 vinxru

#include "compiler.h"
#include <iostream>

int main(int argc, char** argv) {
#ifdef WIN32
    setlocale(LC_ALL, "RUSSIAN");
#endif

    printf("PDP11/8080 Assembler/C\nPRE PRE PRE ALPHA VERSION\n2017 (c) aleksey.f.morozov@gmail.com\n");
    try {
        Compiler c;

        // Ожидается один аргумент
        if(argc != 2) {
            std::cout << "Specify one file name on the command line" << std::endl;
            return 0;
        }
    
        // Компиляция
        c.compileFile(argv[1]);

        // Выход без ошибок
        std::cout << "Done" << std::endl;
        return 0;

        // Выход с ошибками
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}