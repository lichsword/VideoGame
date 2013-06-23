# the make file of game complier
# link:http://stackoverflow.com/questions/10866331/freeglut-on-mac-os-x-lion
# In MacOS, the openGL lib install in /System/Libaray/Frameworks/OpenGL.framework/
#gcc -framework OpenGL -framework GLUT main.c game_log.c -o run
#gcc -framework OpenGL -framework GLUT main.c ../service/log/log.o -o run
#./run
make clean
make
./run
