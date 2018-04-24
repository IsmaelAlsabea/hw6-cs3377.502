
# Author: Ismael Alsabea
 #Email:  isa170030@utdallas.edu     


CXX = g++
CXXFLAGS =
#CPPFLAGS = -Wall -g -I/people/cs/s/sxp127930/include
#LDFLAGS = -L/people/cs/s/sxp127930/lib
CPPFLAGS = -Wall -g -I/scratch/perkins/include
LDLFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses 


#
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters

EXECFILE = program6

OBJS = program6.o


all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $(OBJS) -L/scratch/perkins/lib $(LDLIBS)

