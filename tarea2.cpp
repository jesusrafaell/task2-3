#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define M 1000 //total de hijos

//Vampiros
int table_vampires[M][M];
string name_vampires[M];
int n_vampires; //numero de vampieros

//Busquedas de Vampiros
string quest_vampieres[M]; //resultado de las las quest
int n_quest; //numero de quest resultas

//Clanes
string clanes[M]; //lideres de los clanes
int nro_clanes; //numero de clanes

//Nodos de la lista
struct nodo {
 int nro_clans;
 string boss_clan[M];
 int mienbros_clan[M];
 int generation_clan[M];
 int n_response;
 string response[M];
 nodo *next;
};

//Lista para Imprimir los casos de prueba
typedef struct nodo *Jlist;

//Ordenar los clanes alfabeticamente
void order_clans(){
    int salto = nro_clanes / 2;
    while(salto > 0){
        for(int i = salto; i < nro_clanes; i++){
            int j = i - salto;
            while(j >= 0){
                int k = j + salto;
                if(clanes[j].compare(clanes[k]) < 0){
                    j = -1;
                }else{      
                    string aux = clanes[j];
                    clanes[j] = clanes[k];
                    clanes[k] = aux;
                }
            }           
        }
        salto /= 2;
    }
}

//Cantidad de clanes
int clans(){
    int cont = 0;
    bool es_clan = false;
    for (int i = 0; i < n_vampires; i++){    
        for (int j = 0; j < n_vampires; j++){
            if(table_vampires[j][i] == 1){
                es_clan = true;
            }
        }
        if(!es_clan){
            clanes[cont] = name_vampires[i];
            cont++;
            //cout << name_vampires[i] << endl;
        }
        es_clan = false;
    }   
    nro_clanes = cont;
    return cont;
}

//Posicion del nombre actual
int position(string name){
    for (int i = 0; i < n_vampires; i++){
        if(!name_vampires[i].compare(name)){
            return i;
        }
    }
    name_vampires[n_vampires] = name;
    n_vampires++;
   return (n_vampires-1); 
}

//Si es una hoja del arbol o no
int is_hoja(int actual){
    for (int i = 0; i < n_vampires; i++){
        if(table_vampires[actual][i] == 1)
            return 0;
    }
    return 1;   
}

//Cantidad de mienbros de un clan
int cant_mienbros(int actual){
    int cont = 0;
    int cola[M];
    int t_cola = 0;
    int x = 0;
    while(1){
        for (int i = 0; i < n_vampires; i++){
            if(table_vampires[actual][i] == 1){
                cola[t_cola] = i;
                t_cola++;
            }
        }
        if(t_cola == x){
            break;
        }
        actual = cola[x];
        x++;
    }
    return t_cola;
}

//Numero de generaciones que tiene un clan
int cant_generation(int actual, int cont, int mcont){
    if(is_hoja(actual)){
        if(cont > mcont){
            return cont;
        }
        return mcont;
    }else{
        for(int i = 0; i < n_vampires; i++){
            if(table_vampires[actual][i] == 1){
                mcont = cant_generation(i, cont+1, mcont);
            }
        }
    }
    return mcont;
}

//Si un nombre esta en el clan o no
int in_clan(int actual, string name,int x){
    if(!name_vampires[actual].compare(name)){
        return 1;
    }else{
        for(int i = 0; i < n_vampires; i++){
            if(table_vampires[actual][i] == 1){
                x = in_clan(i,name, x);
            }
        }
    }
    return x;
}

//inicializar la tabla de vampiros y las variables
void init_table(){
    n_vampires = 0;
    n_quest = 0;
    for (int i = 0; i < M; i++){
        for (int j = 0; j < M; j++){
            table_vampires[i][j] = 0;
        }
        name_vampires[i] = " ";
    }    
}

//Donde seperar los dos nombres 
int mitad(string names){ //Divición de los nombres
    int cont = 0;
    for (int i = 0; i < sizeof(names); i++){
        if(names[i] == ' '){
            return i;
        }
    }
    return cont;
}

//Recorrer y imprimir los valores en la lista
void imprimir_lista(Jlist &list){
  Jlist Node = list;
  int cont=1;
  while (Node != NULL){
    cout << "Caso " << cont << ":" << endl; //Nro del caso
    cout << Node->nro_clans << endl;         //total de clanes
    for(int i = 0; i < Node->nro_clans; i++){
        cout << "Clan " << i+1 << ":" << endl << Node->boss_clan[i] << endl;  
        cout << Node->mienbros_clan[i] << " " << Node->generation_clan[i] << endl;      
    }
    for(int i = 0; i < Node->n_response; i++){
        cout << Node->response[i] << endl;
    }
    cout << endl;
    cont++;
    Node = Node->next;
  }
}

//Guardar los casos de pruebas resultos
void save_case(Jlist &list){
    Jlist Node = new (struct nodo);
    Node->next = NULL;
    Node->nro_clans = nro_clanes;
    //Se guardan los lideres de los clanes
    for(int i = 0; i < nro_clanes; i++){
        Node->boss_clan[i] = clanes[i];
    }
    //Se guardan la cant de mienbros y nro de generaciones de cada clan
    for (int i = 0; i < nro_clanes; i++){
        int pos = position(clanes[i]);
        Node->mienbros_clan[i] = cant_mienbros(pos) + 1;           //cantidad de mienbros del clan
        Node->generation_clan[i] = cant_generation(pos, 1, 1);     //las generaciones mas el lider
    }
    //Se guardan las respuestas a las busquedas de nombres
    Node->n_response = n_quest;
    int x=0;
    string line;
    for(int j = 0; j < n_quest; j++){
        line = quest_vampieres[j];
        for (int i = 0; i < nro_clanes; i++){
            int pos = position(clanes[i]);
            if(in_clan(pos, line, 0)){
                Node->response[x] = clanes[i];
                x++;
                break;
            }
        }
    }   
    //Agregar grupo a la lista
    if(list == NULL)
      list = Node;
    else{
      Jlist t = list;
      while(t->next != NULL){
        t = t->next;
      }
      t->next = Node;
    }
}

int main(){
    int c;
    cin >> c;
    Jlist list = NULL;
    for (int x = 1; x <= c; x++){
        string k,l;  //k fue convertido por l
        string line;
        init_table();
        int parte2=false;
        //Leer las lineas siguiente hasta que sea "."
        while(1){
            cin.sync();
            getline(cin, line);
            if (!line.compare(".")){
                nro_clanes=clans();
                order_clans();
                save_case(list);
                break;
            }
            int p = mitad(line);
            if(p == 0){  
                parte2=true; //Ya solo se puede preguntar por nombres
            }
            if(parte2){                 //Preguntar por un nombre
                quest_vampieres[n_quest] = line;
                n_quest++;
            }else{                      //Agregar vampiros
                k = line.substr(0,p);
                l = line.substr(p+1,sizeof(line));
                int a = position(k);
                int b = position(l);
                table_vampires[a][b] = 1;
            }
        }
    }
    imprimir_lista(list); //Imprimir los casos de pruebas
}