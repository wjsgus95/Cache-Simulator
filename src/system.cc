#include "system.h"
#include "trace.h"
#include "cache.h"
#include "memory.h"

using namespace std;

vector<component_t*> system::hiearchy;
unsigned system::word_size;
unsigned system::block_size;
bool system::write_back;

void system::init(section_t& m_section) {
    m_section.get_setting("word_size", word_size);
    m_section.get_setting("block_size", block_size);
    m_section.get_setting("write_back", write_back);
}

void system::run(trace_t& m_trace) {
}

void system::fin() {
    for(unsigned i = 0; i < hiearchy.size(); i++)
        delete hiearchy[i];
}

unsigned system::levels() {
    return hiearchy.size();
}

unsigned system::create_cache(section_t& m_section) {
    // Create cache.
    cache_t* cache = new cache_t(m_section);
    hiearchy.push_back(cache);

    // Set outlink from previous level cache to current one.
    int level = hiearchy.size() - 1;
    if(level > 0) {
        component_t* prev_cache = hiearchy[level-1];
        prev_cache->set_outlink(cache);
    }

    return level;
}

unsigned system::create_memory(section_t& m_section) {
    // Create memory.
    memory_t* memory = new memory_t(m_section);
    hiearchy.push_back(memory);

    // Set outlink from LLC to main memory.
    int level = hiearchy.size() - 1;
    component_t* llc = hiearchy[level-1];
    llc->set_outlink(memory);

    return level;
}
