include config.mk

# building actual program

debug-build:
	${DCOMMAND_P} src/main.cpp ${DCOMMAND_S} -o abg.out

build:
	${COMMAND_P} src/main.cpp ${COMMAND_S} -o abg.out

release-build: build

man:
	mkdir -p ${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < abg.1 > ${DESTDIR}${MANPREFIX}/man1/abg.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/abg.1
install: release-build man
	cp abg.out /usr/local/bin/abg
clean:
	rm *.out

# other
fmt:
	clang-format -i src/*.cpp
	clang-format -i tests/*.cpp
format: fmt

# snapshot update
snapshot-update:
	${TCOMMAND_P} tests/snapshot_update.cpp ${TCOMMAND_S} -o snapshot_update.out
	./snapshot_update.out
	rm snapshot_update.out

# tests
snapshot-test:
	${TCOMMAND_P} tests/snapshot_test.cpp ${TCOMMAND_S} -o snapshot_tests.out
	./snapshot_tests.out
	rm snapshot_tests.out
graph-test:
	${TCOMMAND_P} tests/graph_test.cpp ${TCOMMAND_S} -o graph_tests.out
	./graph_tests.out
	rm graph_tests.out
algo-test:
	${TCOMMAND_P} tests/algo_test.cpp ${TCOMMAND_S} -o algo_tests.out
	./algo_tests.out
	rm algo_tests.out

test: format snapshot-test graph-test algo-test
