#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <string>

#include <map>
#include <functional>


#include "Play.hpp"
#include "Player.hpp"

#define ARG_NUM 2
#define LINE_PLAY_NAME 1
#define SUCCESS 0
#define PROGRAM_NAME 0 
#define CONFIG_NAME 1
#define ERR_ARGS -1
#define ERR_INVALID_CONFIG -2
#define ERR_OPEN_CONFIG -3
#define ERR_OPEN_CHAR -4



//print helpful message about the program, called by check_args
void print_help_messeage(char* argv[]){
    std::cout << "usage: " << argv[PROGRAM_NAME] << " <configuration_file_name>" << std::endl;
}

void check_args(int argc, char* argv[]){
    if(argc < ARG_NUM){
        print_help_messeage(argv);
        exit(ERR_ARGS);
    }
}



//read configuration file, return number of Players
int read_config_file(int argc, char* argv[], std::string& playName, std::map<std::string, std::ifstream*>& character_fstreams){
    std::ifstream ifs(argv[CONFIG_NAME]);
    int line_num = 0;
    int num_players = 0;
    if (ifs.is_open()){
        std::string line;
        while(getline(ifs, line)){
            //skip blank lines and white spaces line
            if (!is_all_white_spaces(line)){
                line_num++;
                //if this line is the play name
                if(line_num == LINE_PLAY_NAME){
                    playName = line;
                }
                else{
                    std::istringstream iss(line);
                    std::string charName, fileName;
                    
                    //read in two white space delimited tokens, and ignore others
                    if((iss >> charName >> fileName)){
                        std::ifstream* ifs = new std::ifstream(fileName);
                        if (!ifs->is_open()){
                            std::cout << "Error opening the character file for " << charName << std::endl;
                            
                            //clean ifstream pointers
                            std::map<std::string, std::ifstream*>::iterator it;
                            for(it = character_fstreams.begin(); it != character_fstreams.end(); it++)
                                delete it->second;

                            exit(ERR_OPEN_CHAR);
                        }
                        num_players++;
                        character_fstreams.insert(std::pair<std::string,  std::ifstream*>(charName, ifs));

                    }
                    else{
                        std::cout << "skip ill formed line" << std::endl;
                    }
                }
            }
        }
        //if there is no single non-empty line
        if(line_num == 0)
        {
            std::cout << "Invalid Configuration File" << std::endl;
            exit(ERR_INVALID_CONFIG);
        }
        if(num_players == 0)
        {   
            std::cout << "no valid character input in configuration file" << std::endl;
            exit(ERR_INVALID_CONFIG);
        }

        return num_players;
    }
    else{
        std::cout << "Error Opening Configuration File" << std::endl;
        exit(ERR_OPEN_CONFIG);
    }

}


int main(int argc, char* argv[]){
    std::string playName;

    //check argument, exit if invalid args
    check_args(argc, argv);

    std::map<std::string, std::ifstream*> character_file;
    
    //read configuration file to get character part files 
    read_config_file(argc, argv, playName, character_file);

    //create the Play object
    Play myPlay(playName); 

    //create Player objects
    std::vector<Player> players;

    std::map<std::string, std::ifstream*>::iterator it; 

    
    for(it = character_file.begin(); it != character_file.end(); ++it){
        //Player p = new Play
        players.emplace_back(myPlay, it->first, *(it->second));
    }

    std::vector<Player>::iterator player_it;

    //enter
    for(player_it = players.begin(); player_it != players.end(); ++player_it)
       player_it->enter();

    //read
    for(player_it = players.begin(); player_it != players.end(); ++player_it)
        player_it->exit();
    
    //clean ifstreams
    for(it = character_file.begin(); it != character_file.end(); ++it){
        delete it->second;
    }
    
    

    return SUCCESS;
}