#include "vcfio.h"

VCFIO::VCFIO()
{
}

VCFIO::~VCFIO()
{
        Friend *f;
        for(int i = friends.size(); i>0; i--)
        {
                f = friends.back();
                friends.pop_back();
                delete f;
        }
}

void VCFIO::readvcf(std::string pfilename)
{
        std::fstream fs;
        fs.open(pfilename.c_str(), std::fstream::in);

        if(!fs)
        {
                std::cerr << "error while opening " << pfilename << std::endl;
        }

        std::string input;
        Friend *f;
        while(!fs.eof())
        {
                std::getline(fs, input);
                if(input.substr(0,5).compare("BEGIN") == 0)
                {
                        f = new Friend();
                }
                if(input.substr(0,3).compare("END") == 0)
                {
                        friends.push_back(f);
                }

                if(input.substr(0,2).compare("N:") == 0)
                {
                        std::size_t pos = input.find(";");
                        std::size_t pos2 = input.find(";", pos+1);
                        std::size_t pos3 = input.find(";", pos2+1);

                        std::string name, fname1, fname2;

                        name = input.substr(2, pos-2);
                        fname1 = input.substr(pos+1, pos2-pos-1);
                        fname2 = input.substr(pos2+1, pos3-pos2-1);

                        f->setname(name, fname1, fname2);
                }

                if(input.substr(0,42).compare("N;CHARSET=UTF-8;ENCODING=QUOTED-PRINTABLE:") == 0)
                {
                        std::size_t cutpos = input.find(":");
                        input = input.substr(cutpos);
                        std::size_t pos = input.find(";");
                        std::size_t pos2 = input.find(";", pos+1);
                        std::size_t pos3 = input.find(";", pos2+1);

                        std::string name, fname1, fname2;

                        name = convertUTF8(input.substr(2, pos-2));
                        fname1 = convertUTF8(input.substr(pos+1, pos2-pos-1));
                        fname2 = convertUTF8(input.substr(pos2+1, pos3-pos2-1));

                        f->setname(name, fname1, fname2);
                }


                if(input.substr(0,3).compare("TEL") == 0)
                {
                        std::size_t pos = input.find(":");

                        std::string snumber = input.substr(pos+1);
                        snumber.erase(remove(snumber.begin(), snumber.end(), '-'), snumber.end());
                        snumber.erase(remove(snumber.begin(), snumber.end(), ' '), snumber.end());
                        snumber.erase(remove(snumber.begin(), snumber.end(), '\r'), snumber.end());

                        f->addnumber(snumber);
                }
        }
        fs.close();
}

void VCFIO::writephonebook(std::string pfilename)
{
        std::fstream fs;
        fs.open(pfilename.c_str(), std::fstream::out);
        for(unsigned int i = 0; i<friends.size(); i++)
        {
                if(i > 0)
                        fs << std::setfill('-') << std::setw(61) << " " << std::setfill(' ') << std::endl;
                fs << std::left << "--   " << std::setw(30) << friends[i]->getfullname2() << std::right;
                std::vector<std::string> numbers = friends[i]->getnumbers();
                if(numbers.size() > 0)
                        fs << std::setw(20) << (numbers.size() > 0 ?numbers[0] : " ") << "   --" << std::endl;
                for(unsigned int i = 1; i<numbers.size(); i++)
                        fs << std::setw(35) << std::left << "--   " << std::setw(20) << std::right << numbers[i] << "   --" << std::endl;
        }
        fs.close();
}

std::vector<Friend*> VCFIO::getfriends()
{
        return friends;
}

void VCFIO::setfriends(std::vector<Friend*> pfriends)
{
        friends = pfriends;
}

std::string VCFIO::convertUTF8(std::string putf8)
{
        std::vector<std::string> chars;
        std::size_t pos;
        std::string tmp;
        while(putf8.length() > 0)
        {
                pos = putf8.find("=");
                if(pos == std::string::npos)
                        break;
                tmp = putf8.substr(0,pos);
                if(tmp.compare("") != 0)
                        chars.push_back(tmp);
                putf8 = putf8.substr(pos+1);
        }

        std::string out;
        for(unsigned int i = 0; i< chars.size(); i++)
        {
                out += decodeUTF8(chars[i]);
        }
        return out;
}

std::string VCFIO::decodeUTF8(std::string pcode)
{
        int code = stol(pcode, NULL, 16); 

        char c = code < 256 ? code : 53;
        std::string out;
        out += c;
        return out;
}
