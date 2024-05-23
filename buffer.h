#ifndef BUFFER
#define BUFFER
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
#define FOR_LOOP(val,i, len) for (int i = val; i < len; ++i)
#define REVERSE_FOR_LOPP(i, start, end) for(int i = (end) - 1; i >= start; i--)
using namespace std;
#include "pageTable.h"


class buffer{
    public:
    int framesSize;
    vector<Page> paginas;
    queue<int> FreeFrame;
    buffer(int);
    int isInTable(string namePage);
    void llenarFreeFrame();
    void crearPagina();
    void subirPagina();
    void imprimirBuffer();
    int LRU();
};


#endif
