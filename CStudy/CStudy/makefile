CC = g++
EXE = cstudy
SRCS = $(wildcard *.cpp ./DesignPattern/*.cpp ./DesignPattern/factory/*.cpp)
OBJS = $(patsubst %.cpp,%.o,${SRCS})
INCLUDE_DIR = -I./DesignPattern\
	-I./DesignPattern/factory

RM = rm -rf

${EXE}: ${OBJS}
	$(CC) -o ${EXE} ${OBJS}

# “$<”表示所有的依赖目标集,也就是%.cpp
# “$@”表示目标集,也就是%.o
%.o: %.cpp
	$(CC) -c ${INCLUDE_DIR} $< -o $@

clean:
	@$(RM) -rf ${EXE} ${OBJS}
