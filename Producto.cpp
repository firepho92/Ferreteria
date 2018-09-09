/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Producto.cpp
 * Author: alex
 * 
 * Created on 5 de septiembre de 2018, 11:20 PM
 */
#include <string>
#include <iostream>
#include "Producto.h"

using namespace std;

Producto::Producto(string clave, string nombre, float precio, float precioCompra, int unidades){
  this->clave = clave;
  this->nombre = nombre;
  this->precio = precio;
  this->precioCompra = precioCompra;
  this->unidades = unidades;
}

void Producto::setClave(string clave){
  this->clave = clave;
}

void Producto::setNombre(string nombre){
  this->nombre = nombre;
}

void Producto::setPrecio(float precio){
  this->precio = precio;
}

void Producto::setPrecioCompra(float precioCompra){
    this->precioCompra = precioCompra;
}

void Producto::setUnidades(int unidades){
  this->unidades = unidades;
}

string Producto::getClave(){
  return this->clave;
}

string Producto::getNombre(){
  return this->nombre;
}

float Producto::getPrecio(){
  return this->precio;
}

float Producto::getPrecioCompra(){
    return this->precioCompra;
}

int Producto::getUnidades(){
  return this->unidades;
}

bool Producto::vender(int unidades){
    if(this->unidades > 0){
        if(unidades < this->unidades){
            this->unidades = this->unidades - unidades;
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

Producto::Producto(const Producto& orig) {
}

Producto::~Producto() {
}

