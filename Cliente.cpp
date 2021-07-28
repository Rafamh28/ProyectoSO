#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;


class Cliente{
    string username, email, password;

    public:
        //Metodos de los atributos privado.
        void setPassword(string password);
        string getPassword();
        void setUsername(string username);
        string getUsername();
        void setEmail(string email);
        string getEmail();

        //Metodos de la clase cliente
        int infoRegistro();
};

void Cliente::setPassword(string password){
    this->password = password;
}

string Cliente::getPassword(){
    return this->password;
}

void Cliente::setUsername(string username){
    this->username = username;
}

string Cliente::getUsername(){
    return this->username;
}

void Cliente::setEmail(string email){
    this->email = email;
}

string Cliente::getEmail(){
    return this->email;
}

int Cliente::infoRegistro(){
    string user, pass, passaux, email;
    int status;

    cout << "Introduce tu nombre de usuario: ";
    cin >> user;
    cout << "Introduce tu email: ";
    cin >> email;
    bool bandera = true;
    while(bandera == true){
        cout << "Introduce tu password o contraseña: ";
        cin >> pass;
        cout << "Confirma tu contraseña: ";
        cin >> passaux;

        if(pass != passaux){
            cout << "Contraseña incorrecta. \n";
        }else{
            cout << "Contraseña establecida. \n";
            bandera = false;
        }
    }
    setUsername(user);
    setPassword(pass);
    setEmail(email);
}
