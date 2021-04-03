main: exe base12 base34 m1 m2 m3 m4

exe:
	mkdir exe

base12:
	g++ -o ./exe/base12 base12.cpp -std=c++11 `pkg-config --cflags --libs opencv`
	
m1:
	g++ -o ./exe/m1 m1.cpp -std=c++11 `pkg-config --cflags --libs opencv`
	
m2:
	g++ -o ./exe/m2 m2.cpp -std=c++11 `pkg-config --cflags --libs opencv`
	
base34:
	g++ -o ./exe/base34 base34.cpp -std=c++11 `pkg-config --cflags --libs opencv`

m3:
	g++ -o ./exe/m3 m3.cpp -lpthread -std=c++11 `pkg-config --cflags --libs opencv`
	
m4:
	g++ -o ./exe/m4 m4.cpp -lpthread -std=c++11 `pkg-config --cflags --libs opencv`

run_b12: exe base12
	@echo "type: $$./exe/base12 <video_path>?"
	
run_b34: exe base34
	@echo "type: $$./exe/base34 <video_path>?"
	
run1: exe m1
	@echo "type: $$./exe/m1 <video_path> <parameter>?"
	
run2: exe m2
	@echo "type: $$./exe/m2 <video_path> <parameter>?"
	
run3: exe m3
	@echo "type: $$./exe/m3 <video_path> <parameter>?"
	
run4: exe m4
	@echo "type: $$./exe/m4 <video_path> <parameter>?"
	
clean:
	rm -r exe
