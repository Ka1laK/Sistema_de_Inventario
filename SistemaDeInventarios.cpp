#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iomanip>
#include<time.h>
#include<vector>
#include<cmath>
//#include<bits/stdc++.h>
using namespace std;

const int periodoMAXIMO = 3;

struct producto{	
	int numero;
	char nombre[30];
	char marca[20];
  	char codigo[10];  //sku del producto       
	float precio[periodoMAXIMO];      
	int stock[periodoMAXIMO];  
	int cantidad_vendida[periodoMAXIMO];      
};

struct promedioABC{
	producto pp;
	float promedioPpp;
	float promedioVpp;
	float valor_de_utilizacionpp;
};
//           SISTEMA DE INVENTARIOS
//           https://github.com/Ka1laK
void menu();
void sub_menu1();
void sub_menu6();
void limitacion_del_proceso(int);
void agregar_stock(int,int&,producto*);
void verificar_stock(producto*);
void eliminar_stock();
void reescribir();
void modificar_stock(int&,producto*, int&);
void metodo_modificar(int,int,producto*, int&);
void promediosABCreal(vector<promedioABC>& premediosParaABC, producto* p1, int periodo, int& totalDeVentas);
void ordenamientoDePromedios(vector<promedioABC>& promediosParaABC);
void metodoAgrupacionPareto(int totalDeVentas, vector<promedioABC> promediosParaABC);

int main(){  
  	system("COLOR 02");
	int periodo=0, validar = 1;
	ifstream archivo("validacion.dat", std::ios::binary);
	if(archivo){
        archivo.read(reinterpret_cast<char*>(&periodo), sizeof(periodo));
        archivo.close();
    }else{
    	do{
    		cout << "*********************************************************************" << endl;
    		cout << "              ETAPA DE LIMITACION DEL PROYECTO - PERIODO             " << endl;
    		cout << "*********************************************************************" << endl;
    		cout << "\n Determinaremos el numero de meses para la elaboracion del analisis" << endl;
    		cout << "\n El proyecto disponde de una capacidad de [1-3] meses:" << endl;
			cout << " -> Numero de meses para el analisis: "; cin >> periodo;
    		if( (periodo<1) || (periodo>3)){
    			cout << "\n El intervalo aceptado es de 1 mes minimo y 3 maximo! " << endl;
    			cout << "\n\n\n";
    			system("pause"); system("cls");
			}else{
				validar = 0;
			}
		}while(validar!=0);
        ofstream nuevoArchivo("validacion.dat", std::ios::binary);
        nuevoArchivo.write(reinterpret_cast<const char*>(&periodo), sizeof(periodo));
        nuevoArchivo.close();
    }
	producto *p1;
	vector<int> promediosPrecios;
	vector<int> promediosVentas;
	vector<promedioABC> promediosParaABC;
	int totalDeVentas = 0;
	int cantidad_de_productos=0, cont=0, N=100;	
		
	system("COLOR F0");
	
	int opc=0,opc1=0, opc2=0, e=0;
	p1 = (producto*)malloc(N*sizeof(producto));
	if(p1==NULL){
		printf("No se ha podido reservar la memoria dinamica\n");
	}
	system("cls");
	do{
		menu();
		cout<<" Ingrese un opcion: ";
		cin>>opc;
		switch(opc){
			case 1:
				system("cls");
				limitacion_del_proceso(periodo);
				system("pause");
				system("cls");
				break;
			case 2:
				system("cls");
				verificar_stock(p1); 
				system("pause");
				system("cls");
				break;
			case 3:
				do{
					sub_menu1();
					cout<<" Ingrese un opcion: ";
					cin>>opc1;
					switch(opc1){
						case 1:
							agregar_stock(periodo,cont,p1);
							system("pause");
							system("cls");
							break;
						case 2:
							eliminar_stock();
							system("pause");
							system("cls");
							break;
						case 3:
							system("cls");
							break;
						default:
							cout << " \n Elija una opcion valida por favor!\n" <<endl;
							system("pause"); system("cls");
							break;
					}
				}while(opc1!=3);
				break;
				
			case 4:
				system("cls");
				modificar_stock(periodo,p1, totalDeVentas);
				system("pause");
				system("cls");
				break;
				
			case 5:
				system("cls");
				promediosParaABC.clear();
				do{
					sub_menu6();
					cout<<" Ingrese una opcion: "; cin>>opc2;
					switch(opc2){
						case 1: 
							system("cls");
							promediosParaABC.clear();
							promediosABCreal(promediosParaABC, p1, periodo, totalDeVentas);
							system("pause"); system("cls");
							break;
						case 2:
							system("cls");
							ordenamientoDePromedios(promediosParaABC);
							system("pause"); system("cls");
							break;
						case 3:
							system("cls");
							opc2 = 3;
							break;
						deafault:
							cout << " \nElija una opcion valida por favor!\n" <<endl;
							system("pause"); system("cls");
							break;
					}
				}while(opc2!=3);
				break;
				
			case 6:
				system("cls");
				metodoAgrupacionPareto(totalDeVentas, promediosParaABC);
				system("pause"); system("cls"); 
				break;
				
				
			case 7:
				system("cls");
				system("cls");
        		cout << "\n";
        		cout << "\n";
        		cout << " ----------------------------------------------------" << endl;
        		cout << "                      <<<<<<CREDITOS>>>>>>            " << endl;
        		cout << " ----------------------------------------------------" << endl;
        		cout << "\t\t\t-Aldana, Mauricio"<<endl;
        		cout << "\t\t\t-Castillo, Yon"<<endl;
        		cout << "\t\t\t-Escribas, Daniel"<<endl;
        		cout << "\t\t\t-Morales, Cristian"<<endl;
        		cout << "\t\t\t-Principe, Ivan"<<endl;
        		cout << "\t\t\t-Saavedra, Rissel"<<endl;
        		cout << " ----------------------------------------------------" << endl;
				cout << "\n";
        		cout << "\n";
        		cout << "\n";
        		system("pause"); system("cls"); 
				break;
					
				
				
	      	case 8:
	        	system("cls");
				system("cls");
        		cout << "\n";
        		cout << "\n";
        		cout << " ----------------------------------------------------" << endl;
        		cout << "            Gracias por usar el programa!            " << endl;
        		cout << " ----------------------------------------------------" << endl;
        		cout << "\n";
        		cout << "\n";
        		cout << "\n";
				break;
			
			default:
				cout << " \n Elija una opcion valida por favor!\n" <<endl;
				system("pause"); system("cls");
				break;
		}
	}while(opc!=8);
	
	return 0;
}

