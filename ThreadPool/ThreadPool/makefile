CC = g++
EXE = main
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,${SRCS})

RM = rm -rf

${EXE}: ${OBJS}
	$(CC) -o ${EXE} ${OBJS}

%.o: %.cpp
	$(CC) -c $< -o $@

clean:
	@$(RM) -rf ${EXE} ${OBJS}
