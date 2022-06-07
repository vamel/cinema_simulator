OBJS	= cinema.o datetime.o main.o purchasable.o Repertoire.o worker.o playable.o show.o room.o shop.o
SOURCE	= cinema.cpp datetime.cpp main.cpp purchasable.cpp Repertoire.cpp worker.cpp playable.cpp show.cpp room.cpp shop.cpp
HEADER	= cinema.h datetime.h json.hpp purchasable.h Repertoire.h worker.h playable.h show.h room.h shop.h
OUT	= program.exe
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

cinema.o: cinema.cpp
	$(CC) $(FLAGS) cinema.cpp 

datetime.o: datetime.cpp
	$(CC) $(FLAGS) datetime.cpp 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

show.o: show.cpp
	$(CC) $(FLAGS) show.cpp

worker.o: worker.cpp
	$(CC) $(FLAGS) worker.cpp

purchasable.o: purchasable.cpp
	$(CC) $(FLAGS) purchasable.cpp 

Repertoire.o: Repertoire.cpp
	$(CC) $(FLAGS) Repertoire.cpp

playable.o: playable.cpp
	$(CC) $(FLAGS) playable.cpp

room.o: room.cpp
	$(CC) $(FLAGS) room.cpp

shop.o: shop.cpp
	$(CC) $(FLAGS) shop.cpp

clean:
	rm -f $(OBJS) $(OUT)
