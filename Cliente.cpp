#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;


class Usuario{
    string username, email, password;
    int status;

    public:
        //Metodos de los atributos privado.
        void setPassword(string password);
        void setUsername(string username);
        void setEmail(string email);
        void setStatus(int status);

        //Metodos de la clase cliente
        int infoRegistro();
};

void Usuario::setPassword(string password){
    this->password = password;
}

void Usuario::setUsername(string username){
    this->username = username;
}

void Usuario::setEmail(string email){
    this->email = email;
}

void Usuario::setStatus(int status){
    this->status = status;
}

int Usuario::infoRegistro(){
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
    cout << "Indique si es Administrador[0], Cliente[1] ó Proveedor[2]: ";
    cin >> status;
    switch (status){
    case 0:
        setStatus(0);
        break;
    case 1:
        setStatus(1);
        break;
    case 2:
        setStatus(2);
        break;
    default:
        break;
    }
}