void menu(){
	cout<<" ******************************************************"<<endl;
    cout<<" *          BIENVENIDO AL REGISTRO DE INVENTARIO      *"<<endl;
    cout<<" ******************************************************"<<endl;
    cout<<"  1  .- Periodo establecido"<<endl;
    cout<<"  2  .- Listar el Inventario completo."<<endl;
    cout<<"  3  .- Gestion de Articulos"<<endl;
    cout<<"  4  .- Ingresar cantidad vendida"<<endl; 
    cout<<"  5  .- Analisis metodologico (valor de utilizacion)"<<endl; 
    cout<<"  6  .- Clasificacion de inventario ABC"<<endl;
    cout<<"  7  .- Creditos"<<endl;
    cout<<"  8  .- Salir"<<endl;
	cout<<" ------------------------------------------------------"<<endl;
}
void sub_menu1(){
	system("cls");
	cout<<" ***********************************"<<endl;
    cout<<" *        GESTIONAR ARTICULOS      *"<<endl;
    cout<<" ***********************************"<<endl;
    cout<<"  1  .- Agregar producto"<<endl;
    cout<<"  2  .- Eliminar producto"<<endl;
    cout<<"  3  .- Volver"<<endl;
    cout<<" ------------------------------------"<<endl;
}
void sub_menu6(){
	system("cls");
	cout<<" **************************************************************** "<<endl;
    cout<<" *           METODOLOGIA ABC POR VALOR DE UTILIZACION           * "<<endl;
    cout<<" **************************************************************** "<<endl;
    cout<<" >> Asegurese de regenerar estos datos cada que cambie el almacen "<<endl;
    cout<<" ---------------------------------------------------------------- "<<endl;
    cout<<"  1  .- Promedios de cada producto"<<endl;
    cout<<"  2  .- Tabla de valor de utilizacion de cada producto"<<endl;
    cout<<"  3  .- Volver"<<endl;
    cout<<" ---------------------------------------------------------------- "<<endl;
}

