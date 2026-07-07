# this makefile compile all cpp files in the current directory.
# A cpp file will generate an executable with the same name as the cpp file.

all: $(patsubst %.cpp,%,$(wildcard *.cpp))

clean:
	rm -f $(patsubst %.cpp,%,$(wildcard *.cpp))

*.cpp:
	g++ -o $@ $<
