#include <iostream>

#include "system.h"
#include "cache.h"
#include "trace.h"

using namespace std;

int main(int argc, char** argv) {
    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " " << "memory_trace [config_file]" << endl;
        exit(0);
    }

    // Create trace model.
    trace_t trace = trace_t(argv[1]);

    // Generate default config.
    config_t config;
    // Parse config file if given any.
    if(argc == 3) { config = config_t(argv[2]); }

    // Configure general settings.
    section_t& general = config.get_section("general");
    system::init(general);

    // Create multi-level cache.
    unsigned level = 1;
    string cache_name = string("cache") + to_string(level);
    while(config.exists(cache_name)) {
        section_t& section = config.get_section(cache_name);
        system::create_cache(section);
        
        cache_name = string("cache") + to_string(++level);
    }

    // Create main memory.
    section_t& memory = config.get_section("memory");
    system::create_memory(memory);

    // Run traces.
    system::run(trace);

    // Finalize system.
    system::fin();
}
