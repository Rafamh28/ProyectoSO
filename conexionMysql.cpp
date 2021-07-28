#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <mariadb/mysql.h>
#include <Producto.cpp>

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
    int registrar(char * username, char * email, char * pass,int type); //1 se registro 0 no se registro 
    int logear(char *emial,char *pass);  // Devuelve 0 en error o contraseña incorrecta, 1 con contraseña correcta
    int agregarProducto(char *name,char *brand, int amount,float presio,char * producer,int id_producer); // 0 en error, 1 en registro de producto exitoso
    bool mostrarProductos();  // True en caso de que se muestren los productos, falso en caso de error con la base datos
    int actualizarProducto(int id, char *name,char *brand, int amount,float presio,char * producer, int id_producer); //actualiza los productos
    char * encriptarContra(char * password);
    int getProducto(int id);
};

Connection::Connection() // Esto se encarga de fijar los parametros necesarios para la conexión
{

    HOSTNAME = "sql10.freemysqlhosting.net";
    DATABASE = "sql10428138";
    USERNAME = "sql10428138";
    PASSWORD = "i58SCBcJtR";
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

char *Connection::encriptarContra(char * password){
    if (!password)
        return nullptr;

    int size = strlen(password);
    int i = 0;
    char *str = new char[size + 1]();
    
    for (; password[i] != '\0'; i++)
        str[i] = password[i] + i + 3;
    str[i] = '\0';

    return str;
}

int Connection::registrar(char * username, char * email, char * pass,int type){  //Función para el registro del usuario
    try
    {
        CONN = mysql_init(NULL);

        string username_str(username);
        string email_str(email);
        string pass_str(Connection::encriptarContra(pass));
        string type_str(to_string(type));

        string consulta = "INSERT INTO User (username, email, password, user_type) VALUES (\""+username_str+"\",\""+email_str+"\",\""+pass_str+"\","+type_str+")";
        
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
        string consulta = "SELECT * FROM User WHERE email = \""+email_str+"\"";

        if (mysql_query(CONN, consulta.c_str()))
        {
            cerr << mysql_error(CONN) << endl;
            return 0;
        }

        RES = mysql_use_result(CONN);

        if(RES == NULL)
            return 0;

        if((ROW = mysql_fetch_row(RES)) != NULL){            
            if(strcmp(Connection::encriptarContra(pass),ROW[3])==0)
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

int Connection::getProducto(int id){  //traer producto
    try
    {

        CONN = mysql_init(NULL);
        
        if (!mysql_real_connect(CONN, HOSTNAME, USERNAME, PASSWORD, DATABASE, PORT, SOCKET, 0))
        {
            cerr << mysql_error(CONN) << endl;
            return 0;
        }
        string id_str(to_string(id));
        string consulta = "SELECT * FROM Products WHERE id = "+id_str;

        if (mysql_query(CONN, consulta.c_str()))
        {
            cerr << mysql_error(CONN) << endl;
            return 0;
        }

        RES = mysql_use_result(CONN);

        if(RES == NULL)
            return 0;

        if((ROW = mysql_fetch_row(RES)) != NULL){            
            cout << ROW[0] << endl;  //id
            cout << ROW[1] << endl;  //name   
            cout << ROW[2] << endl;  //brand
            cout << ROW[3] << endl;  //amount   
            cout << ROW[4] << endl;  //price    
            cout << ROW[5] << endl;  //producer
            cout << ROW[6] << endl;  //id_producer   
        }else
        return 0;

        mysql_free_result(RES);

        mysql_close(CONN);

        return 1;
    }
    catch (char *e)
    {
        cerr << "[EXECPTION] " << e << endl;
        return 0;
    }    
}

int Connection::agregarProducto(char *name,char *brand,int amount, float presio,char * producer,int id_producer){  // Esta función agrega un producto a la lista de productos
    try
    {
        CONN = mysql_init(NULL);

        string name_str(name);
        string brand_str(brand);
        string presio_str(to_string(presio));
        string producer_str(producer);
        string amount_str(to_string(amount));
        string id_producer_str(to_string(id_producer));
    
        string consulta = "INSERT INTO Products (name, brand, amount, price, producer, id_producer) VALUES (\""+name_str+"\",\""+brand_str+"\",\""+amount_str+"\","+presio_str+",\""+producer_str+"\","+id_producer_str+")";
        
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

int Connection::actualizarProducto(int id, char *name,char *brand, int amount,float presio,char * producer, int id_producer){  // Función que se encarga de actualizar el estado de los productos
    try
    {
       CONN = mysql_init(NULL);

        string name_str(name);
        string brand_str(brand);
        string presio_str(to_string(presio));
        string producer_str(producer);
        string amount_str(to_string(amount));
        string id_str(to_string(id));
        string id_producer_str(to_string(id_producer));
    
        string consulta = "UPDATE Products SET name=\""+name_str+"\",brand =\""+brand_str+"\",amount ="+amount_str+",price="+presio_str+",producer=\""+producer_str+"\","+"id_producer="+id_producer_str+" WHERE id="+id_str;
        
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
    int result = objConn.getProducto(1);
    cout << result << endl; 
    if (!result) cout << "ERROR!!!!" <<endl;

    } catch (char *e){
        cerr << "[EXECPTION] " << e << endl;
    }
    return 0;
}