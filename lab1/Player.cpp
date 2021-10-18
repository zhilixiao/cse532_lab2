#include "Player.hpp"


Player::Player(Play& mplay_, const std::string& char_name_, std::ifstream& ifs_):
    mplay(mplay_), char_name(char_name_), ifs(ifs_)
{

}

void Player::read()
{
    //std::cout << "read()" << std::endl;
    if (ifs.is_open()){
        std::string str;
        while(std::getline(ifs, str)){ 
            name_script mname_script;  

            //Skip a blank character line;
            if(is_all_white_spaces(str)){
                continue;
            }
            size_t npo = str.find(" "); 
                
            //Skip an invalid character line
            if (npo == std::string::npos){
                continue;
            }
                
            //get the line number
            std::string num = str.substr(0, npo);

            //Cannot convert line number
            if (!isnumber(num)){
                continue;
            }
            unsigned int line_num = std::stoi(str.substr(0, npo));

            //check second white space token
            if(is_all_white_spaces(str.substr(npo + 1))){
                continue;
            }

            //get the line script, trim it to format inputs
            std::string words = trim(str.substr(npo + 1));  

            //packed into line struct
            mname_script = std::make_pair(char_name, words);
            line_stuct line = std::make_pair(line_num, mname_script);

            //insert into the container
            scripts.insert(line);
        }
    }
    else{
        std::cout << "Thread_funct: Error Opening Character File" << std::endl;
    }
}

void Player::act(){
    
    for(std::map<unsigned int, name_script>::iterator it = scripts.begin(); it != scripts.end(); ++it)
        mplay.recite(it);

}

void Player::enter(){
    std::thread t([this](){
        try{
            this->read();
            this->act();
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }

    }); 
    player_thread = std::move(t);
}

void Player::exit(){
    if (player_thread.joinable())
        player_thread.join();
}


