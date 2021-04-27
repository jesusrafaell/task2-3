#include <iostream>
#include <unistd.h>
#define M 500 

using namespace std;

//Nodos de la lista
struct nodo {
 int response;
 string maquina_turing[M];
 int cant_lines;
 nodo *next;
};

//Lista para Imprimir los casos de prueba
typedef struct nodo *Jlist;


int vSimbolos(char x, char y, int ns, char simbolos[])
{
    int u, v;
    u = v = 0;
    for (int i = 0; i < ns; i++){
        if (x == simbolos[i])
            u = 1;
        if (y == simbolos[i])
            v = 1;
    }
    if (u == 1 && v == 1)
    {
        return 1;
    }else{
        return 0;
    }
}

int main(){
    int c;
    cin >> c;
    Jlist list = NULL; //Lista para imprimir
    for (int x = 1; x <= c; x++){
        int n, t;
        cin >> n >> t;

        string simbols;
        char simbolos[100]; //simbolos permitidos
        //Simbolos del sistema

        int ns = 0; //numero de simbolos
        cin.sync();
        getline(cin, simbols);

        for (int i = 0; i < sizeof(simbols); i++)
        {
            if (simbols[i] != '\n' && simbols[i] != '\0' && simbols[i] != ' ')
            {
                simbolos[ns] = simbols[i];
                ns++;
                if (simbols[i + 1] != ' ')
                {
                    break;
                }
            }
        }
        simbolos[ns] = '~';
        ns++;

        //transiciones
        char transition[t][5];
        int states[t][5];

        //O F L E D (0 -> F, L lee, E escribe y D desplazamiento)
        for (int i = 0; i < t; i++){
            //Transiciones
            int oint, fint;
            char L, E, D;
            cin >> oint >> fint >> L >> E >> D;
            if(vSimbolos(L, E, ns, simbolos)){
                states[i][0] = oint; //estado
                states[i][1] = fint; //estado siguente
                transition[i][2] = L; //Leer
                transition[i][3] = E; //Escribir
                transition[i][4] = D; //Desplazamiento
            }else{
                cout << "Existe un Simbolo invalido es '" << L << "' (o) '" << E << "'" << endl;
                i--;
            }
        }

        string cadena;
        cin >> cadena;

        char cinta[M];
        for (int i = 0; i < M; i++){
            cinta[i] = '~';
        }
        int izcinta = 100;
        int nc = cadena.length();
        int dercinta = 100 + nc;
        for (int i = 0; i < nc; i++){
            cinta[izcinta+i] = cadena[i];
        }
     

        char actual = 0;
        int index = izcinta;
        int v = 0;
        Jlist Node = new (struct nodo);
        Node->next = NULL;
        
        Node->maquina_turing[0] = cinta;

        int n_lines = 1;
        while (1){
            //sleep(1);
            int v = 1;
            for (int i = 0; i < t; i++){
                if(states[i][0] == actual){
                    if(transition[i][2] == cinta[index]){
                        cinta[index] = transition[i][3];
                        v = 0;

                        if(transition[i][4] == 'D'){
                            index++;
                        }else if(transition[i][4] == 'I'){
                            index--;
                        }else if(transition[i][4] == 'S'){
                            v = 2;
                        }

                        Node->maquina_turing[n_lines] = cinta;
                        n_lines++;
                        actual = states[i][1];
                    }
                }
            }
            if(v == 1){
                Node->response = 0; //Rechazada
                break;
            }else if(v == 2){
                Node->response = 1; //Aceptada
                break;
            }
        }
        Node->cant_lines = n_lines;
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
    }// fin de los casos de prueba

    //Imprimir casos
    Jlist Node = list;
    for (int x = 1; x <= c; x++){
        cout << "Caso " << x << ":" << endl;
        for (int i = 0; i < Node->cant_lines; i++){
            int izcinta, dercinta;
            for (int j = 0; j < M; j++){
                if(Node->maquina_turing[i][j] != '~'){
                    izcinta = j;
                    break;
                }
            }

            for (int j = M-1; j > 0; j--){
                if(Node->maquina_turing[i][j] != '~'){
                    dercinta = j+1;
                    break;
                }
            }

            for (int j = izcinta; j < dercinta; j++){
                cout << Node->maquina_turing[i][j];
            }
            cout << endl;
        }
        if(Node->response){
            cout << "Aceptada" << endl; 
        }else{
            cout << "Rechazada" << endl;
        }
        cout << endl; //Linea en blanco
        Node = Node->next;
    }
    
}
