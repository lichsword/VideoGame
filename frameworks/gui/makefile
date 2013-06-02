run: main.o ../service/log/sv_log.o
	gcc -o run main.o ../service/log/sv_log.o -framework OpenGl -framework GLUT 
main.o: main.c
	gcc -c main.c #-framework OpenGL -framework GLUT
../service/log/log.0: ../service/log/sv_log.c
	gcc -c ../service/log/sv_log.c
clean:  
	cd ..
	rm -ir *.o run
