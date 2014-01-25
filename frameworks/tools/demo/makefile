CC = gcc

LIBS = -framework OpenGl -framework GLUT

PROJ = main

OBJ_LOG = gtlog

DEBUG = true

OBJS = $(PROJ).o $(OBJ_LOG).o

ifeq ('$(DEBUG)', 'true')
$(PROJ): $(OBJS)
	$(CC) -g -o $(PROJ) $(OBJS) $(LIBS)
$(OBJS): $(PROJ).c $(OBJ_LOG).c 
	$(CC) -g -c $(PROJ).c $(OBJ_LOG).c
else
$(PROJ): $(OBJS)
	$(CC) -o $(PROJ) $(OBJS) $(LIBS)
$(OBJS): $(PROJ).c $(OBJ_LOG).c 
	$(CC) -c $(PROJ).c $(OBJ_LOG).c
endif

clean:
	rm *.o $(PROJ)
