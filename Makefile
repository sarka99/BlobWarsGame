win:
	gcc -Iinclude -Iinclude/sdl -Iinclude/headers -Llib -o Main src/*.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lSDL2_mixer
mac:
	gcc -o Main src/main.c src/collisions.c  -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -
	
server:
	gcc -Iinclude -Iinclude/sdl -Iinclude/headers -Llib -o server server/UDPserver.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lSDL2_mixer
	