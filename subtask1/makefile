make: fun
	clear
	./fun empty.jpg   	
	
fun:
	g++ -o fun fun.cpp -std=c++11 `pkg-config --cflags --libs opencv`

clear:
	rm fun
	rm grey_empty.jpg
	rm final_cropped_projection.jpg
