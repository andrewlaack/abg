include config.mk


build:
	${COMMAND_P} src/main.cpp ${COMMAND_S} -o abg.out
install: build
	cp abg.out /usr/local/bin/abg
clean:
	rm abg.out
update-snapshot:
	${TCOMMAND_P} tests/snapshot_update.cpp ${TCOMMAND_S} -o snapshot_update
	./snapshot_update
	rm snapshot_update
test:
	${TCOMMAND_P} tests/snapshot_test.cpp ${TCOMMAND_S} -o snapshot_tests
	./snapshot_tests
	rm snapshot_tests
	${TCOMMAND_P} tests/graph_test.cpp ${TCOMMAND_S} -o graph_tests
	./graph_tests
	rm graph_tests
	${TCOMMAND_P} tests/algo_test.cpp ${TCOMMAND_S} -o algo_tests
	./algo_tests
	rm algo_tests
