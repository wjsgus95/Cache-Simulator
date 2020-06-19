#include "memory.h"
#include "request.h"

memory_t::memory_t(section_t& m_config) {

}

memory_t::~memory_t() {
}

void memory_t::tick() {

}

void memory_t::recv(request_t* m_req) {
    if(m_req->type == LOAD) {
        load_queue.push_back(m_req);
    }
    else if(m_req->type == STORE) {
        store_queue.push_back(m_req);
    }
}

