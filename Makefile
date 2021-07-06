main.o : Station.c Timer.c Menu.c main.c
	gcc -o main.o Station.c Timer.c  Menu.c main.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm
clean:
	rm -f main.o
run:
	./main.o