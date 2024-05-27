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
#include "page.h"


class buffer{
    public:
    int framesSize;
    vector<Page> paginas;
    queue<int> FreeFrame;
    buffer(int);
    void run(); //AUTOR: ERIK
    int isInTable(string namePage); //AUTOR: KERIN
    void llenarFreeFrame(); //AUTOR: KERIN
    void crearPagina(); // AUTOR: SEBASTIAN
    void subirPagina(); // AUTOR: SEBASTIAN
    void imprimirBuffer(); // AUTOR: KERIN
    int LRU(); // AUTOR: SEBASTIAN
    void terminar_proceso(string namePage); // AUTOR: ERIK
};


#endif
