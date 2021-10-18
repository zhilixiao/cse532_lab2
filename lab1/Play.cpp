#include "Play.hpp"

void Play::recite(std::map<unsigned int, name_script>::iterator it)
{
    //synchronize with mutex, conditon
    std::unique_lock<std::mutex> lg(m);
     
    if (cnt < it->first)
    {
        //wait on condition
        cv.wait(lg, [this, &it] {return this->cnt == it->first;});

        if (cur_charName.compare(it->second.first)){
            
            std::cout << std::endl;
            std::cout << it->second.first << std::endl;
            cur_charName = it->second.first;
        }
        std::cout << it->second.second << std::endl;
        cnt++;
        cv.notify_all();
        return;
    }
    else if (cnt > it->first)
    {
        std::cerr << "counter bigger than line number" << std::endl;
        it++;
        cv.notify_all();
        return;
    }
    else{//cnt == it->first
        
        if (cnt == 1){
            std::cout << it->second.first << std::endl;
            cur_charName = it->second.first;
        }
        


        std::cout << it->second.second << std::endl;
        cnt++;
        cv.notify_all();
        return;
    }
    return;



}