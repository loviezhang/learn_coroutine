G++ = g++
G++_FLAGS = -c -O0
LD_FLAGS =

SOURCE_FILE = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCE_FILE))
TARGET = co_main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LD_FLAGS)

%.o : %.cpp
	$(G++) $(G++_FLAGS) $<

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
