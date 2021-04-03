#!/bin/sh
echo video path?
read VIDEO_PATH
echo "Looping over method 4"
echo "--------------------------------"  
echo "executing baseline method"
g++ -o ../code/exe/base34 ../code/base34.cpp -lpthread -std=c++11 `pkg-config --cflags --libs opencv`
g++ -o ../code/exe/m4 ../code/m4.cpp -lpthread -std=c++11 `pkg-config --cflags --libs opencv`
g++ -o error error.cpp
../code/exe/base34 /$VIDEO_PATH
for i in 1 2 4 8 16 32
do
  echo "--------------------------------"
  echo "i = $i"  
    ../code/exe/m4 /$VIDEO_PATH $i
    ./error base34.txt m4.txt
done
