#include "system.h"

#include <algorithm> 

#include "trace.h"
#include "cache.h"
#include "memory.h"
#include "request.h"

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
    bool stall = false, end = false;
    unsigned long address;
    access_type_t type;

    while(!end || pending_requests()) {
        if(!end && !stall) {
            end = !m_trace.get_next_trace(address, type);
            debug_printf("New trace %lu %d\n", address, type);
        }

        if(!end) {
            stall = !hiearchy[0]->is_available(type);
            if(!stall) {
                request_t* req = new request_t(address, type);        
                hiearchy[0]->recv(req);
            }
        }

        for(int i = hiearchy.size() - 1; i >= 0; i--) {
            hiearchy[i]->tick();
        }
    }
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

unsigned system::pending_requests() {
    unsigned result = 0;
    std::for_each(hiearchy.begin(), hiearchy.end(), [&] (component_t* m_component) {
        result += m_component->pending_requests();
    });

    return result;
}
