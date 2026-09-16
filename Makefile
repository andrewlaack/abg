include config.mk

# building actual program
build:
	${COMMAND_P} src/main.cpp ${COMMAND_S} -o abg.out
man:
	mkdir -p ${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < abg.1 > ${DESTDIR}${MANPREFIX}/man1/abg.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/abg.1
install: build man
	cp abg.out /usr/local/bin/abg
clean:
	rm abg.out

# other
fmt:
	clang-format -i src/*.cpp
	clang-format -i tests/*.cpp
format: fmt

# snapshot update
snapshot-update:
	${TCOMMAND_P} tests/snapshot_update.cpp ${TCOMMAND_S} -o snapshot_update
	./snapshot_update
	rm snapshot_update

# tests
snapshot-test:
	${TCOMMAND_P} tests/snapshot_test.cpp ${TCOMMAND_S} -o snapshot_tests
	./snapshot_tests
	rm snapshot_tests
graph-test:
	${TCOMMAND_P} tests/graph_test.cpp ${TCOMMAND_S} -o graph_tests
	./graph_tests
	rm graph_tests
algo-test:
	${TCOMMAND_P} tests/algo_test.cpp ${TCOMMAND_S} -o algo_tests
	./algo_tests
	rm algo_tests

test: format snapshot-test graph-test algo-test
