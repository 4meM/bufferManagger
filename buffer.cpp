#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <iomanip>
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
    cout << "Nombre de la pagina a subir\n";
    getline(cin,namePag);
    cout << "En que modo desea la pagina(Escritura o Lectura)\n";
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
    if(FreeFrame.empty()){
        string name;
        string modo;
        cout << "Nombre de la pagina a usar\n";
        cin >> name;
        cout << "En que modo desea la pagina(Escritura o Lectura)\n";
        cin >> modo;
        if(isInTable(name) == -1){
            int indice = LRU(); 

            if(modo == "escritura"){
                paginas[indice].actualizar(name, 1);
            } 
            else{
                paginas[indice].actualizar(name, 0);
            }
        }
        else{
            paginas[isInTable(name)].increment_pin();
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
    FOR_LOOP(0, i, pin.size()){
        cout << pin[i].pag_id << " ";
    }
    cout << endl;

    time_t actualH = time(0);
    int max = 0; 
    int index;
    FOR_LOOP(0, i,pin.size()){
        if(actualH - pin[i].hora > max){
            max = actualH - pin[i].hora;
            index = pin[i].frame_id; 
        }
    }
    return index;
}

void buffer :: imprimirBuffer (){
        cout<< left << setw(10) << "frame_id"
            << left << setw(10) << "dirty_bit"
            << left << setw(15) << "Hora"
            << left << setw(20) << "pag_id"
            << left << setw(10) << "pin_count"
            << endl;
    FOR_LOOP(0, i, paginas.size()){
        cout << left << setw(10) << paginas[i].frame_id
        << left << setw(10) << paginas[i].dirty_bit
        << left << setw(15) << paginas[i].hora
        << left << setw(20) << paginas[i].pag_id
        << left << setw(10) << paginas[i].pin_count
        << endl;
    }
}

void buffer :: terminar_proceso(string namePage){
    int index = isInTable(namePage);        
    if(index != -1){
        paginas[index].decrecer_pin();
    }
}

void buffer :: run(){
    while(true){
        cout <<"\n";
        cout << "-------------------------------------------------------\n";
        cout << "Desea usar una pagina? SI(1) NO(0)\n";
        cout << "Desea terminar un proceso(2)\n";
        int valor;
        cout << "Ingresa tu opcion: "; cin >> valor;
        cout << "-------------------------------------------------------\n";
        cin.ignore();
        if(valor == 1){
            subirPagina();
            cout << "Pagina subida\n";
            cout << "\n\n";    
            cout << "****************************************************\n\n";
            
            imprimirBuffer();
            cout << "\n\n****************************************************\n";
        }
        else if(valor == 2){
            cout << "Ingresa el nombre del proceso que desea terminar\n";
            string namePro;
            cin >> namePro;
            cin.ignore();
            terminar_proceso(namePro);
            cout << "Se finalizo el proceso " << namePro << "\n";
            cout << "\n\n";
            cout << "**************************************************\n\n";
            imprimirBuffer();
            cout << "\n\n**************************************************\n";
            cout << "\n";
        }

        else{
            break;    
        }
    }
}