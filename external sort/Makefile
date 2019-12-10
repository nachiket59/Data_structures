mysortt: mysort.o functions.o options.o
	gcc -o mysortt mysort.o functions.o options.o
mysort.o: mysort.c functions.h 
	gcc -c mysort.c		
functions.o: functions.c functions.h options.h
	gcc -c functions.c
options.o: options.c options.h
	gcc -c options.c	
