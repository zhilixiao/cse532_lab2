#pragma once

#include <iostream>
#include <fstream>
#include <thread>
#include <map>
#include <exception>
#include "Play.hpp"
#include "player_helper.hpp"

class Player 
{
private:
    Play& mplay;
    const std::string& char_name;
    std::ifstream& ifs;
    std::map<unsigned int, name_script> scripts;
    std::thread player_thread;

    void read();
    void act();

public:
    Player(Play& mplay_, const std::string& char_name_, std::ifstream& ifs_);
    void enter();
    void exit();

};