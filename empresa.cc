#include "empresa.h"
#include <iostream>
#include <string>
using namespace std;

void crear (const string id,const instante &i,const float v,empresa &e){
    e.id=id;
    e.i=i;
    e.valor=v;
    e.abierta=false;
    crear(e.h);
}
string identificador(const empresa &e){
    return e.id;
}
instante instanteCotizacionCierre (const empresa &e){
    return e.i;
}
float valorCotizacionCierre(const empresa &e){
    return e.valor;
}
bool sesionAbierta(const empresa &e){
    return e.abierta;
}
bool introducir (empresa &e, const instante &i,const float v){
    if(sesionAbierta(e) && mayorInstante(i,ultimoInstante(e))){
        if(introducir(e.h,i,v)){
            return true;;           
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
void maximoValor(const empresa &e, float& v, bool &error){
    if(sesionAbierta(e)){
        bool error1;
        float aux;
        maximoValor(e.h,aux,error1);
        if(error1){
            error=true;
        }
        else{
            error=false;
            v=aux;
        }
    }
    else{
        error=false;
        v=valorCotizacionCierre(e);
    }
}
void instanteDeMayorValor (const empresa &e, instante& i, bool& error){
    if(sesionAbierta(e)){
        bool error1;
        instante aux;
        ordenDeMayorValor(e.h,aux,error1);
        if(error1){
            error=true;;
        }
        else{
            error=false;
            i=aux;
        }
    }
    else{
        error=false;
        i=instanteCotizacionCierre(e);
    }
}
instante ultimoInstante (const empresa &e){
    if(tamanyoHistorico(e)>0){
        bool error;
        instante aux;
        ordenDeUltimo(e.h,aux,error);
        return aux;
    }
    else{
        return instanteCotizacionCierre(e);
    }
}
float ultimoValor(const empresa &e){
    if(tamanyoHistorico(e)>0){
        bool error;
        float aux;
        valorDeUltimo(e.h,aux,error);
        return aux;  
    }
    else{
        return valorCotizacionCierre(e);
    }
}
int tamanyoHistorico(const empresa &e){
    return tamanyo(e.h);
}
bool esVacioHistorico (const empresa &e){
    return esVacio(e.h);
}
void abrirSesion (empresa &e,bool &error){
    if(sesionAbierta(e)){
        error=true;
    }
    else{
        e.abierta=true;
        error=false;
    }
}
void cerrarSesion (empresa &e,bool &error){
    if(sesionAbierta(e)){
        if(tamanyoHistorico(e)>0){
            e.i=ultimoInstante(e);
            e.valor=ultimoValor(e);
            liberar(e.h); 
        }
        e.abierta=false;
        error=false;
    }
    else{
        error=true;
    }
    
}
void listarHistorico (empresa &e, string &c){
    listar(e.h,c); 
}
void listarDatosBaseEmpresa (const empresa &e, string &c){
    string ins;
    generaInstanteCadena(e.i,ins);
    string val=to_string(e.valor);
    string abierta;
    if(sesionAbierta(e)){
        abierta="ABIERTA";
    }
    else{
        abierta="CERRADA";
    }
    c=e.id+';'+ins+';'+val+';'+abierta;
}