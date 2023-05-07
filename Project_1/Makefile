all: clean main.cpp

driver2: driver2.cpp main.cpp cssText.cpp Selector.cpp
	@echo "-------------------------------------------"
	@echo "Compiling... Hocam durun bekleyin yavas compile ediyo bi 15 saniye falan suruyo. Compile edilirken bu yaziyi okuyabilirsiniz tesekkurler :)"
	@g++ -std=c++11 -g -O3 -o main main.cpp cssText.cpp Selector.cpp
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "================================================================================="
	./driver2
	@echo "================================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f driver1 driver2
