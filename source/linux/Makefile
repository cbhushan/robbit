CC = cc 

LDLIBS = -lGL -lGLU -lXi -lX11 -lm -lglut -Wno-deprecated `pkg-config --cflags opencv` `pkg-config --libs opencv`

.cpp:
	$(CC)  $@.cpp $(LDLIBS) -o $@
