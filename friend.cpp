#include "friend.h"

Friend::Friend() : name(""), fname1(""), fname2("")
{
}

Friend::~Friend()
{
        for(int i = numbers.size(); i>0; i--)
        {
                numbers.pop_back();
        }
}

void Friend::setname(std::string pname)
{
        name = pname;
}

void Friend::setname(std::string pname, std::string pfname1, std::string pfname2)
{
        name = pname;
        fname1 = pfname1;
        fname2 = pfname2;
}

void Friend::setfname1(std::string pfname1)
{
        fname1 = pfname1;
}

void Friend::addnumber(std::string pnumber)
{
        numbers.push_back(pnumber);
}

std::string Friend::getname()
{
        return name;
}

std::string Friend::getfname()
{
        std::string fname = fname1 + " " + fname2;
        return fname;
}

std::string Friend::getfullname()
{
        std::string ret = name + ", " + fname1 + " " + fname2;
        return ret;
}

std::string Friend::getfullname2()
{
        std::string ret = fname1 + (fname2.compare("") != 0 ? " " + fname2 : "") + " " + name;
        return ret;
}

std::vector<std::string> Friend::getnumbers()
{
        return numbers;
}
