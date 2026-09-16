build:
	g++ -Ofast src/main.cpp src/prim.cpp src/graph.cpp src/edge.cpp src/utils.cpp src/vertex.cpp src/background.cpp -lraylib  -lX11 -o abg.out
install: build
	cp abg.out /usr/local/bin/abg
clean:
	rm abg.out
update-snapshot:
	g++ tests/snapshot_update.cpp src/prim.cpp src/graph.cpp src/edge.cpp src/utils.cpp src/vertex.cpp src/background.cpp -lCatch2Main -lCatch2 -lraylib -lX11 -o snapshot_update
	./snapshot_update
	rm snapshot_update
test:
	g++ tests/snapshot_test.cpp src/prim.cpp src/graph.cpp src/edge.cpp src/utils.cpp src/vertex.cpp src/background.cpp -lCatch2Main -lCatch2 -lraylib -lX11 -o snapshot_tests
	./snapshot_tests
	rm snapshot_tests
	g++ tests/graph_test.cpp src/prim.cpp src/graph.cpp src/edge.cpp src/utils.cpp src/vertex.cpp src/background.cpp -lCatch2Main -lCatch2 -lraylib -lX11 -o graph_tests
	./graph_tests
	rm graph_tests
	g++ tests/algo_test.cpp src/prim.cpp src/graph.cpp src/edge.cpp src/utils.cpp src/vertex.cpp src/background.cpp -lCatch2Main -lCatch2 -lraylib -lX11 -o algo_tests
	./algo_tests
	rm algo_tests
