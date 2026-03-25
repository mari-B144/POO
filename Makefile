CXX = g++
CXXFLAGS = -std=c++11 -Wall
SOURCES = main.cpp Film.cpp Sala.cpp Bilet.cpp Rezervare.cpp
TARGET = cinematograf
build:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
run: build
	./$(TARGET)
clean:
	rm -f $(TARGET)