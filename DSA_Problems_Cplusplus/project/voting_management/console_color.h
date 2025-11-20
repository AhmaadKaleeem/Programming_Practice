#pragma once
#include "libraries.h" 

inline void blue()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
}

inline void reset()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

inline void black()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
}

inline void yellow()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
}

inline void green()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
}
