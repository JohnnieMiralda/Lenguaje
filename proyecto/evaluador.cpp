#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>		//Para la potencia
#include <string>
#include <vector>
using namespace std;

struct Nodo {

	string dato;
	Nodo* siguiente = NULL;

};

//Esto es una feature de C++14
template <class T>
constexpr T pi = T(3.1415926535897932385L);

//variables globales
    Nodo* pila = NULL;
	bool validacion=true;
    string* arreglo;
    vector <string> holi;
    auto t = 0;					//Feature de C++11
    auto expected = " ";

void Ingresar_Expresion() {
	do{
		cout << "Ingrese dimension: ";
		cin >> t;
	}while(t<3);

	arreglo = new string[t];

	//Ingresar expresion
	for (int i = 0; i < t; i++) {
		cout << "Ingrese un valor para [" << i << "]";
		cin >> arreglo[i];
	}
	system("cls");
	cout << endl;
}

//meter y sacar de la pila
string Sacar_Pila(Nodo*& pila, string& n) {
	Nodo* temp = pila;
	n = temp->dato;
	pila = temp->siguiente;
	//delete temp;
	return temp->dato;
}

void borrar(Nodo *&x){
	if(x->siguiente == NULL){
		delete x;
	}else{
		borrar(x->siguiente);
	}
	delete x;
}


void Agregar_Pila(Nodo*& pila, string n) {
	Nodo* nuevo_nodo = new Nodo();
	nuevo_nodo->dato = n;
	nuevo_nodo->siguiente = pila;
	pila = nuevo_nodo;
}
void Imprimir_Elementos(Nodo*& pila) {
	Nodo* temp;
	temp = pila;
	while (temp != NULL) {
		cout << temp->dato << " -> ";
		temp = temp->siguiente;
	}
}

//parse de string a int
double S2I(string x, string y, int op) {
	auto xx = stod(x);
    auto yy = stod(y);
    auto r= xx-xx;
	int xxx=xx;
	int yyy=yy;	
	try {
		switch (op) {

		case 1:		
			r = xx + yy;
			break;
		case 2:		
			r = yy - xx;
			break;
		case 3:		
			r = xx * yy;
			break;
		case 4:		
			r = yy / xx;
			break;
		case 5:	
			r = yyy % xxx;
			break;
		case 6:		
			r = pow(yy,xx);
			break;
		case 7:		//pi
			r = 0;
			break;
		default:
			r = 0;
			break;
		}
	}
	catch (invalid_argument const& e) {
		cout << "Bad input: invalid_argument thrown" << '\n';
	}
	catch (out_of_range const& e) {
		cout << "Integer overflow: out_of_range thrown" << '\n';
	}
	return r;
}

bool S2II(string x){
	try{
        int myint3 = stoi(x); 
     }catch (const invalid_argument& ia) {
       return false; 
     }catch (const out_of_range& i) {
       return false; 
     }
    return true;
}

string I2S(double n) {
	auto s = to_string(n);	
	return s;
}
bool modfloat(int x, double y){
	if(x==y){
		return false;
	}else{
		return true;
	}
}
void vaciar(){
	for (int i = 0; i < holi.size(); i++) {
		if (pila != NULL) {

			holi.push_back(Sacar_Pila(pila, arreglo[i]));

		}
	}
}

void vaciarvector(){
	holi.clear();	
}

