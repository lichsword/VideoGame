run: make3d.o ../../service/log/sv_log.o ../../service/font/sv_font.o
	gcc -g -o run make3d.o ../../service/log/sv_log.o ../../service/font/sv_font.o -framework OpenGl -framework GLUT 
make3d.o: make3d.c
	gcc -g -c make3d.c
../../service/log/sv_log.o: ../../service/log/sv_log.c
	gcc -g -c ../../service/log/sv_log.c -o ../../service/log/sv_log.o
../../service/font/sv_font.o: ../../service/font/sv_font.c
	gcc -g -c ../../service/font/sv_font.c -o ../../service/font/sv_font.o
clean:  
	rm -r run
	find ../../../frameworks -name '*.o'|xargs rm -r
