/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Producto.h
 * Author: alex
 *
 * Created on 5 de septiembre de 2018, 11:20 PM
 */
#include <string>
#ifndef PRODUCTO_H
#define PRODUCTO_H

using namespace std;

class Producto {
public:
    Producto(string clave, string nombre, float precio, float precioCompra, int unidades);
    void setClave(string clave);
    void setNombre(string nombre);
    void setPrecio(float precio);
    void setPrecioCompra(float precioCompra);
    void setUnidades(int unidades);
    string getClave();
    string getNombre();
    float getPrecio();
    float getPrecioCompra();
    int getUnidades();
    bool vender(int cantidad);
    Producto(const Producto& orig);
    virtual ~Producto();
private:
    string clave, nombre;
    float precio, precioCompra;
    int unidades;
};

#endif /* PRODUCTO_H */

