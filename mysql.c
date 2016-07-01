/***********************************************************
 **
 ** Hochschule Ostwestfalen-Lippe
 **
 ** Author: 		Darius Korzeniewski
 ** Date:   		01.07.2016
 ** Filename:		mysql.c
 ** Descirption:	MySQL Client for Linux 
 ** 
 ***********************************************************/

// Vorab muessen noch folgende Pakte installieren werden:
// * sudo apt-get install mysql-client-core-5.7
// * sudo apt-get install libmysqlclient-dev

// <-- Befehl zum kompilieren der Datei --->
//  gcc mysql.c -o mysql `mysql_config --cflags --libs`

//<--- includes --->
#include <my_global.h>
#include <mysql.h>

//<-- functions --->
void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

//<--- main --->
int main(int argc, char **argv)
{  
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  // Verbindungsaufbau zur MySQL Datenbank
  if (!mysql_real_connect(con,
			 "127.0.0.1",	/*Server hostname or IP-Adresse*/
			"datauser",	/*mysql user*/	
			"datauser",	/*password*/
          		"databank",	/*default Database to use, NULL for none*/
			 3306,		/*port number, 0 for default*/
			"NULL",		/*socket file or named pipe name*/
			 0)) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }

  // In die Datenbank schreiben
  if (mysql_query(con, "INSERT INTO `tab` (`date`, `red`, `yellow`, `green`, `status`) VALUES (CURRENT_TIMESTAMP, '0', '1', '0', 'PI -> Warning')"))
  {    
      finish_with_error(con);    
  }  

  // Datenbank auslesen
  if (mysql_query(con, "SELECT * FROM tab")) 
  {
      finish_with_error(con);
  }

  MYSQL_RES *result = mysql_store_result(con);
  
  if (result == NULL) 
  {
      finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);
 
  MYSQL_ROW row;
 
  while ((row = mysql_fetch_row(result))) 
  { 
      for(int i = 0; i < num_fields; i++) 
      { 
          printf("%s ", row[i] ? row[i] : "NULL"); 
      } 
          printf("\n"); 
  }

  mysql_free_result(result);

  // Verbindung zur Datenbank schliessen
  mysql_close(con);
  exit(0);
}