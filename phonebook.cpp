#include <vector>
#include "friend.h"
#include "vcfio.h"
#include <iostream>

std::vector<Friend*> friends;

int main(int argc, char* argv[])
{
        system("./combine.sh");
        VCFIO *io = new VCFIO();

        io->readvcf(argv[1]);
        friends = io->getfriends();
        io->setfriends(friends);
        io->writephonebook("myphonebook");

        delete io;

        return 0;
}
