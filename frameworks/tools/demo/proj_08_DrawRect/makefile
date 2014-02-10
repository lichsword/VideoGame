CC = gcc
LIBS = -framework OpenGl -framework GLUT
PROJ = ViewPort

COM = ../include/gtcommon
# 1:enable 0:disable
DEBUG = 1
# debug flag: -g
DFLAG = -g
OBJS = $(PROJ).o 

# link
$(PROJ):$(OBJS)
	$(CC) $(DFLAG) -o $(PROJ) $(OBJS) $(LIBS)
# build
$(PROJ).o:$(PROJ).c $(COM).h
	$(CC) $(DFLAG) -c $(PROJ).c
clean:
	rm *.o $(PROJ)
