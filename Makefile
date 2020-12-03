OBJECTS := main.o JSON.o units.o Hero.o Monster.o Map.o Game.o MarkedMap.o PreparedGame.o Renderer.o
COMP := clang++ -Wall -std=c++17

build-game: $(OBJECTS)
	$(COMP) -o game $(OBJECTS)

main.o: main.cpp units.h JSON.h Hero.h Monster.h
	$(COMP) -c main.cpp

JSON.o: JSON.cpp JSON.h
	$(COMP) -c JSON.cpp

units.o: units.cpp units.h JSON.h
	$(COMP) -c units.cpp

Monster.o: Monster.cpp Monster.h units.h JSON.h
	$(COMP) -c Monster.cpp

Hero.o: Hero.cpp Hero.h units.h JSON.h
	$(COMP) -c Hero.cpp

Map.o: Map.cpp Map.h
	$(COMP) -c Map.cpp

MarkedMap.o: MarkedMap.cpp MarkedMap.h units.h
	$(COMP) -c MarkedMap.cpp

PreparedGame.o: PreparedGame.cpp PreparedGame.h Game.h JSON.h MarkedMap.h Renderer.h
	$(COMP) -c PreparedGame.cpp

Renderer.o: Renderer.cpp Renderer.h Game.h
	$(COMP) -c Renderer.cpp

Game.o: Game.cpp Game.h Map.h JSON.h units.h Monster.h Hero.h
	$(COMP) -c Game.cpp

output-tests:
	./run_test.sh game

io-diff-tests:
	diff output1.txt good_output1.txt
	diff output2.txt good_output2.txt

Unit-tests:
	cd tesztek && cmake CMakeLists.txt
	cd tesztek && make
	cd tesztek && ./runTests

static-code-analysis:
	cppcheck *.cpp --enable=warning --output-file=errors.txt
	./static_check.sh
	cppcheck *.cpp --enable=style --enable=performance --output-file=artifact.txt
	
memory-leak-check:
	valgrind --leak-check=full --error-exitcode=1 ./game scenario1.json

documentation:
	doxygen doxyconfig

clean:
	rm *.o game tesztek/cmake_install.cmake tesztek/CMakeCache.txt tesztek/Makefile tesztek/runTests
	rm -r tesztek/CMakeFiles