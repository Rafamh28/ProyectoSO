#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;

class Producto{
    string name, brand, producer, id_producer;
    float price;
    int amount, id;

    public:
        void setID(int id);
        void setName(string name);
        void setBrand(string brand);
        void setProducer(string producer);
        void setID_Producer(string id_producer);

        void setPrice(float price);
        float getPrice();
        
        void setAmount(int amount);

        float getItemPriceByID();

    void Producto::setID(int id){
        this->id = id;
    }

    void Producto::setName(string name){
        this->name = name;
    }

    void Producto::setBrand(string brand){
        this->brand = brand;
    }

    void Producto::setProducer(string producer){
        this->producer = producer;
    }

    void Producto::setID_Producer(string id_producer){
        this->id_producer = id_producer;
    }

    void Producto::setPrice(float price){
        this->price = price;
    }

    float Producto::getPrice(){
        return price;
    }

    void Producto::setAmount(int amount){
        this->amount = amount;
    }

};