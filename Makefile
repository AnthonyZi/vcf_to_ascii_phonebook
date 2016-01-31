MAKE = make
CC = gcc
CXX = g++

##################
CFLAGS = -Wall -g -O3 -std=c++11
CXXFLAGS = $(CFLAGS)
LDFLAGS = 

NAME = phonebook

CSOURCE =
CPPSOURCE = phonebook.cpp friend.cpp vcfio.cpp

VCF = combine.vcf
#################

OBJS += $(patsubst %.cpp, %.o, $(filter %.cpp, $(CPPSOURCE)))
OBJS += $(patsubst $.c, %.o, $(filter %.c, $(CSOURCE)))

%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

default : $(NAME)
	$(MAKE) $(NAME)
	./$(NAME) $(VCF)
	less myphonebook

compile : 
	$(MAKE) $(NAME)

run :
	./$(NAME) $(IMAGE)

#all :
#	$(MAKE) $(NAME)	

$(NAME) : $(OBJS)
	$(CXX) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

clean :
	rm -rf *.o

veryclean : clean
	rm -rf $(NAME)

depend :
	$(CXX) -MM $(CFLAGS) $(CSOURCE) $(CPPSOURCE) > Makefile.dep

-include Makefile.dep

.PHONY: all clean default depend veryclean
