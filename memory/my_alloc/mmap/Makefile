EXE = allocation readfile ipc memory_protection exe

.PHONY: all
all: $(EXE)


exe: exe.o
	ld -o exe exe.o

exe.o: exe.asm
	nasm -o exe.o -felf64 exe.asm


%: %.cpp
	g++ -Wall -ggdb -o $@ $< 


.PHONY: clean
clean:
	rm -rfv $(EXE)	

