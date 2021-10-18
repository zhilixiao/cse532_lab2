#pragma once

#include <iostream>
#include <fstream>
#include <mutex>
#include <condition_variable>

#include <map>
//define a struct where the first string is the character's name, and the second is the line of this character
typedef std::pair<std::string, std::string> name_script;

//define the line struct to map the line number with name_script
typedef std::pair<unsigned int, name_script> line_stuct;

class Play
{
private:
    std::string playName;

    //atomic?
    unsigned int cnt;

    //to keep track of current character
    std::string cur_charName;

    //use of map to sort the scripts automatically
    std::map<unsigned int, name_script> scripts;
    //private access to mutex
    std::mutex m;

    std::condition_variable cv;
    



public:
    Play(std::string Name):playName(Name), cnt(1)
    {}
    
    void recite(std::map<unsigned int, name_script>::iterator it);


};