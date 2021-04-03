#!/bin/sh
echo video path?
read VIDEO_PATH
echo "Looping over method 1"
echo "--------------------------------"  
echo "executing baseline method"
g++ -o ../code/exe/base12 ../code/base12.cpp -std=c++11 `pkg-config --cflags --libs opencv`
g++ -o ../code/exe/m1 ../code/m1.cpp -std=c++11 `pkg-config --cflags --libs opencv`
g++ -o error error.cpp
../code/exe/base12 /$VIDEO_PATH
for i in 1 2 3 4 5 6 7 8 9 10 11 12
do
  echo "--------------------------------"
  echo "i = $i"  
    ../code/exe/m1 /$VIDEO_PATH $i
    ./error base12.txt m1.txt
done
