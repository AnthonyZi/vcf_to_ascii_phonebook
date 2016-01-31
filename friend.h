#ifndef FRIEND_H
#define FRIEND_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

class Friend
{
private:
        std::string name, fname1, fname2;
        std::vector<std::string> numbers;

public:
        Friend();
        ~Friend();

        void setname(std::string pname);
        void setname(std::string pname, std::string pfname1, std::string pfname2 = "");
        void setfname1(std::string pfname1);

        void addnumber(std::string pnumber);

        std::string getname();
        std::string getfname();
        //Mustermann, Max Herbert
        std::string getfullname();
        //Max Herbert Mustermann
        std::string getfullname2();
        std::vector<std::string> getnumbers();
};

#endif
