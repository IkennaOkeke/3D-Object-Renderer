CC = gcc
CFLAGS = -Wall -Werror -std=c99
OBJECTS = spheres.o color.o vector.o

all: 3D_Obj_Renderer clean

# executable
3D_Obj_Renderer: main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o 3D_Obj_Renderer main.o $(OBJECTS) -lm

# main file
main.o: src/main.c src/spheres.h src/color.h src/vector.h
	$(CC) $(CFLAGS) -c src/main.c -o main.o

# object files
spheres.o: src/spheres.c src/spheres.h src/vector.h
	$(CC) $(CFLAGS) -c src/spheres.c

color.o: src/color.c src/color.h src/vector.h
	$(CC) $(CFLAGS) -c src/color.c

vector.o: src/vector.c src/vector.h
	$(CC) $(CFLAGS) -c src/vector.c

# clean object files
clean:
ifeq ($(OS),Windows_NT)
	del /Q *.o
else
	rm -f *.o
endif

# clean executable
clean2:
ifeq ($(OS),Windows_NT)
	del /Q 3D_Obj_Renderer.exe
else
	rm -f 3D_Obj_Renderer
endif
