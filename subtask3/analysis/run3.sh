#!/bin/sh
echo video path?
read VIDEO_PATH
echo "Looping over method 3"
echo "--------------------------------"  
echo "executing baseline method"
g++ -o ../code/exe/base34 ../code/base34.cpp -lpthread -std=c++11 `pkg-config --cflags --libs opencv`
g++ -o ../code/exe/m3 ../code/m3.cpp -lpthread -std=c++11 `pkg-config --cflags --libs opencv`
g++ -o error error.cpp
../code/exe/base34 /$VIDEO_PATH
for i in 1 2 4 8 16 32
do
  echo "--------------------------------"
  echo "i = $i"  
    ../code/exe/m3 /$VIDEO_PATH $i
    ./error base34.txt m3.txt
done
