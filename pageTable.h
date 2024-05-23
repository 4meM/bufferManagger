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
    Page (string name, int frame_id, int EO);
    void increment_pin();
    void decrecer_pin();
    void cambiar_dirty();
    void actualizar(string name, int EO);
    
};


#endif