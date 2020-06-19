#include "cache.h"
#include "request.h"

using namespace std;

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
    /* TODO */
    //request_t* req = policy->get_next(lsq);

    if(lsq.size()) {
        request_t* req = *lsq.begin();
        debug_printf("%lu %d\n", req->address, req->type);
        delete req;

        lsq.erase(lsq.begin());
    }
}

void cache_t::recv(request_t* m_req) {
    lsq.push_back(m_req);
}

