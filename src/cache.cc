#include "cache.h"
#include "request.h"

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
    if(load_queue.size()) {
        request_t* req = *load_queue.begin();
        debug_printf("%lu %d\n", req->address, req->type);
        delete req;
        
        load_queue.erase(load_queue.begin());
    }
    else if(store_queue.size()) {
        request_t* req = *store_queue.begin();
        debug_printf("%lu %d\n", req->address, req->type);
        delete req;

        store_queue.erase(store_queue.begin());
    }
}

void cache_t::recv(request_t* m_req) {
    if(m_req->type == LOAD) {
        load_queue.push_back(m_req);
    }
    else if(m_req->type == STORE) {
        store_queue.push_back(m_req);
    }
}

