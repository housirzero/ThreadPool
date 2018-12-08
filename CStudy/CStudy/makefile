CC = g++
EXE = cstudy
SRCS = $(wildcard *.cpp ./DesignPattern/*.cpp)
OBJS = $(patsubst %.cpp,%.o,${SRCS})
INCLUDE_DIR = -I./DesignPattern

RM = rm -rf

${EXE}: ${OBJS}
	$(CC) -o ${EXE} ${OBJS}

%.o: %.cpp
	$(CC) -c ${INCLUDE_DIR} $< -o $@

clean:
	@$(RM) -rf ${EXE} ${OBJS}
