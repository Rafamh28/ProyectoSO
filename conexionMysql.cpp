#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <mariadb/mysql.h>

using namespace std;

class Connection
{

    const char *HOSTNAME;
    const char *DATABASE;
    const char *USERNAME;
    const char *PASSWORD;
    const char *SOCKET;
    const int PORT = 3306;
    const int OPT = 0;

    MYSQL *CONN;
    MYSQL_RES *RES;
    MYSQL_ROW ROW;

public:
    Connection();
    bool ejecucion();
    int registrar(char * username, char * email, char * pass); //1 se registro 0 no se registro 
    int logear(char *emial,char *pass);  // Devuelve 0 en error o contraseña incorrecta, 1 con contraseña correcta
    int agregarProducto(char *name,char *brand, int amount,float presio,char * producer); // 0 en error, 1 en registro de producto exitoso
    bool mostrarProductos();  // True en caso de que se muestren los productos, falso en caso de error con la base datos
    int actualizarProducto(int id, char *name,char *brand, int amount,float presio,char * producer); //
};

Connection::Connection() // Esto se encarga de fijar los parametros necesarios para la conexión
{

    HOSTNAME = "sql10.freemysqlhosting.net";
    DATABASE = "sql10420882";
    USERNAME = "sql10420882";
    PASSWORD = "te5qkMTUAT";
    SOCKET = NULL;
}

bool Connection::ejecucion() // Esta es una función de prueba
{

    try
    {

        CONN = mysql_init(NULL);
        
        if (!mysql_real_connect(CONN, HOSTNAME, USERNAME, PASSWORD, DATABASE, PORT, SOCKET, 0))
        {
            cerr << mysql_error(CONN) << endl;
            return false;
        }

        if (mysql_query(CONN, "SHOW DATABASES"))
        {
            cerr << mysql_error(CONN) << endl;
            return false;
        }

        RES = mysql_use_result(CONN);

        cout << "*** Resultado de la consulta a *** => " << DATABASE << endl;
        //cout << mysql_num_fields(RES) << endl; 

        while ((ROW = mysql_fetch_row(RES)) != NULL){            
            cout << ROW[0] << endl;
        }

        mysql_free_result(RES);

        mysql_close(CONN);

        return true;
    }
    catch (char *e)
    {
        cerr << "[EXECPTION] " << e << endl;
        return false;
    }
}


int Connection::registrar(char * username, char * email, char * pass){  //Función para el registro del usuario
    try
    {
        CONN = mysql_init(NULL);

        string username_str(username);
        string email_str(email);
        string pass_str(pass);

        string consulta = "INSERT INTO Users (username, email, password) VALUES (\""+username_str+"\",\""+email_str+"\",\""+pass_str+"\")";
        
        if (!mysql_real_connect(CONN, HOSTNAME, USERNAME, PASSWORD, DATABASE, PORT, SOCKET, 0))
        {
            cerr << mysql_error(CONN) << endl;
            return 0;
        }

        if (mysql_query(CONN, consulta.c_str()))
        {
            cerr << mysql_error(CONN) << endl;
            return 0;
        }

     
        mysql_close(CONN);

        return 1;
    }
    catch (char *e)
    {
        cerr << "[EXECPTION] " << e << endl;
        return 0;
    }
}

int Connection::logear(char *email,char *pass){  // Función para el loguin del usuario
    try
    {

        CONN = mysql_init(NULL);
        
        if (!mysql_real_connect(CONN, HOSTNAME, USERNAME, PASSWORD, DATABASE, PORT, SOCKET, 0))
        {
            cerr << mysql_error(CONN) << endl;
            return 0;
        }

        string email_str(email);        
        string consulta = "SELECT * FROM Users WHERE email = \""+email_str+"\"";

        if (mysql_query(CONN, consulta.c_str()))
        {
            cerr << mysql_error(CONN) << endl;
            return 0;
        }

        RES = mysql_use_result(CONN);

        if(RES == NULL)
            return 0;

        if((ROW = mysql_fetch_row(RES)) != NULL){            
            if(strcmp(pass,ROW[3])==0)
                return 1;
        }else
                return 0;

        mysql_free_result(RES);

        mysql_close(CONN);

        return 0;
    }
    catch (char *e)
    {
        cerr << "[EXECPTION] " << e << endl;
        return 0;
    }    
}

