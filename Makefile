bin:
	g++ -g -o build/main.bin src/main.cpp

dump:
	objdump -M intel -d -S build/main.bin

all: bin dump