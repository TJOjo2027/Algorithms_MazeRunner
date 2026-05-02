all:
	g++ -I src/include -L src/lib -o BoothMain BoothMain.cpp -lmingw32 -lSDL3main -lSDL3