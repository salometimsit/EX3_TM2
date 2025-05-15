CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC -I.
QTFLAGS = $(shell pkg-config --cflags --libs Qt5Widgets)

SRC = main.cpp \
      GUI.cpp \
      moc_GUI.cpp \
      Game.cpp \
      Player.cpp\
      PlayerManager.cpp \
      Roles/Role.cpp \
      Roles/RoleFactory.cpp \
      Actions/ActionFactory.cpp \
      Actions/AllAction.cpp\
      Roles/AllRole.cpp    # ← ✅ Add this line

OBJ = $(SRC:.cpp=.o)
TARGET = coup_game

all: $(TARGET)

# Automatically generate moc_GUI.cpp before compiling GUI.o
moc_GUI.cpp: GUI.hpp
	moc GUI.hpp -o moc_GUI.cpp

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(QTFLAGS)

%.o: %.cpp moc_GUI.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(QTFLAGS)

clean:
	rm -f $(OBJ) $(TARGET) moc_GUI.cpp
