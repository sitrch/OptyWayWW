#include <stdio.h>
#include "libxl.h"

int main()
{
    BookHandle book = xlCreateXMLBook();
    if(book) 
    {
        SheetHandle sheet = xlBookAddSheet(book, L"Sheet1", 0);
        if(sheet) 
        {
            FormatHandle dateFormat;

            xlSheetWriteStr(sheet, 2, 1, L"Hello, World !", 0);
            xlSheetWriteNum(sheet, 3, 1, 1000, 0);

            dateFormat = xlBookAddFormat(book, 0);
            xlFormatSetNumFormat(dateFormat, NUMFORMAT_DATE);
            xlSheetWriteNum(sheet, 4, 1, xlBookDatePack(book, 2008, 4, 29, 0, 0, 0, 0), dateFormat);

            xlSheetSetCol(sheet, 1, 1, 12, 0, 0);
        }

        if(xlBookSave(book, L"example.xlsx")) printf("\nFile example.xlsx has been created.\n");
        xlBookRelease(book);
    }   

    return 0;
}
