// Main.cpp - Zander Clucas 2014
// The entry point

#include "System.h"

// The entry point.
int main( int argc, char **argv )
{
    System sys;

    if(!sys.init(argc, argv))
    {
        return 0;
    }

    return sys.run();
}