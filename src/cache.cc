#include "cache.h"
#include "message.h"

cache_line_t::cache_line_t(unsigned m_associativity) : 
    associativity(m_associativity) {
}

cache_line_t::~cache_line_t() {
}


cache_t::cache_t(section_t& m_section) {
    unsigned num_blocks;
    m_section.get_setting("blocks", num_blocks);
    m_section.get_setting("latency", latency);
    m_section.get_setting("associativity", associativity);

    for(unsigned i = 0; i < num_blocks; i++) {
        cache_line_t* cache_line = new cache_line_t(associativity);
        cache_lines.push_back(cache_line);
    }
}

cache_t::~cache_t() {
    for(unsigned i = 0; i < cache_lines.size(); i++) {
        delete cache_lines[i];
    }
}

void cache_t::tick() {

}

void cache_t::recv(message_t* m_msg) {
    queue.push_back(m_msg);
}
