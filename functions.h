#pragma once
#include "stdio.h"
#include <string>
#include <iostream>
using namespace std;

void gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}

void puts(string x)
{
    cout << x << endl;
}

