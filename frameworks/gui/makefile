run: main.o ../service/log/sv_log.o ../service/font/sv_font.o
	gcc -o run main.o ../service/log/sv_log.o ../service/font/sv_font.o -framework OpenGl -framework GLUT 
main.o: main.c
	gcc -c main.c
../service/log/sv_log.o: ../service/log/sv_log.c
	gcc -c ../service/log/sv_log.c -o ../service/log/sv_log.o
../service/font/sv_font.o: ../service/font/sv_font.c
	gcc -c ../service/font/sv_font.c -o ../service/font/sv_font.o
clean:  
	cd ..
	rm -ir *.o run
