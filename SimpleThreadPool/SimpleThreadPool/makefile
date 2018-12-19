CC = g++
EXE = simpleTPDemo
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,${SRCS})
INCLUDE_DIR = -I./
MACRO = -DUSE_ATOMIC #是否使用C++11的原子操作
CFLAG = $(MACRO) -Wall -std=c++11 #-Wno-deprecated-declarations

RM = rm -rf

${EXE}: ${OBJS}
	@$(CC) $(CFLAG) -o ${EXE} ${OBJS}
	@echo build ${EXE} success.

# “$<”表示所有的依赖目标集,也就是%.cpp
# “$@”表示目标集,也就是%.o
%.o: %.cpp
	@$(CC) $(CFLAG) -c ${INCLUDE_DIR} $< -o $@

clean:
	$(RM) -rf ${EXE} ${OBJS}
