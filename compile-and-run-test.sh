DS=UpdateProcMap

g++ -c $DS.cpp -std=c++11
g++ -o test $DS.o Test-$DS.cpp -std=c++11 -lgtest -pthread -I.
./test
rm test *.o
