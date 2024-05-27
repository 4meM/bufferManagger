#ifndef TABLE
#define TABLE

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <chrono>
#define FOR_LOOP(val,i, len) for (int i = val; i < len; ++i)
#define REVERSE_FOR_LOPP(i, start, end) for(int i = (end) - 1; i >= start; i--)
using namespace std;

class Page{
    public:
    int frame_id;
    string pag_id;
    int pin_count;
    bool dirty_bit;
    time_t hora;
    Page (string name, int frame_id, int EO); //AUTOR: SEBASTIAN
    void incrementar_pin(); // AUTOR: ERIK
    void decrecer_pin(); // AUTOR: ERIK
    void cambiar_dirty(); //AUTOR: ERIK
    void actualizarPage(string name, int EO); //AUTOR: KERIN
    
};


#endif