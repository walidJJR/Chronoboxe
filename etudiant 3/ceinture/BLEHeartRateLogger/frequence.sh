#! /bin/bash

count=0
while ((count != 1))
do
	echo "Prêt ?"
	echo "1. Start"
	echo "2. Remove"
	echo "3. Compile"
	echo "4. Improved read file"
	echo "5. Export file to SQL"
	echo "Quit"

	read user

	case $user in

	1)
		clear
                touch test.sql
                touch test.db

		chown pi test.db
		chgrp pi test.db

		chown pi test.sql
                chgrp pi test.sql

		python3 BLEHeartRateLogger.py -m EE:8B:10:23:C4:E8 -o test.db
		;;
	2)
		clear
        	rm test.sql
        	rm test.db
		;;

	3)
		clear
                sudo sqlite3 test.db .dump > test.sql
		;;

	4)
		clear

                touch f1.txt

		cat test.sql | sed -e 's/CREATE TABLE hrm (tstamp INTEGER, hr INTEGER, rr INTEGER);//'  |sed -e 's/BEGIN TRANSACTION;//' | sed -e 's/PRAGMA foreign_keys=OFF;//' | sed -e 's/CREATE TABLE sql (tstamp INTEGER, commit_time REAL, commit_every INTEGER);//' | sed -e 's/COMMIT;//' | sed -e "/^ *$/d"  >> f1.txt

                cat f1.txt > test.sql
                rm f1.txt

                cat test.sql
       		;;

	5)
		clear
		sudo mysql -u pi -p chronoboxe < test.sql
		;;

        *)
                clear
                echo "Bye !"
                ((count++))
                ;;
	esac
done

