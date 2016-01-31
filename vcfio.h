#ifndef VCFIO_H
#define VCFIO_H

#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <iomanip>
#include <algorithm>
#include "friend.h"

class VCFIO
{
private:
        std::vector<Friend*> friends;
        
public:
        VCFIO();
        ~VCFIO();

        void readvcf(std::string pfilename);
        void writephonebook(std::string pfilename);
        std::vector<Friend*> getfriends();
        void setfriends(std::vector<Friend*> pfriends);

        std::string convertUTF8(std::string putf8);
        std::string decodeUTF8(std::string pcode);
};

#endif
