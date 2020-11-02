OBJECTS := main.o jsonparser.o units.o
COMP := g++ -Wall -std=c++17

build-game: $(OBJECTS)
	$(COMP) -o game $(OBJECTS)

main.o: main.cpp
	$(COMP) -c main.cpp

jsonparser.o: jsonparser.cpp
	$(COMP) -c jsonparser.cpp

units.o: units.cpp
	$(COMP) -c units.cpp

permission:
	chmod +x ./run_test.sh ./static_check.sh

output-tests:
	./run_test.sh game

io-diff-tests:
	diff output.txt good_output.txt

Unit-tests:
	cd /usr/src/gtest && sudo cmake CMakeLists.txt && sudo make
	cd tesztek && cmake CMakeLists.txt
	cd tesztek && make
	cd tesztek && ./runTests

static-code-analysis:
	sudo apt-get install cppcheck
	cppcheck *.cpp --enable=warning --output-file=errors.txt
	./static_check.sh
	cppcheck *.cpp --enable=style --enable=performance --output-file=artifact.txt
	
memory-leak-check:
	sudo apt install valgrind
	valgrind --leak-check=full --error-exitcode=1 ./game units/unit1.json units/unit2.json
clean:
	rm *.o game tesztek/cmake_install.cmake tesztek/CMakeCache.txt tesztek/Makefile tesztek/runTests
	rm -r tesztek/CMakeFiles