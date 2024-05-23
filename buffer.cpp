#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#define FOR_LOOP(val,i, len) for (int i = val; i < len; ++i)
#define REVERSE_FOR_LOPP(i, start, end) for(int i = (end) - 1; i >= start; i--)
using namespace std;
#include "buffer.h"

buffer :: buffer(int frames){
    this -> framesSize = frames;
    llenarFreeFrame();
}


int buffer :: isInTable(string indexPage){
    FOR_LOOP(0, i, paginas.size()){
        if(paginas[i].pag_id == indexPage){
            return i;
        }
    }
    return -1;
}

void buffer :: llenarFreeFrame (){
    FOR_LOOP(0, i, framesSize){
        FreeFrame.push(i);
        
    }
} 

void buffer :: crearPagina (){
    string namePag;
    string modo;
    cout << "Nombre de la pagina a subir";
    getline(cin,namePag);
    cout << "En que modo desea la pagina(Escritura o Lectura)";
    getline(cin,modo);
    if(isInTable(namePag) == -1){
        
        if(modo == "escritura"){
            paginas.push_back(Page(namePag,FreeFrame.front(),1));
        } 
        else{
            paginas.push_back(Page(namePag,FreeFrame.front(),0));
    
        }
        FreeFrame.pop();
    }
    else{
        paginas[isInTable(namePag)].increment_pin();
        if(modo == "escritura"){
            paginas[isInTable(namePag)].cambiar_dirty();
        }
    }
}

void buffer :: subirPagina(){
    cout << "Funciona \n";
    if(FreeFrame.empty()){
        string name;
        string modo;
        cout << "Nombre de la pagina a subir\n";
        cin >> name;
        cout << "En que modo desea la pagina(Escritura o Lectura)\n";
        cin >> modo;

        int indice = LRU(); 

        if(modo == "escritura"){
            paginas[indice].actualizar(name, 1);
        } 
        else{
            paginas[indice].actualizar(name, 0);
        }
    }
    else{
        crearPagina();
    }
}

int buffer :: LRU(){
    vector<Page> pin;
    FOR_LOOP(0, i, paginas.size()){
        if(paginas[i].pin_count == 0){
            pin.push_back(paginas[i]);
        }
    }

    time_t actualH = time(0);
    int max = 0; 
    int index;
    FOR_LOOP(0, i,pin.size()){
        if(actualH - pin[i].hora > max){
            max = actualH - pin[i].hora;
            index = i; 
        }
    }
    return index;
}

void buffer :: imprimirBuffer (){
    FOR_LOOP(0, i, paginas.size()){
        cout <<paginas[i].frame_id << "," << paginas[i].dirty_bit <<", " << paginas[i].hora << ", " <<paginas[i].pag_id << ", " <<paginas[i].pin_count << "\n";
    }
}

void buffer :: terminar_proceso(string namePage){
    int index = isInTable(namePage);        
    if(index != -1){
        paginas[index].decrecer_pin();
    }
}