int Connection::agregarProducto(char *name,char *brand,int amount, float presio,char * producer){  // Esta función agrega un producto a la lista de productos
    try
    {
        CONN = mysql_init(NULL);

        string name_str(name);
        string brand_str(brand);
        string presio_str(to_string(presio));
        string producer_str(producer);
        string amount_str(to_string(amount));
    
        string consulta = "INSERT INTO Products (name, brand, amount, presio, producer) VALUES (\""+name_str+"\",\""+brand_str+"\",\""+amount_str+"\","+presio_str+",\""+producer_str+"\")";
        
        if (!mysql_real_connect(CONN, HOSTNAME, USERNAME, PASSWORD, DATABASE, PORT, SOCKET, 0))
        {
            cerr << mysql_error(CONN) << endl;
            return 0;
        }

        if (mysql_query(CONN, consulta.c_str()))
        {
            cerr << mysql_error(CONN) << endl;
            return 0;
        }

        mysql_close(CONN);

        return 1;
    }
    catch (char *e)
    {
        cerr << "[EXECPTION] " << e << endl;
        return 0;
    }
}

int Connection::actualizarProducto(int id, char *name,char *brand, int amount,float presio,char * producer){  // Función que se encarga de actualizar el estado de los productos
    try
    {
       CONN = mysql_init(NULL);

        string name_str(name);
        string brand_str(brand);
        string presio_str(to_string(presio));
        string producer_str(producer);
        string amount_str(to_string(amount));
        string id_str(to_string(id));
    
        string consulta = "UPDATE Products SET name=\""+name_str+"\",brand =\""+brand_str+"\",amount ="+amount_str+",presio="+presio_str+",producer=\""+producer_str+"\" WHERE id="+id_str;
        
        if (!mysql_real_connect(CONN, HOSTNAME, USERNAME, PASSWORD, DATABASE, PORT, SOCKET, 0))
        {
            cerr << mysql_error(CONN) << endl;
            return 0;
        }

        if (mysql_query(CONN, consulta.c_str()))
        {
            cerr << mysql_error(CONN) << endl;
            return 0;
        }

        mysql_close(CONN);

        return 1;
    }
    catch (char *e)
    {
        cerr << "[EXECPTION] " << e << endl;
        return 0;
    }
}

bool Connection::mostrarProductos(){  // Muestra una lista de todos los productos de la base de datos 
   try
    {

        CONN = mysql_init(NULL);
        
        if (!mysql_real_connect(CONN, HOSTNAME, USERNAME, PASSWORD, DATABASE, PORT, SOCKET, 0))
        {
            cerr << mysql_error(CONN) << endl;
            return false;
        }

        if (mysql_query(CONN, "SELECT * FROM Products"))
        {
            cerr << mysql_error(CONN) << endl;
            return false;
        }

        RES = mysql_use_result(CONN);

        cout << "Lista de Productos Disponibles" << endl << endl; 

        while ((ROW = mysql_fetch_row(RES)) != NULL){            
            cout << "| " << ROW[0] << " | "  << ROW[1] << " | " << ROW[2] << " | " << ROW[3] << " | " << ROW[4] << " | " << ROW[5] << " | " << endl;
        }

        mysql_free_result(RES);

        mysql_close(CONN);

        return true;
    }
    catch (char *e)
    {
        cerr << "[EXECPTION] " << e << endl;
        return false;
    }  
}

int main()
{
    try{

    Connection objConn;
    int result = objConn.actualizarProducto(4,"Pasta Dental","Colgate",8,2500.4,"Colgate Corp");
    cout << result << endl; 
    if (!result) cout << "ERROR!!!!" <<endl;

    } catch (char *e){
        cerr << "[EXECPTION] " << e << endl;
    }
    return 0;
}