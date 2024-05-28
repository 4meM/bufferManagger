#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <iomanip>
#define FOR_LOOP(val,i, len) for (int i = val; i < len; ++i)
#define REVERSE_FOR_LOPP(i, start, end) for(int i = (end) - 1; i >= start; i--)
using namespace std;
#include "bufferM.h"

buffer :: buffer(int frames){ // DEFINE EL TAMA;O FIJO DE LOS FRAMES E INICIALIZA UNA COLA CON LOS FRAMES LIBRES
    this -> framesSize = frames;
    llenarFreeFrame();
}


int buffer :: isInTable(string indexPage){ // VERIFICA SI LA PAGINA ESTA EN LA PAGE TABLE Y REGRESA SU POSICION O -1 SI NO SE ENCUENTRA
    FOR_LOOP(0, i, paginas.size()){
        if(paginas[i].pag_id == indexPage){
            return i;
        }
    }
    return -1;
}

void buffer :: llenarFreeFrame (){ //INICIALIZA UNA COLA CON LOS FRAMES LIBRES(AL INICIO SON TODOS LIBRES)
    FOR_LOOP(0, i, framesSize){
        FreeFrame.push(i);
        
    }
} 

void buffer :: crearPagina (){ //SUBE UNA PAGINA AL BUFFER POOL CUANDO AUN HAY FRAMES LIBRES
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
        paginas[isInTable(namePag)].incrementar_pin();
        if(modo == "escritura"){
            paginas[isInTable(namePag)].cambiar_dirty();
        }
    }
}

void buffer :: subirPagina(){ //SE ENCARGA DE SUBIR UNA PAGINA AL BUFFER POOL, INDEPENDIENTEMENTE DE SI HAY O NO HAY ESPACIO EN EL BP
    if(FreeFrame.empty()){
        string name;
        string modo;
        cout << "Nombre de la pagina a usar\n";
        cin >> name;
        cout << "En que modo desea la pagina(Escritura o Lectura)\n";
        cin >> modo;
        if(isInTable(name) == -1){
            int indice = LRU(); 
            if(indice != -1){
                if(modo == "escritura"){
                    paginas[indice].actualizarPage(name, 1);
                } 
                else{
                    paginas[indice].actualizarPage(name, 0);
                }
            }
            else{
                cout << "\nTERMINA PROCESOS, NINGUNA PAGINA TIENE PINCOUNT = 0\n";
            }
        }
        else{
            paginas[isInTable(name)].incrementar_pin();
            if(modo == "escritura"){
                paginas[isInTable(name)].dirty_bit = 1;
                paginas[isInTable(name)].hora = time(0);
            }

        }
    }
    else{
        crearPagina();
    }
}

int buffer :: LRU(){ //POLITICA DE REEMPLAZO A LA PAGINA MAS ANTIGUA CON PINCOUNT = 0;
    vector<Page> pin;
    FOR_LOOP(0, i, paginas.size()){
        if(paginas[i].pin_count == 0){
            pin.push_back(paginas[i]);
        }
    }
    if(pin.empty()){
        return -1;
    }
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

void buffer :: imprimirBuffer (){ // IMPRIME TODAS LA PAGINAS QUE ESTAN EN EL BUFFER
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

void buffer :: terminar_proceso(string namePage){ //ACABA LA SOLICITUD DE UNA PAGINA DISMINUYENDO SU PINCOUNT
    int index = isInTable(namePage);        
    if(index != -1){
        paginas[index].decrecer_pin();
    }
}

void buffer :: run(){ //INTERFAZ CON LAS FUNCIONES NECESARIAS PARA OPERAR EL BUFFER 
    while(true){
        cout <<"\n";
        cout << "-------------------------------------------------------\n";
        cout << "DESEA SALIR DEL BUFFER MANAGGER? SI(0)\n";
        cout << "DESEA SUBIR UNA PAGINA? SI(1)\n";
        cout << "DESEA TERMINAR UN PROCESO? SI(2)\n";
        int opcion;
        cout << "Ingresa tu opcion: "; cin >> opcion;
        cout << "-------------------------------------------------------\n";
        cin.ignore();
        if(opcion == 1){
            subirPagina();
            cout << "\n\n";    
            cout << "****************************************************\n\n";
            
            imprimirBuffer();
            cout << "\n\n****************************************************\n";
        }
        else if(opcion == 2){
            cout << "Ingresa el nombre del proceso que desea terminar\n";
            string namePro;
            cin >> namePro;
            cin.ignore();
            terminar_proceso(namePro);
            cout << "SE FINALIZO EL PROCESO -> " << namePro << "\n";
            cout << "\n\n";
            cout << "**************************************************\n\n";
            imprimirBuffer();
            cout << "\n\n**************************************************\n";
            cout << "\n";
        }

        else if(opcion == 0){
            cout << "\nSALIENDO DEL BUFFER MANAGER QUE TENGA BUEN DIA! :D\n";
            break;    
        }
        else{
            cout << "\nESA OPCION NO ESTA DISPONIBLE\n";
        }
    }
}