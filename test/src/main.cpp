#include <iostream>

#include <gtest/gtest.h>
#include <gflags/gflags.h>

using namespace std;

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);

    gflags::SetUsageMessage("Runs the tests for codility");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    if ( argc > 1 ) {
        cerr << "Command line arguments not recognized, please execute:" << endl;
        cerr << "  " << argv[0] << " --help" << endl;
        exit(1);
    }

    return RUN_ALL_TESTS();
}
