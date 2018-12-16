g++ -c -fpic libroll/iroll.cpp -o libroll/iroll.o
g++ -shared -o libroll.so libroll/*.o libroll/libroll.h 
g++ roll.cpp -o roll -lroll -L. -Wl,-rpath=.
