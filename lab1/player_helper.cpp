#include "player_helper.hpp"

//check if this line is all white spaces
bool is_all_white_spaces(std::string str){
    return std::all_of(str.begin(), str.end(), isspace);
}

//used to elminate white space before the actual script
std::string trim(const std::string& str ){
    size_t found = str.find_first_not_of(" ");
    return str.substr(found);
}

//used to tell if the first white space delimited tokens can be converted to unsigned integer
bool isnumber(std::string s)
{
    for (unsigned int i = 0; i < s.length(); i++){
        if (isdigit(s[i]) == false)
            return false;
    }
    return true;
}