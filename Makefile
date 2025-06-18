# tomergal40@gmail.com
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Source files
HEADERS = MyContainer.hpp
DEMO_SRC = Demo.cpp
TEST_SRC = test.cpp

# Executables
DEMO_EXEC = Demo
TEST_EXEC = TestRunner

# Default target
all: $(DEMO_EXEC) $(TEST_EXEC)

# Build and run demo
Main: $(DEMO_EXEC)
	./$(DEMO_EXEC)

# Build demo executable
$(DEMO_EXEC): $(DEMO_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(DEMO_EXEC) $(DEMO_SRC)

# Build and run tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Build test executable
$(TEST_EXEC): $(TEST_SRC) $(HEADERS) doctest.h
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(TEST_SRC)

# Valgrind memory check
valgrind: $(DEMO_EXEC) $(TEST_EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(DEMO_EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_EXEC)

# Clean up generated files
clean:
	rm -f $(DEMO_EXEC) $(TEST_EXEC) *.o

.PHONY: all Main test valgrind clean