void Expresion_Postfija() {

	string omitir[10];		//Aqui agrego el parentesis izquierdo que omito
	vaciarvector();
	//Llenamos el arreglo y la pila
	for (int i = 0; i < t; i++) {

		//Agregamos los operadores a la pila
		if (arreglo[i] == "(" || arreglo[i] == "^" || 
			arreglo[i] == "*" || arreglo[i] == "/" || 
			arreglo[i] == "%" || arreglo[i] == "+" || 
			arreglo[i] == "-" || arreglo[i] == "pi") {
			Agregar_Pila(pila, arreglo[i]);
		}
		else {		//Agregamos los numeros al arreglo
			if (arreglo[i] != ")") {
				holi.push_back(arreglo[i]);
			}
		}

		//Botamos el parentesis izquierdo!!
		if (arreglo[i] == ")") {

			do {
				holi.push_back(Sacar_Pila(pila, arreglo[i]));
				omitir[i] = Sacar_Pila(pila, arreglo[i]);
				break;
			} while (arreglo[i] != "(");

		}

	}
	
	//Vaciamos la pila
	vaciar();
	
	cout<<"pila v"<<endl;
	Imprimir_Elementos(pila);
	
	cout << "Imprimiendo resultado final..." << endl;
	for (int dim = 0; dim < holi.size(); dim++) {
		cout << "[" << dim << "]" << holi[dim] << endl;
	}

}
void Evaluar_Postfija() {
	
	cout << endl;
	auto i = 0;
	auto resultado = 0.0;
	string x = " ", y = " ", salida = " ";

	do {

		if (holi[i] == "^") {

			x = Sacar_Pila(pila, holi[i]);
			y = Sacar_Pila(pila, holi[i]);
			resultado = S2I(x, y, 6);
			salida = I2S(resultado);
			cout << "El resultado es : " << salida << endl;
			Agregar_Pila(pila, salida);

		}
		else if (holi[i] == "*") {

			x = Sacar_Pila(pila, holi[i]);
			y = Sacar_Pila(pila, holi[i]);
			resultado = S2I(x, y, 3);
			salida = I2S(resultado);
			cout << "El resultado es : " << salida << endl;
			Agregar_Pila(pila, salida);

		}
		else if (holi[i] == "/") {

			x = Sacar_Pila(pila, holi[i]);
			y = Sacar_Pila(pila, holi[i]);
			resultado = S2I(x, y, 4);
			salida = I2S(resultado);
			cout << "El resultado es : " << salida << endl;
			Agregar_Pila(pila, salida);
		}
		else if (holi[i] == "%") {

			x = Sacar_Pila(pila, holi[i]);
			y = Sacar_Pila(pila, holi[i]);
			resultado = S2I(x, y, 5);
			salida = I2S(resultado);
			cout << "El resultado es : " << salida << endl;
			Agregar_Pila(pila, salida);
		}else if (holi[i] == "+") {

			x = Sacar_Pila(pila, holi[i]);
			y = Sacar_Pila(pila, holi[i]);
			resultado = S2I(x, y, 1);
			salida = I2S(resultado);
			cout << "El resultado es : " << salida << endl;
			Agregar_Pila(pila, salida);
			
		}else if (holi[i] == "-") {
			
			x = Sacar_Pila(pila, holi[i]);
			y = Sacar_Pila(pila, holi[i]);
			resultado = S2I(x, y, 2);
			salida = I2S(resultado);
			cout << "El resultado es : " << salida << endl;
			Agregar_Pila(pila, salida);

		}else if (holi[i] == "pi") {

			x = Sacar_Pila(pila, holi[i]);
			y = Sacar_Pila(pila, holi[i]);
			resultado = S2I(x, y, 0);
			salida = I2S(resultado);
			cout << "El resultado es : " << salida << endl;
			Agregar_Pila(pila, salida);

		}
		else {
			Agregar_Pila(pila, holi[i]);
		}
		
		i++;	//No borrar esta linea

	} while (i < holi.size());
	vaciarvector();
	vaciar();
	cout << "Imprimiendo resultado final..." << endl;
	for (int dim = 0; dim < holi.size(); dim++) {
		cout << "[" << dim << "]" << holi[dim] << endl;
	}
	Imprimir_Elementos(pila);
	cout << endl;
	cout << "Expected: " << expected << endl;
	cout << "Found: " << salida << endl;

	if (salida == expected) {
		cout << "Test Case exitoso!" << endl;
		cout << endl;
	}
	else {
		cout << "Test case fallido!" << endl;
	}
	vaciarvector();
	vaciar();
}

