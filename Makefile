CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
TARGET = matrix_lab

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

clean:
	rm -f $(TARGET)