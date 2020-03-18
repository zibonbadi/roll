CC = g++
PROGRAM = roll
DIR_LIBROLL = libroll/
OBJ_LIBROLL = $(wildcard $(DIR_LIBROLL)*.cpp) 
LD_RUN_PATH = $(PATH)

.PHONY: clean roll

roll: clean $(PROGRAM).cpp libroll.so
	$(CC) roll.cpp -o $(PROGRAM) -L. -lroll -Wl,-rpath=$(PATH) 
libroll.so: $(OBJ_LIBROLL:%.cpp=%.o)
	$(CC) -shared -o $@ $+ libroll/libroll.h 
%.o: %.cpp 
	$(CC) -c $<  -o $@ -fPIC  
clean:
	rm -rf libroll/*.o 
