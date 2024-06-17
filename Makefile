CC=g++
CFLAGS=-lncurses -pthread
TARGET=game.out
OBJS=project.o


$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

project.o: project.cpp
	$(CC) -c project.cpp $(CFLAGS)

clean:
	rm $(OBJECT) $(TARGET)