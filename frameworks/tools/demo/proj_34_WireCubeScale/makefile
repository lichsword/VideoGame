#ifeq ('$(DEBUG)', 'true')
#$(PROJ): $(OBJS)
#	$(CC) -g -o $(PROJ) $(OBJS) $(LIBS)
#$(OBJS): $(PROJ).c $(LOG).c $(MOD).c
#	$(CC) -g -c $(PROJ).c $(LOG).c $(MOD).c
#else
#$(PROJ): $(OBJS)
#	$(CC) -o $(PROJ) $(OBJS) $(LIBS)
#$(OBJS): $(PROJ).c $(LOG).c $(MOD).c
#	$(CC) -c $(PROJ).c $(LOG).c $(MOD).c
#endif
#---------------------------------------------

CC = gcc
LIBS = -framework OpenGl -framework GLUT
PROJ = WireCubeScale

COM = ../include/gtcommon
LOG = ../include/gtlog
# 1:enable 0:disable
DEBUG = 1
# debug flag: -g
DFLAG = -g
OBJS = $(PROJ).o $(LOG).o

# link
$(PROJ):$(OBJS)
	$(CC) $(DFLAG) -o $(PROJ) $(OBJS) $(LIBS)
# build
$(PROJ).o:$(PROJ).c $(LOG).h $(COM).h
	$(CC) $(DFLAG) -c $(PROJ).c
$(LOG).o:$(LOG).c $(COM).h
	$(CC) $(DFLAG) -c $(LOG).c -o $(LOG).o
clean:
	rm *.o $(LOG).o $(PROJ)
