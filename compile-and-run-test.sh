DS=UpdateWorkMap
CPPC=g++-8

$CPPC -c $DS.cpp -std=c++11
$CPPC -o test $DS.o Test-$DS.cpp -std=c++11 -lgtest -pthread -I.
./test
rm test *.o
