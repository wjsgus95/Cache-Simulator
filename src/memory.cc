#include "memory.h"
#include "request.h"

memory_t::memory_t(section_t& m_config) {

}

memory_t::~memory_t() {
}

void memory_t::tick() {

}

void memory_t::recv(request_t* m_req) {
    lsq.push_back(m_req);
}

