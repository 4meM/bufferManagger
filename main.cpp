#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define FOR_LOOP(val,i, len) for (int i = val; i < len; ++i)
#define REVERSE_FOR_LOPP(i, start, end) for(int i = (end) - 1; i >= start; i--)
using namespace std;
#include "bufferM.h"


int main() {
    int sizeFrames;
    cout << "Ingresa el numero de frames en tu Buffer Pool\n";
    cin >> sizeFrames;
    cin.ignore();
    buffer mi_buffer(sizeFrames);
    mi_buffer.run();
}