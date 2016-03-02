NAME = feb
src := $(wildcard *.cpp)
obj := $(src:%.cpp=%.o)
#FLAGS = -O0 -g -Wall -Wextra -std=c++11 -mwindows
FLAGS = -O3 -Wall -Wextra -std=c++11 -D__NO_INLINE__ -mwindows
LINKS_WIN = -lm -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_mixer
LINKS_LINUX = -lm -lSDL -lSDL_image -lSDL_mixer

${NAME}: $(obj) makefile
	g++ -o zofkir $(obj) ${FLAGS} ${LINKS_LINUX}

feb_res.o: feb.rc icon.png
	windres feb.rc feb_res.o --use-temp-file

$(obj): %.o: %.cpp
	g++ ${FLAGS} -c -o $@ $<

clean:
	rm -f ${NAME} *.o
