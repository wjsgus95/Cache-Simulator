#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <vector>

#include "config.h"

// Forward declaration
class trace_t;
class component_t;

// Global system settings
class system {
public:
    // Initialize system.
    static void init(section_t& m_section);
    // Run traces.
    static void run(trace_t& m_trace);
    // Finalize system.
    static void fin();

    // Return the depth of memory system.
    static unsigned levels();

    // Create cache given config and return it's depth. Depth increments as you create more memory models.
    static unsigned create_cache(section_t& m_section);
    // Create memory given config and return it's depth. Depth increments as you create more memory models.
    static unsigned create_memory(section_t& m_section);

private:
    static std::vector<component_t*> hiearchy;

    static unsigned word_size;
    static unsigned block_size;
    static bool write_back;
};

#endif
