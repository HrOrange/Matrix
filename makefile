TARGET = bin/main.exe
OBJS = main.cpp frac.h matrix.h

$(TARGET): $(OBJS)
	g++ -o $(TARGET) $(OBJS)