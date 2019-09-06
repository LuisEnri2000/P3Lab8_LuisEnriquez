#include <iostream>
#include <stdlib.h>
#include <sqlite3.h>
#include <iomanip>
#include <bits/stdc++.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

int main(int argc, char** argv) {
	
	int op = 0;
	int subop = 0;
	sqlite3 *conn;
	sqlite3_stmt *res;
	int error=0;
	int rec_count =0;
	const char *tail;
	
	
	while (op != 7) {
		
		cout << "...::: MENU :::..." << endl;
		cout << "1. Listar (Dept/Emp)"<< endl;
		cout << "2. Agregar (Dept/Emp)" << endl;
		cout << "3. Eliminar empleado" << endl;
		cout << "4. Listar jefe y empleado" << endl;
		cout << "5. Actualizar salario empleado" << endl;
		cout << "6. Empleados de departamento" << endl;
		cout << "7. Salir" << endl;
		cout << "Opcion: ";
		cin >> op;
		
		system("CLS");
		
		if (op == 1) {
			cout << "..:: Listar ::.." << endl;
			cout << "1. Departamentos" << endl;
			cout << "2. Empleados" << endl;
			cout << "Opcion: ";
			cin >> subop;
			
			system("CLS");
			
			if (subop == 1) {
				// Listar deptos.
				//listar	
				error=sqlite3_open("oracle-sample.db",&conn);
				error=sqlite3_prepare_v2(conn,
				        "select * from dept",1000,&res,&tail);
				        
				cout<< endl;
				        
				cout << setw(20) << "Numero" << setw(20) << "Nombre" << setw(20) << "Lugar" << endl;
				        
				while(sqlite3_step(res) == SQLITE_ROW){
					cout<< setw(20) << sqlite3_column_text(res,0);
					cout<< setw(20) << sqlite3_column_text(res,1);
					cout<< setw(20) << sqlite3_column_text(res,2);
					cout << endl;
				}	
				sqlite3_close(conn);	
			}
			
			if (subop == 2) {
				// Listar empleados
				//listar	
				error=sqlite3_open("oracle-sample.db",&conn);
				error=sqlite3_prepare_v2(conn,
				        "select * from emp",1000,&res,&tail);
				        
				cout<< endl;
				        
				cout << setw(20) << "Codigo" << setw(20) << "Nombre" << setw(20) << "Puesto" << endl;
				        
				while(sqlite3_step(res) == SQLITE_ROW){
					cout<< setw(20) << sqlite3_column_text(res,0);
					cout<< setw(20) << sqlite3_column_text(res,1);
					cout<< setw(20) << sqlite3_column_text(res,2);
					cout << endl;
				}	
				sqlite3_close(conn);
			}
		}
		
		if (op == 2) {
			cout << "..:: Agregar ::.." << endl;
			cout << "1. Departamentos" << endl;
			cout << "2. Empleados" << endl;
			cout << "Opcion: ";
			cin >> subop;
			
			system("CLS");
			
			if (subop == 1) {
				// Agregar deptos.	
				string cta, nom, tit;
				cout << "..:: Agregar departamento ::.." << endl;
				cout << "Codigo: "; cin >> cta;
				cout << "Nombre: "; cin >> nom;
				cout << "Lugar : "; cin >> tit;
				
				string x = "insert into dept values('"+cta+"','"+nom+"','"+tit+"')";
				
				
				error=sqlite3_open("oracle-sample.db",&conn);
				error=sqlite3_exec(conn,
				x.c_str()
				,0,0,0);
				
				
				if(error != SQLITE_OK)
				cout<<"ERROR"<<endl;
				else
				cout << "Insertado exitosamente!" << endl;
				
				sqlite3_close(conn);
			}
			
			if (subop == 2) {
				// Agregar empleados
				// Agregar deptos.	
				string num, nom, puesto, numJefe, fecha, salario, comm, dept;
				cout << "..:: Agregar departamento ::.." << endl;
				cout << "Codigo: "; cin >> num;
				cout << "Nombre: "; cin >> nom;
				cout << "Puesto: "; cin >> puesto;
				cout << "ID Jefe: "; cin >> numJefe;
				cout << "Fecha (YYYY-MM-DD): "; cin >> fecha;
				cout << "Salario: "; cin >> salario;
				cout << "Comm: "; cin >> comm;
				cout << "Departamento: "; cin >> dept;
				
				string x = "insert into emp values('"+num+"','"+nom+"','"+puesto+"','"+numJefe+"','"+fecha+"','"+salario+"','"+comm+"','"+dept+"')";
				
				
				error=sqlite3_open("oracle-sample.db",&conn);
				error=sqlite3_exec(conn,
				x.c_str()
				,0,0,0);
				
				
				if(error != SQLITE_OK)
				cout<<"ERROR"<<endl;
				else
				cout << "Insertado exitosamente!" << endl;
				
				sqlite3_close(conn);
			}
		}
		
		if (op == 3) {
			cout << "..:: Eliminar empleado ::.." << endl;
			string codigo;
			cout << "Ingrese el ID a eliminar: ";
			cin >> codigo;
			
			string x = "delete from emp where empno='"+codigo+"'";
			
			//eliminar
			error=sqlite3_open("oracle-sample.db",&conn);
			error=sqlite3_exec(conn,
			x.c_str()
			,0,0,0);
			sqlite3_close(conn);
			
			
			cout << "Eliminado con exito!" << endl;
			
		}
		
		if (op == 4) {
			cout << "..:: Listar jefe y empleado ::.." << endl;
			// Preguntar que pedo
			string codigo;
			cout << "Ingrese codigo de empleado x: ";
			cin >> codigo;
			
			string x = "select mgr from emp where empno = '"+codigo+"'";
			
			error=sqlite3_open("oracle-sample.db",&conn);
			error = sqlite3_prepare_v2(conn,x.c_str(),x.length()+1,&res,&tail);
			
			if(error != SQLITE_OK)
				cout<<"ERROR"<<endl;
			
			if (sqlite3_step(res) == SQLITE_ROW) {
				x = (char *) sqlite3_column_text(res,0);
			}else{
				cout<<"No se encontro esa ID"<<endl;
			}
			
			cout << "El manager es: " + x;
			
			string y = "select * from emp where mgr ='" + x + "'";
			
			error=sqlite3_prepare_v2(conn,
				        y.c_str(),1000,&res,&tail);
				        
			cout<< endl;
			        
			cout << setw(20) << "Codigo" << setw(20) << "Nombre" << setw(20) << "Puesto" << endl;
			        
			while(sqlite3_step(res) == SQLITE_ROW){
				cout<< setw(20) << sqlite3_column_text(res,0);
				cout<< setw(20) << sqlite3_column_text(res,1);
				cout<< setw(20) << sqlite3_column_text(res,2);
				cout << endl;
			}	
			
			
			
			sqlite3_close(conn);
		}
		
		if (op == 5) {
			cout << "..:: Actualizar sueldo ::.." << endl;
			string codigo, sueldo;
			
			cout << "Ingrese el ID del empleado: ";
			cin >> codigo;
			
			string y = "select * from emp where mgr ='" + codigo + "'";
			
			error=sqlite3_open("oracle-sample.db",&conn);
			error=sqlite3_prepare_v2(conn,
				        y.c_str(),1000,&res,&tail);
				        
			int total = 0;
			int temp = 0;
			int cont = 0;
			        
			//cout << setw(20) << "Codigo" << setw(20) << "Nombre" << setw(20) << "Puesto" << endl;
			        
			while(sqlite3_step(res) == SQLITE_ROW){		
				temp = atoi((char *) sqlite3_column_text(res,5));
				//cout << temp;
				total += temp;
				cont ++;
			}
			
			if (cont != 0) {
				string mau;
				stringstream ss;
				ss << (total/cont)*2;
				mau = ss.str();
				
				cout << "El nuevo salario es: " << total << endl;
				
				string prro = "update emp set sal='"+ mau +"' where empno='"+ codigo +"'";
				error=sqlite3_exec(conn,
				prro.c_str()
				,0,0,0);
			}else{
				cout << "Ese brother no es jefe de nadie xddd" << endl;
			}
	
			sqlite3_close(conn);
			
			
			cout << "Salario actualizado!" << endl;
		}
		
		if (op == 6) {
			cout << "..:: Empleados de departamento ::.." << endl;
			string codigo;
			//preguntar que pedo
			cout << "Ingrese codigo del departamento: ";
			cin >> codigo;
			
			string y = "select * from emp where deptno = '" + codigo + "'";
			
			error=sqlite3_open("oracle-sample.db",&conn);
			error=sqlite3_prepare_v2(conn,
				        y.c_str(),1000,&res,&tail);
				        
			cout<< endl;
			
			int total = 0;
			int temp = 0;
			string castear = "";
			        
			cout << setw(20) << "Codigo" << setw(20) << "Nombre" << setw(20) << "Puesto" << endl;
			        
			while(sqlite3_step(res) == SQLITE_ROW){
				cout<< setw(20) << sqlite3_column_text(res,0);
				cout<< setw(20) << sqlite3_column_text(res,1);
				cout<< setw(20) << sqlite3_column_text(res,2);
				cout << endl;
				
				//castear = (char *) sqlite3_column_text(res,6);
				
				temp = atoi((char *) sqlite3_column_text(res,5));
				//cout << temp;
				total += temp;
			}
			cout << endl;
			cout << "Total a pagar: " << total << endl;
			sqlite3_close(conn);
		}
		
		system("pause");
		system("CLS");
		
	}
	
	cout << "Sistema cerrado, puede usar su base de datos." << endl;
	
	
	
	return 0;
}
