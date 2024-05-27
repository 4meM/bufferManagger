#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define FOR_LOOP(val,i, len) for (int i = val; i < len; ++i)
#define REVERSE_FOR_LOPP(i, start, end) for(int i = (end) - 1; i >= start; i--)
using namespace std;
#include "page.h"


Page :: Page (string name, int frame_id, int EO){ //RELLENA LOS METADATOS Y SOLICITA LOS NECESARIOS POR EL BUFFER_M
    this -> frame_id = frame_id;
    this -> pag_id = name;
    this -> dirty_bit = EO; 
    this -> pin_count = 1;
    this -> hora = time(0);
}

void Page :: actualizarPage(string name, int EO){ //ACTUALIZA EL CONTENIDO DE UNA PAGINA CUANDO ES SUBIDA AL BUFFER POOL
    this -> pag_id = name;
    this -> dirty_bit = EO;
    this -> pin_count = 1;
    this -> hora = time(0);
}

void Page :: decrecer_pin(){ //DISMINUYO EL PIN_COUNT PARA CUANDO ALGO TERMINE EL PROCESO DE USO
    if(pin_count >= 1){
        pin_count --;
    }
}

void Page :: incrementar_pin(){ //INCREMENTE EL PIN_COUNT PARA CUANDO SE VUELVA A SOLICITAR LA PAGINA
    pin_count ++;
}

void Page :: cambiar_dirty(){ // ACTUALIZA EL DIRTY BIT, ESTO CUANDO LA PAGINA ESTE EN MODO ESCRITURA
    dirty_bit = 1;
}








