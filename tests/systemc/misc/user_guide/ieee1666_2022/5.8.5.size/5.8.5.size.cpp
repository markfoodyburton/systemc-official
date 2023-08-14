// COMPLETE TEST
//
// If this test does not assert it indicates the example is executing correctly.

#include <systemc.h>

int sc_main( int argc, char* argv[] ) { 

    using namespace sc_core;
    sc_event ev;
    sc_event_or_list list = ev | ev;
    sc_assert( list.size() == 1 );

    std::cout << "program completed" << std::endl;
    return 0;
}
