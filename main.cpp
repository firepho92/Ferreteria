/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: alex
 *
 * Created on 5 de septiembre de 2018, 10:43 PM
 */
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <chrono>
#include <ctime>
#include <sstream>
#include "Producto.h"

using namespace std;
using json = nlohmann::json;

/*
 * 
 */
/*functions*/
void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #endif
    #ifdef linux
        system("clear");
    #endif
}

float validateNumber(string prompt){
    float number;
    string str;
    while(true){
        cout << prompt;
        getline(cin, str);
        stringstream convert(str);
        if(convert >> number && !(convert >> str)) return number;
        cout << "Ingrese un número válido \n";
    }
}

/*Main*/

int main(int argc, char** argv) {
    vector<Producto*> productos;
    json carrito, ventas;
    int menuPrincipalOpcion = 0, menuInventarioOpcion = 0, menuVentasOpcion = 0;
    
    productos.push_back(new Producto("1", "Martillo", 50, 100, 1000));
    productos.push_back(new Producto("2", "Desarmador cruz", 25, 50, 5));
    productos.push_back(new Producto("3", "Clavos 1/4", 0.5, 1, 2000));
    
    while(menuPrincipalOpcion != 3){
        menuInventarioOpcion = 0;
        menuVentasOpcion = 0;
        clearScreen();
        cout << "Selecciona una opción del menú: \n";
        cout << "1. Inventario \n";
        cout << "2. Ventas \n";
        cout << "3. Salir \n";
        cin >> menuPrincipalOpcion;
        if(menuPrincipalOpcion == 1){
            while(menuInventarioOpcion != 5){
                auto productosIterator = productos.begin();
                string clave = "", nombre = "", str = "", stop = "";
                float precioCompra = 0, precioVenta = 0;
                int cantidad = 0, index = 0;
                clearScreen();
                cout << "Selecciona una opción: \n";
                cout << "1. Agregar un producto.\n";
                cout << "2. Actualizar producto. \n";
                cout << "3. Ver productos. \n";
                cout << "4. Eliminar producto. \n";
                cout << "5. Volver al menu principal. \n";
                cin >> menuInventarioOpcion;
                cin.get();
                switch(menuInventarioOpcion){
                    case 1:
                        clearScreen();
                        cout << "Agregar nuevo producto:\n";
                        cout << "Ingresa nombre: \n";
                        cin >> nombre;
                        cin.get();
                        precioVenta = validateNumber("Ingresa precio de venta:\n");
                        precioCompra = validateNumber("Ingresa precio de compra: \n");
                        cantidad = validateNumber("Ingresa la cantidad de unidades en stock: \n");
                        clave = to_string(productos.size() + 1);
                        productos.push_back(new Producto(clave, nombre, precioCompra, precioVenta, cantidad));
                        cin.get();
                        break;
                    case 2:
                        clearScreen();
                        cout << "Ingresa el nombre del producto a editar: " << endl;
                        getline(cin, str);
                        for(int i = 0; i < productos.size(); i++){
                            if(str == productos[i]->getNombre()){
                                cout << "Ingresa nombre: \n";
                                getline(cin, nombre);
                                productos[i]->setNombre(nombre);
                                cout << "Ingresa el precio de venta:\n";
                                cin >> precioVenta;
                                productos[i]->setPrecio(precioVenta);
                                cout << "Ingresa el precio de compra:\n";
                                cin >> precioCompra;
                                productos[i]->setPrecioCompra(precioCompra);
                                cout << "Ingresa la cantidad de unidades en Stock: \n";
                                cin >> cantidad;
                                productos[i]->setUnidades(cantidad);
                                break;
                            }
                        }
                        cin.get();
                        break;
                    case 3:
                        clearScreen();
                        for(int i = 0; i < productos.size(); i++){
                            cout << "Clave: " << productos[i]->getClave() << ", Nombre: " <<productos[i]->getNombre() << ", Precio de venta: " << productos[i]->getPrecio() << ", Precio de compra: " << productos[i]->getPrecioCompra() << ", Unidades: " << productos[i]->getUnidades() << endl ;
                        }
                        cout << "Presione enter para volver...";
                        cin.get();
                        break;
                    case 4:
                        clearScreen();
                        cout << "Ingresa el nombre del producto a borrar: \n";
                        getline(cin, nombre);
                        
                        for(int i = 0; i < productos.size(); i++){
                            if(nombre == productos[i]->getNombre()){
                                productos.erase(productosIterator);
                            }
                            productosIterator++;
                        }
                        cout << "Producto removido\nPresione enter para volver...";
                        cin.get();
                        break;
                }
            }
        }
        if(menuPrincipalOpcion == 2){
            while(menuVentasOpcion != 6){
                auto time_now = chrono::system_clock::now();
                time_t time_now_t = chrono::system_clock::to_time_t(time_now);
                json objeto, elemento, elementos, venta;
                string clave, date = "", finalizarVenta;
                int cantidad;
                bool sellingFlag = false;
                float total = 0;
                clearScreen();
                cout << "Selecciona una opción: \n";
                cout << "1. Agregar un producto al carrito.\n";
                cout << "2. Eliminar un producto del carrito.\n";
                cout << "3. Ver carrito. \n";
                cout << "4. Finalizar venta. \n";
                cout << "5. Ver historial de ventas.\n";
                cout << "6. Regresar al menu principal.\n";
                cin >> menuVentasOpcion;
                cin.get();
                switch(menuVentasOpcion){
                    case 1:
                        clearScreen();
                        for(int i = 0; i < productos.size(); i++){
                            cout << "Clave: " << productos[i]->getClave() << ", Nombre: " <<productos[i]->getNombre() << ", Precio de venta: " << productos[i]->getPrecio() << ", Precio de compra: " << productos[i]->getPrecioCompra() << ", Unidades: " << productos[i]->getUnidades() << endl ;
                        }
                        cout << "Ingrese la clave del producto a comprar: \n";
                        cin >> clave;
                        cout << "Ingrese la cantidad a comprar:\n";
                        cin >> cantidad;
                        for(int i = 0; i < productos.size(); i++){
                            if(clave == productos[i]->getClave()){
                                objeto["clave"] = clave;
                                objeto["nombre"] = productos[i]->getNombre();
                                objeto["precioVenta"] = productos[i]->getPrecio();
                                objeto["cantidad"] = cantidad;
                            }
                        }
                        carrito["productos"].push_back(objeto);
                        cin.get();
                        break;
                    case 2:
                        clave = "";
                        clearScreen();
                        if(carrito.size() > 0){
                            cout << carrito["productos"] << endl;
                            cout << "Ingresa clave del producto a borrar:\n";
                            getline(cin, clave);
                            for(int i = 0; i < carrito["productos"].size(); i++){
                                if(clave == carrito["productos"][i]["clave"]){
                                    carrito["productos"].erase(i);
                                    break;
                                }
                            }
                            cout << "Producto removido \n";
                        }else{
                            cout << "Carrito de compras vacio\n";
                        }
                        cout << "Presione enter para regresar...";
                        cin.get();
                        break;
                    case 3:
                        clearScreen();
                        if(carrito["productos"].size() > 0){
                            cout << carrito["productos"] << endl << endl;
                        }else{
                            cout << "Carrito de compras vacio\n";
                        }
                        cout << "Presione enter para regresar...";
                        cin.get();
                        break;
                    case 4:
                        clearScreen();
                        date = ctime(&time_now_t);
                        cout << date << endl;
                        for(int i = 0; i < carrito["productos"].size(); i++){
                            float pV, c, sT;
                            pV = carrito["productos"][i]["precioVenta"];
                            c = carrito["productos"][i]["cantidad"];
                            sT = pV * c;
                            elemento["clave"] = carrito["productos"][i]["clave"];
                            elemento["nombre"] = carrito["productos"][i]["nombre"];
                            elemento["precioVenta"] = carrito["productos"][i]["precioVenta"];
                            elemento["cantidad"] = carrito["productos"][i]["cantidad"];
                            elemento["subtotal"] = sT;
                            elementos.push_back(elemento);
                            total += sT;
                            cout << "nombre: " << carrito["productos"][i]["nombre"] << ", precio unitario: " << carrito["productos"][i]["precioVenta"] << ", cantidad: " << carrito["productos"][i]["cantidad"] << ", subtotal: "<< sT << endl;
                        }
                        cout << endl << "Total: " << total << endl;
                        cout << "Presione S para aceptar o N para cancelar:\n";
                        getline(cin, finalizarVenta);
                        if(finalizarVenta == "s"){
                            for(int i = 0; i < elementos.size(); i++){
                                for(int j = 0; j < productos.size(); j++){
                                    if(elementos[i]["clave"] == productos[j]->getClave()){
                                        if(productos[j]->vender(elementos[i]["cantidad"])){
                                            sellingFlag = true;
                                        }else{
                                            sellingFlag = false;
                                        }
                                    }
                                }
                            }
                            if(sellingFlag){
                                venta["ticket"] = ventas.size() + 1;
                                venta["fecha"] = date;
                                venta["productos"] = elementos;
                                cout << "Venta exitosa\n";
                                ventas.push_back(venta);
                            }else{
                                cout << "No se puede finalizar la venta";
                            }
                        }else{
                            cout << "Venta cancelada\n";
                        }
                        cout << ventas << endl;
                        carrito.clear();
                        elementos.clear();
                        elemento.clear();
                        cout << "Presione enter para continuar...";
                        cin.get();
                        break;
                    case 5:
                        clearScreen();
                        cout << "Ventas:\n";
                        cout << ventas << endl;
                        cout << "Presione enter para volver...";
                        cin.get();
                        break;
                }
            }
        }
    }
    return 0;
}