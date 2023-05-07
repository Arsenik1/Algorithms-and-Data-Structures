all: clean compile run

compile: main.cpp Navigation.cpp City.cpp Vector.cpp String.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -std=c++11 -g -O3 -o main main.cpp Navigation.cpp City.cpp Vector.cpp String.cpp
	@echo "-------------------------------------------"

run: main
	@echo "Running the tests...."
	@echo "================================================================================="
	./main
	@echo "================================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f main
