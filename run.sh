g++ -shared -fPIC change.cpp -o change.so

g++ main.cpp -lpthread -ldl -o main

./main

