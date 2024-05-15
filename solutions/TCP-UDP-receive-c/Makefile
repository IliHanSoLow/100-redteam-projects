all:
	make -C build


run: all
	./build/tcp_server

clear:
	rm -rf build/*
	rm -rf build/.*

setup: clear
	cmake -B build -S .