void limitacion_del_proceso(int periodo){
	cout << "\n\n";
  	cout<<" ************************************************************************"<<endl;
  	cout<<" * El periodo asignado para la gestion de inventarios fue de: " << periodo << " mes(es) *" << endl;
  	cout<<" ************************************************************************"<<endl;
  	cout << "\n\n";
  	system("pause");
}
void agregar_stock(int periodo, int& cont,producto* p1){

	FILE *f;
	f=fopen("inventario1.dat","ab");
	if(f==NULL)
		exit(1);
	system("cls");
	p1[cont].numero=cont+1;
  	printf("Ingrese el codigo del producto:"); 
  	fflush(stdin);
  	cin.getline(p1[cont].codigo,10,'\n');
	printf("Ingrese el nombre del producto: ");
	fflush(stdin);
	cin.getline(p1[cont].nombre,30,'\n');
	printf("Ingrese la marca del producto: ");
	fflush(stdin);
	cin.getline(p1[cont].marca,30,'\n');
	
	for (int i = 0; i < periodo; i++) {
        p1[cont].cantidad_vendida[i] = 0;
    }
    
	for(int i=0;i<periodo;i++){
		printf("\t------>  Periodo %d ",i+1);
		printf("<------\n");
		printf("Ingrese el stock: ");
		cin>>p1[cont].stock[i];
		printf("Ingrese el precio: ");
		cin>>p1[cont].precio[i];   
	}
	fwrite(&p1[cont],sizeof(producto),1,f);
	fclose(f);
	cont++;  
}
void verificar_stock(producto* p1){
	int opc=0,i=0;
	char code[100];
	FILE *f;
	f=fopen("inventario1.dat","rb");
	if(f==NULL){
		cout << "\n El inventario esta vacio!" << endl;
		cout << " Ingrese productos o importe un archivo .dat" << endl;
		cout << "\n\n";
		system("pause");
	}else{
		printf(" De que mes desea ver el inventario: ");
		cin>>opc;
		switch(opc){
		case 1:
			fread(&p1[i],sizeof(producto),1,f);
			cout<<"------------------------------------------------------------------------------------------------------"<<endl;
			cout<< setw(10) <<" Codigo"<< setw(15) <<"Producto" << setw(15) << "Marca" << setw(15) << "Precio" << setw(15) << "Cantidad" <<setw(25)<<"Cantidad vendida"<<endl;
			cout<<"------------------------------------------------------------------------------------------------------"<<endl;
			while(!feof(f)){
				cout<<setw(10)<<p1[i].codigo<<setw(15)<< p1[i].nombre << setw(15) << p1[i].marca << setw(15) << p1[i].precio[0] << setw(15) << p1[i].stock[0] << setw(25) <<p1[i].cantidad_vendida[0]<<endl;
				i++;
				fread(&p1[i],sizeof(producto),1,f);
			}
			cout<<"\n\n\n";
			fclose(f);
			break;
		case 2:
			fread(&p1[i],sizeof(producto),1,f);
			cout<<"------------------------------------------------------------------------------------------------------"<<endl;
			cout<< setw(10) <<" Codigo"<< setw(15) << "Producto" << setw(15) << "Marca" << setw(15) << "Precio" << setw(15) << "Cantidad" <<setw(25)<<"Cantidad vendida"<<endl;
			cout<<"------------------------------------------------------------------------------------------------------"<<endl;
			while(!feof(f)){
				cout<< setw(10) <<p1[i].codigo<<setw(15)<< p1[i].nombre << setw(15) << p1[i].marca << setw(15) << p1[i].precio[1] << setw(15) << p1[i].stock[1] << setw(25) <<p1[i].cantidad_vendida[1]<<endl;
				i++;
				fread(&p1[i],sizeof(producto),1,f);
			}
			cout<<"\n\n\n";
			fclose(f);
			break;
		case 3: //maximo de periodos
			fread(&p1[i],sizeof(producto),1,f);
			cout<<"------------------------------------------------------------------------------------------------------"<<endl;
			cout<< setw(10) << " Codigo" << setw(15) << "Producto" << setw(15) << "Marca" << setw(15) << "Precio" << setw(15) << "Cantidad" <<setw(25)<<"Cantidad vendida"<<endl;
			cout<<"------------------------------------------------------------------------------------------------------"<<endl;
			while(!feof(f)){
				cout<< setw(10) <<p1[i].codigo<<setw(15)<< p1[i].nombre << setw(15) << p1[i].marca << setw(15) << p1[i].precio[2] << setw(15) << p1[i].stock[2] << setw(25) <<p1[i].cantidad_vendida[2]<<endl;
				i++;
				fread(&p1[i],sizeof(producto),1,f);
			}
			cout<<"\n\n\n";
			fclose(f);
			break;
		}
	}	
}
void modificar_stock(int& t,producto* p1, int& totalDeVentas){
	int e=0,elegir=0;
	system("cls");
	cout << "\n Para regresar presione <4> " << endl;
	printf(" Ingrese el mes al que desea agregar una venta: ");	
	cin>>elegir;
	switch(elegir){
		case 1:
			elegir--;
			metodo_modificar(elegir,e,p1,totalDeVentas);
			break;
		case 2:
			elegir--;
			metodo_modificar(elegir,e,p1,totalDeVentas);
			break;
		case 3:
			elegir--;
			metodo_modificar(elegir,e,p1,totalDeVentas);
			break;
		case 4:
			system("cls");
			break;
		default:
			cout << " \n Elija una opcion valida por favor!\n" <<endl;
			system("pause"); system("cls");
			break;		
	}
}
void metodo_modificar(int elegir,int e,producto* p1, int& totalDeVentas){
	int opt=0,pos=0,i=0;
	char cod[10];
	totalDeVentas = 0;
	FILE *f;
	f=fopen("inventario1.dat","r+b");
	if(f==NULL){
		exit(1);
	}	
	system("cls");
	cout<<" Ingrese el codigo del producto: ";
	fflush(stdin);
	cin.getline(cod,10,'\n');
	fread(&p1[i],sizeof(producto),1,f);  
	while(!feof(f)){
		if(strcmp(cod,p1[i].codigo)==0){
			cout<<"\n Ingrese la cantidad vendida: ";
			cin>>p1[i].cantidad_vendida[elegir];
			if (p1[i].cantidad_vendida[elegir] <= p1[i].stock[elegir]) {
                pos = ftell(f) - sizeof(producto);
                fseek(f, pos, SEEK_SET);
                fwrite(&p1[i], sizeof(producto), 1, f);
                cout << "\n Se modifico la cantidad vendida para el producto exitosamente!" << endl;
            } else {
                cout << "\n No se puede modificar la cantidad vendida. La cantidad supera el stock disponible!" << endl;
            }
			e=1;
			break;
		}
		i++;
		fread(&p1[i],sizeof(producto),1,f);
	}
	cout<<"\n\n\n";
	if(e==0){
		printf(" No existe el producto\n");
	}
	fclose(f);
}
void reescribir(){
	producto p1;
	FILE *f;
	FILE *arch;
	f=fopen("inventario1.dat","wb");
	arch=fopen("Inventadonew1.dat","rb");
	fread(&p1,sizeof(producto),1,arch);
	while(!feof(arch)){
		fwrite(&p1,sizeof(producto),1,f);
		fread(&p1,sizeof(producto),1,arch);
	}
	fclose(f);
	fclose(arch);
}
void eliminar_stock(){
	char code[10];
	producto p1;
	FILE *arch;
	FILE *f;
	arch=fopen("Inventadonew1.dat","wb");
	f=fopen("inventario1.dat","rb");
	system("cls");
	printf(" Ingrese el codigo del producto a eliminar: ");
	fflush(stdin);
	cin.getline(code,10,'\n');
	fread(&p1,sizeof(producto),1,f);
	while(!feof(f)){
		if(strcmp(code,p1.codigo)==0){
			cout<<"\n Se ha eliminado el producto exitosamente!\n";
		}else{
			fwrite(&p1,sizeof(producto),1,arch);
			cout << "\n Codigo erroneo, no se ha encontrado el producto! \n";
			cout << "\n\n";
		}
		fread(&p1,sizeof(producto),1,f);
	}
	fclose(arch);
	fclose(f);
	reescribir();
}

