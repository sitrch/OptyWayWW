#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libxl.h"

const int maxRow = 20000;
const int maxCol = 256;

wchar_t* makeString()
{
    static wchar_t s[9] = {0};
    int i;
    
    for(i = 0; i < 8; ++i) {
        s[i] = 0x61 + rand() % 26;        
    }

    return s;
}

void test(int number)
{
    BookHandle book;
    SheetHandle sheet;
    clock_t t1, t2, t3;
    int row, col;
    double d, n;	

    printf("---------------------------------\n");
    if(number == 1) {
        printf("           strings               \n");
    } else {
        printf("           numbers               \n");
    }
    printf("---------------------------------\n");

    book = xlCreateXMLBook();
    if(book) {
        sheet = xlBookAddSheet(book, L"Sheet1", 0);
        if(sheet) {
            printf("writing %d cells... ", (maxRow - 1) * maxCol);
            t1 = clock();
            if(number == 1) {
                for(row = 1; row < maxRow; ++row) {
                    for(col = 0; col < maxCol; ++col) {
                        xlSheetWriteStr(sheet, row, col, makeString(), 0);
                    }
                }
            } else {
                for(row = 1; row < maxRow; ++row) {
                    for(col = 0; col < maxCol; ++col) {
                        xlSheetWriteNum(sheet, row, col, 1234, 0);
                    }
                }
            }
            printf("ok\n");
            t2 = clock();
            d = (double)(t2 - t1) / CLOCKS_PER_SEC;
            printf("time: %.3f sec\n", d);
            if(d > 0) {
                n = (maxRow - 1) * maxCol / d;
                printf("speed: %d cells/sec\n", (int)n);
            }
            printf("\n");

            printf("saving to xlsx... ");
            if(number == 1) {
                xlBookSave(book, L"perfstr.xlsx");
            } else {
                xlBookSave(book, L"perfnum.xlsx");
            }
            printf("ok\n");
            t3 = clock();
            printf("time: %.3f sec\n\n", (double)(t3 - t2) / CLOCKS_PER_SEC);

            printf("total time: %.3f sec\n", (double)(t3 - t1) / CLOCKS_PER_SEC);
            d = (double)(t3 - t1) / CLOCKS_PER_SEC;
            if(d > 0) {
                n = (maxRow - 1) * maxCol / d;
                printf("speed with saving on disk: %d cells/sec\n", (int)n);			
            }
            printf("\n");
        }

        xlBookRelease(book);
    }
}


int main()
{
    test(0);
    test(1);

    return 0;
}
