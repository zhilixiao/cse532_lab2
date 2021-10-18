#include <iostream>
#include <fstream>
#include <sstream>
#include <map>


#define SUCCESS 0
#define SCRIPT_NAME 1
#define CONFIG_NAME 2
#define PLAY_NAME 3

int main(int argc, char* argv[]){
    std::string script =  argv[SCRIPT_NAME];
    std::string configfile = argv[CONFIG_NAME];


    std::ifstream ifs(script);

    std::ofstream ofs_config(configfile);

    //insert play name to config file
    for (int i = PLAY_NAME; i < argc; i++){
        ofs_config << argv[i]; 
    }
    ofs_config << std::endl;

    std::map<int, std::string> num_lines;
    std::map<std::string, std::ofstream*> player_files;

    if (ifs.is_open()){

        int line_cnt = 1;

        std::string line;
        int name_flag = 1;
        std::string cur_name;


        std::map<std::string, std::ofstream*>::iterator it;
        while(getline(ifs, line))
        {
            //the first character
            if(name_flag == 1){
                cur_name = line;

                //find if the character has been added to the map
                it = player_files.find(cur_name);
                if (it == player_files.end()){

                    std::cout << "add character " << cur_name << std::endl;

                    std::ofstream* ofs = new std::ofstream;
                    std::string fileName = cur_name + "txt";
                    ofs.open(fileName);
                   
                    player_files.insert(std::pair<std::string,  std::ofstream*>(cur_name, ofs));
                }
                name_flag = 0;
                continue;
            }
                
            if(line.empty()){
                name_flag = 1;
                continue;
            }

            //script
            std::ofstream* ofs = player_files.find(cur_name)->second;
            *ofs << line_cnt << " " << line << std::endl;
            line_cnt = line_cnt + 1;
        }
    }
    
    //clean ofstream pointer
    for(it = player_files.begin(); it != player_files.end(); it++){
        delete it->second;
    }

    return SUCCESS;

}