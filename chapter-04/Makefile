%PHONY: run_serial_map
run_serial_map: serial_map
	./serial_map

serial_map: serial_map.o
	clang++ -ltbb -std=c++1z $< -o $@

%.o: %.cpp
	clang++ -std=c++1z -O3 -c $< -o $@