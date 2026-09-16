build:
	g++ -Ofast src/main.cpp src/prim.cpp src/graph.cpp src/edge.cpp src/utils.cpp src/vertex.cpp src/background.cpp -lraylib  -lX11 -o background.out
install: build
	cp background.out /usr/local/bin/background
clean:
	rm background.out
test:
	g++ tests/graph_test.cpp src/prim.cpp src/graph.cpp src/edge.cpp src/utils.cpp src/vertex.cpp src/background.cpp -lCatch2Main -lCatch2 -lraylib -lX11 -o graph_tests
	./graph_tests
	rm graph_tests
	g++ tests/algo_test.cpp src/prim.cpp src/graph.cpp src/edge.cpp src/utils.cpp src/vertex.cpp src/background.cpp -lCatch2Main -lCatch2 -lraylib -lX11 -o algo_tests
	./algo_tests
	rm algo_tests
