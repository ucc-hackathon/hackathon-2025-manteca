CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Ejecutables
all: path_game/path_game soccer_game/soccer_game ucc_lib/ucc_lib

# =======================
# PATH_GAME
# =======================
path_game/path_game: path_game/main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# =======================
# SOCCER_GAME
# =======================
soccer_game/soccer_game: soccer_game/main.cpp soccer_game/lib.cpp soccer_game/lib.h
	$(CXX) $(CXXFLAGS) soccer_game/main.cpp soccer_game/lib.cpp -o $@

# =======================
# UCC_LIB
# =======================
ucc_lib/ucc_lib: ucc_lib/main.cpp ucc_lib/lib.cpp ucc_lib/lib.h
	$(CXX) $(CXXFLAGS) ucc_lib/main.cpp ucc_lib/lib.cpp -o $@

# =======================
# CLEAN
# =======================
clean:
	rm -f path_game/path_game soccer_game/soccer_game ucc_lib/ucc_lib

