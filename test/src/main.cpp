#include <iostream>

#include <gtest/gtest.h>
#include <gflags/gflags.h>

using namespace std;

DEFINE_int32(seed, 0, "Use given seed to repeat previous result, 0 means use current time as seed");

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);

    gflags::SetUsageMessage("Runs the tests for codility");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    if ( argc > 1 ) {
        cerr << "Command line arguments not recognized, please see following for usage:" << endl;
        cerr << "  " << argv[0] << " --help" << endl;
        exit(1);
    }

    return RUN_ALL_TESTS();
}
