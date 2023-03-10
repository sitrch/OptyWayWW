#include <iostream>
#include "libxl.h"

using namespace libxl;

const wchar_t* filename = L"..\\generate\\example.xlsx";

int main() 
{
    Book* book = xlCreateXMLBook();
    if(book)
    {
        if(book->load(filename))
        {
            Sheet* sheet = book->getSheet(0);
            if(sheet)
            {
                const wchar_t* s = sheet->readStr(2, 1);
                if(s) std::wcout << s << std::endl << std::endl;                
                
                std::cout << sheet->readNum(4, 1) << std::endl;
                std::cout << sheet->readNum(5, 1) << std::endl;
                const wchar_t* f = sheet->readFormula(6, 1);
                if(f) std::wcout << f << std::endl << std::endl;

                int year, month, day;
                book->dateUnpack(sheet->readNum(8, 1), &year, &month, &day);
                std::cout << year << "-" << month << "-" << day << std::endl;
            }
        }
        else
        {
            std::cout << "At first run generate !" << std::endl;
        }

        book->release();
    }

    return 0;
}
