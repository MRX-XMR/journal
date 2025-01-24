CC = g++
CFLAGS = 	-std=c++17 -pthread -fPIC -ldl -e '$ORIGIN/'
LIB_NAME = liblogged.so
TARGET = app
SOURCES = Logger.cpp main.cpp
OBJECTS = Logger.o main.o	

all: $(LIB_NAME) $(TARGET)
$(LIB_NAME): Logger.o
	$(CC) -shared -o $(LIB_NAME) Logger.o

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) main.o Logger.o -L -lLogger

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET) $(LIB_NAME)

