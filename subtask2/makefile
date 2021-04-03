main : a.out
	clear
	@echo "type:$$./a.out <path_to_video_folder/video_name>"

a.out : main.cpp
	g++ main.cpp -std=c++11 `pkg-config --cflags --libs opencv`


clean :
	rm a.out
	rm data.csv
