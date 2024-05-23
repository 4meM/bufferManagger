#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define FOR_LOOP(val,i, len) for (int i = val; i < len; ++i)
#define REVERSE_FOR_LOPP(i, start, end) for(int i = (end) - 1; i >= start; i--)
using namespace std;
#include "buffer.h"


int main() {
    buffer mi_buffer(3);
    mi_buffer.subirPagina();
    mi_buffer.imprimirBuffer();
    mi_buffer.subirPagina();
    mi_buffer.imprimirBuffer();
    mi_buffer.subirPagina();
    mi_buffer.imprimirBuffer();
    mi_buffer.terminar_proceso("B");
    mi_buffer.terminar_proceso("A");
    mi_buffer.subirPagina();
    mi_buffer.imprimirBuffer();
}