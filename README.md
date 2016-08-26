Beschreibung des MySQL - Clients in C fuer Linux

Der Client beinhaltet das Einloggen auf dem Mysql Server.
Sowie das Daten schreiben und lesen.
Und zu guter letzt das Ausloggen vom Server.

Um den geschriebenen Code ausfuehren zu koennen:
Muessen folgende Pakte installiert werden:

mysql-client-core-5.7
libmysqlclient-dev

Falls man apt-get nutzt, kann man die darunterliegenden Zeilen einfach kopieren
und in die Konsole einfügen.
sudo apt-get install mysql-client-core-5.7
sudo apt-get install libmysqlclient-dev

Folgende Bereiche muessen noch auf Ihre Datenstrukt angepasst werden:

1. Das Einloggen zum Server
2. Das Schreiben in bzw. Lesen aus der Datenbank 