void Validar() {

	for (int i = 0; i < t; i++) {
		cout << arreglo[i];
	}
	cout << endl;

	//Validaciones
	int i = 0;
	int pos = 0;
	int pos2 = 0;
	int izquierdo = 0;
	int derecho = 0;
	bool error = false;
	bool error2 = false;
	bool error3=false;
	bool error4=false;

	while (i < t){

		//Validar que no divida entre 0
		if (arreglo[i] == "/" || arreglo[i] == "%" && arreglo[i + 1] == "0") {
			error = true;
		}

		//Validar que cierre el parentesis
		//Contar cuantos parentesis izquierdos hay, y preguntar si hay la misma cantidad de parentesis derechos 
		if (arreglo[i] == "(")
			izquierdo++;

		if (arreglo[i] == ")")
			derecho++;

		//Validar caracteres no permitidos	ARREGLAR
		if (arreglo[i] == "+" || arreglo[i] == "-" || 
			arreglo[i] == "*" || arreglo[i] == "/" || 
			arreglo[i] == "%" || arreglo[i] == "^" || 
			arreglo[i] == "pi"|| arreglo[i] == "("|| arreglo[i] == ")") {

		}else {
			if(!S2II(arreglo[i])){
				error3=true;
			}else{
				int modx= stoi(arreglo[i]);
				double mody= stod(arreglo[i]);
				if(modfloat(modx,mody)){
					error4=true;
				}
			}
		}

		//Validar expresion infija incorrecta
		if ((t-1) == i){
			if(arreglo[i] == "+" || arreglo[i] == "-" || arreglo[i] == "*" || 
			   arreglo[i] == "/" || arreglo[i] == "%" || arreglo[i] == "^" ||
			   arreglo[i] == "pi") {
				error2 = true;
			}
		}

		i++;	//no borrar esta linea
	}

	if (error) {
		validacion=false;
		cout << "No puedes realizar una division entre 0!" << endl;
	}

	if (error2) {
		validacion=false;
		cout << "No puedes terminar una expresion con un operador!" << endl;
	}

	if(error3){
		validacion=false;
		cout << "Metiste un caracter invalido" << endl;
	}
	if(error4){
		validacion=false;
		cout << "No se puede hacer mod de floats" << endl;
	}

	if (izquierdo > derecho) {
		validacion=false;
		cout << "Olvidaste cerrar el parentesis izquierdo '('!" << endl;
	}
	vaciar();
	vaciarvector();
}

void test1(){ //7*(10-3)+2
    t=9;
	arreglo= new string[t];
    arreglo[0]="7";
    arreglo[1]="*";
    arreglo[2]="(";
    arreglo[3]="10";
    arreglo[4]="-";
    arreglo[5]="3";
    arreglo[6]=")";
    arreglo[7]="+";
    arreglo[8]="2";

    Validar();
	if(validacion){
		Expresion_Postfija();
		expected= "51";
		Evaluar_Postfija();
	}else{

	}
	vaciarvector();
}
void menuTest(){
    system("CLS"); 
    char op;
    bool x=true;
    do{
        cout<<"Que test-case desea ejecutar \n1. 7*(10-3)+2 \n2. 7+8* \n3. (3+)-6 \n9. Volver a menu\n"<<flush;
        cin>>op;
		vaciar();
		
        switch (op)
        {
        case '1':
            test1();
            x=true;
            break;
        case '2':

            x=true;
            break;
        case '3':

            x=true;
            break;
        case '4':

            x=true;
            break;
        case '5':

            x=true;
            break;
        case '6':

            x=true;
            break;
        case '7':

            x=true;
            break;
        case '8':

            x=true;
            break;
        case '9':
            cout<<"\nVolvera al menu\n\n\n";
            x=false;
            break;
        
        default:
            cout<<"\nOpcion invalida\n";
            x=true;
            break;
        }
    }while(x);     
}



int main(){
    char op;
    bool x=true;
    do{
        cout <<"Evaluador \n 1.Ejecutar \n 2.Correr test-cases \n 3.Salir  \n";
        cin >> op;
			
        switch (op)
        {
        case '1':

            Ingresar_Expresion();
            Validar();
			if(validacion){
				Expresion_Postfija();
				Evaluar_Postfija();
			}else{			}

			vaciarvector();
			vaciar();
            x=true;
            break;
        case '2':
            menuTest();
            x=true;
            break;
        case '3':
            cout<<"\nGracias por probar el sistema porfa deme todos los puntos inge";
            x=false;
            break;
        default:
            cout<<"\n\nOpcion invalida vuelve a tratar\n\n";
            break;
        }

    }while(x);
}

