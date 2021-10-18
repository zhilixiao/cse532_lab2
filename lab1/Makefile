CXX = g++ -Wall
CXXFLGAS := -std=c++11

CXX_SRC = lab1.cpp Play.cpp player_helper.cpp Player.cpp # 
#synchronization2.cpp
CXX_EXE = lab1

LIBS = -lpthread

$(CXX_EXE): $(CXX_SRC)
	$(CXX) $(CXXFLGAS) $(CXX_SRC) $(LIBS) -o $@ -DDEBUG
#

clean:
	rm $(CXX_EXE)