void promediosABCreal(vector<promedioABC>& promediosParaABC, producto* p1, int periodo, int& totalDeVentas){
	
  	int j=0, y=0, i=0;
	float sumaPrecios = 0, sumaVentas = 0;
	float promedioP = 0, promedioV = 0;
	float valor_de_utilizacion = 0;
	totalDeVentas = 0;
	promedioABC axuliar;
	
	FILE *f;
	f=fopen("inventario1.dat","rb");
	fread(&p1[j],sizeof(producto),1,f);

	while(!feof(f)){
		
		sumaVentas = 0;
		sumaPrecios = 0;
		
		while(y<periodo){	

			sumaPrecios = sumaPrecios + p1[j].precio[y];
			sumaVentas = sumaVentas + p1[j].cantidad_vendida[y];

			y++;
			axuliar.pp = p1[j];
		}
		
		cout << fixed << setprecision(1);
		promedioP = sumaPrecios/periodo;
		promedioV = sumaVentas/periodo;
		valor_de_utilizacion = (promedioP*promedioV);
		totalDeVentas += promedioV;
		
		axuliar.promedioPpp = promedioP;
		axuliar.promedioVpp = promedioV;
		axuliar.valor_de_utilizacionpp = valor_de_utilizacion;
		
		promediosParaABC.push_back(axuliar); 
		
		promedioP = 0;
		promedioV = 0;
		valor_de_utilizacion = 0;
		y=0;
		j++;
		
		fread(&p1[j],sizeof(producto),1,f);
	}
	
	cout << " ***************************************** " <<endl;
	cout << " *   RELACION DE PROMEDIOS Y PRODUCTOS   * " <<endl;
	cout << " ***************************************** " <<endl;
	for (const promedioABC& promedio : promediosParaABC) {
        	cout << " Producto: " << promedio.pp.nombre << " " << promedio.pp.marca << endl;
        	cout << " Precio promedio: " << promedio.promedioPpp << endl;
        	cout << " Ventas promedio: " << promedio.promedioVpp << endl;
        	cout << " Valor de utilizacion: " << promedio.valor_de_utilizacionpp << endl;
        	cout << " -------------------------------" << endl;
   	 	}
}
void ordenamientoDePromedios(vector<promedioABC>& promediosParaABC) {
    int size = promediosParaABC.size();
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (promediosParaABC[j].valor_de_utilizacionpp < promediosParaABC[j + 1].valor_de_utilizacionpp) {
                swap(promediosParaABC[j], promediosParaABC[j + 1]);
            }
        }
    }

    int orden = 1;
	cout << " *******************************************************************" <<endl;
	cout << " *               ORDENAMIENTO SEGUN VALOR DE UTILIZACION           *" <<endl;
	cout << " *******************************************************************" <<endl; 
	cout<< setw(5) << " Orden" << setw(15) << "Producto" << setw(15) << "Marca" << setw(30) << "Valor de utilizacion" <<endl; 
	cout << " -------------------------------------------------------------------" <<endl;   
    for (const auto& promedio : promediosParaABC) {
        cout << setw(5) << orden << "#" << setw(15) << promedio.pp.nombre << setw(15) << promedio.pp.marca << setw(30) << promedio.valor_de_utilizacionpp << endl;
    	orden++;
	}
    cout << "\n\n";
}
void metodoAgrupacionPareto(int totalDeVentas, vector<promedioABC> promediosParaABC) {
    int sizeGrupoA = 0, sizeGrupoB = 0, sizeGrupoC = 0;
    vector<promedioABC> grupoA;
    vector<promedioABC> grupoB;
    vector<promedioABC> grupoC;

    sizeGrupoA = totalDeVentas * 0.2;           
    sizeGrupoB = totalDeVentas * 0.3;           
    sizeGrupoC = totalDeVentas - sizeGrupoA - sizeGrupoB;     

    float sumaPromedioVpp = 0;
    int i = 0;

    while (i < promediosParaABC.size() && sumaPromedioVpp < sizeGrupoA) {
        grupoA.push_back(promediosParaABC[i]);   
        sumaPromedioVpp += promediosParaABC[i].promedioVpp;
        i++;
    }

    while (i < promediosParaABC.size() && sumaPromedioVpp < sizeGrupoA + sizeGrupoB) {
        grupoB.push_back(promediosParaABC[i]);
        sumaPromedioVpp += promediosParaABC[i].promedioVpp;
        i++;
    }
    
    while (i < promediosParaABC.size()) {
        grupoC.push_back(promediosParaABC[i]);
        i++;
    }
	cout << "\n";
	cout << " **************************************" << endl;
    cout << " *               Grupo A              *" << endl;
    cout << " **************************************" << endl;
    cout << " >> Los mas importantes para la empresa" << endl;
    cout << " --------------------------------------" << endl;
    for (const auto& promedio : grupoA) {
        cout << " Producto: " << promedio.pp.nombre << " " << promedio.pp.marca << endl;
    }
    cout << endl;

	cout << " **************************************" << endl;
    cout << " *               Grupo B              *" << endl;
    cout << " **************************************" << endl;
    cout << " >> Importancia y rentabilidad moderada" << endl;
    cout << " --------------------------------------" << endl;
    for (const auto& promedio : grupoB) {
        cout << " Producto: " << promedio.pp.nombre << " " << promedio.pp.marca << endl;
    }
    cout << endl;

	cout << " **************************************" << endl;
    cout << " *               Grupo C              *" << endl;
    cout << " **************************************" << endl;
    cout << " >> Los mas numerosos, no tan rentables" << endl;
    cout << " --------------------------------------" << endl;
    for (const auto& promedio : grupoC) {
        cout << " Producto: " << promedio.pp.nombre << " " << promedio.pp.marca << endl;
    }
    cout << endl;
}