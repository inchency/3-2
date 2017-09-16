#define STATES 8
#define SYMBOLS 2

int ST_TAB[STATES][SYMBOLS] = {
{ 1, -1 },
{ 2, 3 },
{ 2, 4 },
{ 5, 6 },
{ 5, 4 },
{ -1, 7 },
{ -1, 4 },
{ 5, -1 }
};