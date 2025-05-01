CXX = g++
CXXFLAGS = -std=c++17 -I. -Werror -Wpedantic -Wall -Wextra -g -fPIC
LDFLAGS = -lm

TARGET = prog
LIBPROJECT = lib$(TARGET).a
TESTPROJECT = test-$(TARGET)

SRC_DIR = src
TEST_DIR = tests

SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS = $(SOURCES:.cpp=.o)
DEPENDS = $(OBJECTS:.o=.d)

TEST_SOURCES := $(shell find $(TEST_DIR) -name '*.cpp')
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_DEPENDS = $(TEST_OBJECTS:.o=.d)

LDXXFLAGS = -L. -l:$(LIBPROJECT) $(LDFLAGS)
LDGTESTFLAGS = $(LDXXFLAGS) -lgtest -lgtest_main -pthread

.PHONY: all clean cleanall tests runtests

all: $(TARGET) $(LIBPROJECT)

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(LIBPROJECT): $(OBJECTS)
	$(AR) rcs $@ $^

$(TESTPROJECT): $(LIBPROJECT) $(TEST_OBJECTS)
	$(CXX) -o $@ $(TEST_OBJECTS) $(LDGTESTFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(DEPENDS) $(TEST_DEPENDS)

tests: $(TESTPROJECT)

runtests: $(TESTPROJECT)
	./$(TESTPROJECT)

clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(DEPENDS) $(TEST_DEPENDS)

cleanall: clean
	rm -f $(TARGET) $(LIBPROJECT) $(TESTPROJECT)