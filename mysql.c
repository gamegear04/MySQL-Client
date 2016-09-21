/***********************************************************
 **
 ** Hochschule Ostwestfalen-Lippe
 **
 ** Author: 		Darius Korzeniewski
 ** Date:   		06.09.2016
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
#include <stdlib.h>

//<-- functions --->
void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

int menu()
{
    int auswahl;
    
    printf("Hochschule Ostwestfalen-Lippe\n");
    printf("1: In Datenbank schreiben\n");
    printf("2: Datenbank auslesen\n");
    printf("0: Programm beenden\n");
    
    scanf("%d",&auswahl);
    
    return auswahl;
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

    for(;;)
    {
        int auswahl,
            done = 0;
        int r = rand() % 20;
        
        auswahl = menu();
        
        switch (auswahl) {
            // In Datenbank schreiben
            case 1:
            for(;;)
            {
                int wahl;
                if(done != 0)
                {
                    printf("Eingabe ende\n");
                    break;
                }
                
                printf("3:Fehler 2:Warnung 1:Gut 0:Ende\n");
                printf("Iher Wahl: ");
                scanf("%d",&wahl);
            
                switch(wahl)
                {
                    case 1:
                    printf("Good\n");
                    if (mysql_query(con, "INSERT INTO `tab` (`date`, `red`, `yellow`, `green`, `status`) VALUES (CURRENT_TIMESTAMP, '0', '0', '1', 'PI -> Good')"))
                    {
                        finish_with_error(con);
                    }
                    else
                    {
                        if(mysql_query(con, "INSERT INTO `tab1` (`frequenz`) VALUES ('%d' )",r))
                        {
                            finish_with_error(con);
                        }
                    }
                    break;
                    case 2:
                    printf("Warning\n");
                    if (mysql_query(con, "INSERT INTO `tab` (`date`, `red`, `yellow`, `green`, `status`) VALUES (CURRENT_TIMESTAMP, '0', '1', '0', 'PI -> Warning')"))
                    {
                        finish_with_error(con);
                    }
                    else
                    {
                        if(mysql_query(con, "INSERT INTO `tab1` (`frequenz`) VALUES ('%d' )",r))
                        {
                            finish_with_error(con);
                        }
                    }
                    break;
                    case 3:
                    printf("Error\n");
                    if (mysql_query(con, "INSERT INTO `tab` (`date`, `red`, `yellow`, `green`, `status`) VALUES (CURRENT_TIMESTAMP, '1', '0', '0', 'PI -> Error')"))
                    {
                        finish_with_error(con);
                    }
                    else
                    {
                        if(mysql_query(con, "INSERT INTO `tab1` (`frequenz`) VALUES ('%d' )",r))
                        {
                            finish_with_error(con);
                        }
                    }
                    break;
                    case 0:
                         done = 1;
                    break;
                }
            }
            break;
            // Datenbank auslesen
            case 2:
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
            break;
            case 0:
                printf("Programm wird beendet\n");
                // Verbindung zur Datenbank schliessen
                mysql_close(con);
                exit(0);
                break;
            default:
                printf("Ihre Auswahl ist ungueltig\n");
            break;
        }
    }
}
