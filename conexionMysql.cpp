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
};

Connection::Connection()
{

    HOSTNAME = "sql10.freemysqlhosting.net";
    DATABASE = "sql10420882";
    USERNAME = "sql10420882";
    PASSWORD = "te5qkMTUAT";
    SOCKET = NULL;
}

bool Connection::ejecucion()
{

    try
    {

        CONN = mysql_init(NULL);
        
        if (!mysql_real_connect(CONN, HOSTNAME, USERNAME, PASSWORD, DATABASE, PORT, SOCKET, 0))
        {
            cerr << mysql_error(CONN) << endl;
            return false;
        }

        if (mysql_query(CONN, "Select * from Products"))
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

int Connection::registrar(char * username, char * email, char * pass){
    try
    {
        CONN = mysql_init(NULL);
        char * consulta = "INSERT INTO Users (username, email, password) VALUES ( ?, ?, ?)";
        
        if (!mysql_real_connect(CONN, HOSTNAME, USERNAME, PASSWORD, DATABASE, PORT, SOCKET, 0))
        {
            cerr << mysql_error(CONN) << endl;
            return 0;
        }

        int result; 
        // unsigned long count; 

        MYSQL_STMT * stmt = mysql_stmt_init(CONN); 
        if (stmt == NULL) return 0;

        result = mysql_stmt_prepare(stmt, consulta, strlen(consulta));  
        if (result != 0) return 0; 


        int count = mysql_stmt_param_count(stmt);
        printf("there are %d parameters in the insert statements\n", count); 

        MYSQL_BIND bind[3]; //3 parametros en el statement

        unsigned int array_size = 1; //una sola fila se insertara
        unsigned long username_len = strlen(username); 
        unsigned long email_len = strlen(email); 
        unsigned long pass_len = strlen(pass);

        memset(bind, 0, sizeof(MYSQL_BIND)*3);

        bind[0].buffer_type = MYSQL_TYPE_STRING; 
        bind[0].buffer = username;
        bind[0].buffer_length = strlen(username); 
        bind[0].length = &username_len;

        bind[1].buffer_type = MYSQL_TYPE_STRING; 
        bind[1].buffer = email;
        bind[1].buffer_length = strlen(email); 
        bind[1].length = &email_len;

        bind[2].buffer_type = MYSQL_TYPE_STRING; 
        bind[2].buffer = pass;
        bind[2].buffer_length = strlen(pass); 
        bind[2].length = &pass_len; 

        mysql_stmt_attr_set(stmt, STMT_ATTR_ARRAY_SIZE, &array_size);

        result = mysql_stmt_bind_param(stmt, bind);

        if (result != 0) return 0;

        result = mysql_stmt_execute(stmt); //El error esta aqui que ladillaaaaaaaaaa
    

        if (result != 0) return 0;        

        mysql_stmt_close(stmt);
     
        mysql_close(CONN);

        return 1;
    }
    catch (char *e)
    {
        cerr << "[EXECPTION] " << e << endl;
        return 0;
    }
}

int main()
{
    try{

    Connection objConn;
    bool result = objConn.registrar("hola","hola@gmail.com","123456");
    if (!result) cout << "ERROR!!!!" <<endl;

    } catch (char *e){
        cerr << "[EXECPTION] " << e << endl;
    }
    return 0;
}