build:
	g++ -Ofast src/main.cpp src/prim.cpp src/graph.cpp src/edge.cpp src/utils.cpp src/vertex.cpp -lraylib -o background
install: build
	cp background /usr/local/bin
clean:
	rm background
test:
	g++ tests/graph_test.cpp src/prim.cpp src/graph.cpp src/edge.cpp src/utils.cpp src/vertex.cpp -lCatch2Main -lCatch2 -lraylib -o graph_tests
	./graph_tests
	rm graph_tests
	g++ tests/algo_test.cpp src/prim.cpp src/graph.cpp src/edge.cpp src/utils.cpp src/vertex.cpp -lCatch2Main -lCatch2 -lraylib -o algo_tests
	./algo_tests
	rm algo_tests
