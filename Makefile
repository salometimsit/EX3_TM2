#timsitmelosa@gmail.com
CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC -I. -IAll_Test -IGamelogic
QTFLAGS = $(shell pkg-config --cflags --libs Qt5Widgets)

SRC = main.cpp \
      Gamelogic/GUI.cpp \
      Gamelogic/moc_GUI.cpp \
      Gamelogic/Game.cpp \
      Players/Player.cpp \
      Players/PlayerManager.cpp \
      Roles/Role.cpp \
      Roles/RoleFactory.cpp \
      Actions/ActionFactory.cpp \
      Actions/AllAction.cpp \
      Roles/AllRole.cpp

OBJ = $(SRC:.cpp=.o)
TARGET = coup_game

# Test sources
TEST_SRC = All_Tests/all_tests.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_TARGET = run_tests

all: $(TARGET)

# Automatically generate moc_GUI.cpp before compiling GUI.o
Gamelogic/moc_GUI.cpp: Gamelogic/GUI.hpp
	moc Gamelogic/GUI.hpp -o Gamelogic/moc_GUI.cpp

# Ensure GUI.o depends on the moc file
Gamelogic/GUI.o: Gamelogic/moc_GUI.cpp

# Generic rule for compiling .cpp files into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(QTFLAGS) -c $< -o $@

# Link final executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(QTFLAGS)

# Test target build
$(TEST_TARGET): $(TEST_OBJ)  $(filter-out main.o, $(OBJ))
	$(CXX) $(CXXFLAGS) $^ -o $@ $(QTFLAGS)
valgrind-tests: $(TEST_TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TEST_TARGET)

clean:
	rm -f $(OBJ) $(TARGET) $(TEST_OBJ) $(TEST_TARGET) Gamelogic/moc_GUI.cpp
