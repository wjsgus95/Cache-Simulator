#include <iostream>

#include "cache.h"

using namespace std;

int main(int argc, char** argv) {
    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " " << "memory_trace [config_file]" << endl;
        exit(1);
    }

    // Create trace model.
    //trace_t trace = trace_t(argv[1]);

    // Generate default config.
    config_t config;
    // Parse config file if given any.
    if(argc == 3) { config = config_t(argv[2]); }

    // Create cache model.
    //cache_t* cache = cache_t::create(config);
    // Run trace.
    //cache->run(trace);

    //delete cache;
    return 0;
}
