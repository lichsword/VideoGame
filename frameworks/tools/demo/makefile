CC = gcc
LIBS = -framework OpenGl -framework GLUT
PROJ = main

OBJ_LOG = gtlog

OBJS = $(PROJ).o $(OBJ_LOG).o

$(PROJ): $(OBJS)
	$(CC) -o $(PROJ) $(OBJS) $(LIBS)
$(OBJS): $(PROJ).c $(OBJ_LOG).c 
	$(CC) -c $(PROJ).c $(OBJ_LOG).c
clean:
	rm *.o $(PROJ)
