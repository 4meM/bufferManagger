#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define FOR_LOOP(val,i, len) for (int i = val; i < len; ++i)
#define REVERSE_FOR_LOPP(i, start, end) for(int i = (end) - 1; i >= start; i--)
using namespace std;
#include "pageTable.h"


Page :: Page (string name, int frame_id, int EO){
    this -> frame_id = frame_id;
    this -> pag_id = name;
    this -> dirty_bit = EO; 
    this -> pin_count = 1;
    this -> hora = time(0);
}

void Page :: actualizar(string name, int EO){
    this -> pag_id = name;
    this -> dirty_bit = EO;
    this -> pin_count = 1;
    this -> hora = time(0);
}

void Page :: decrecer_pin(){
    if(pin_count >= 1){
        pin_count --;
    }
}

void Page :: increment_pin(){
    pin_count ++;
}

void Page :: cambiar_dirty(){
    dirty_bit = 1;
}








