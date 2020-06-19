#include "component.h"
#include "link.h"

#include <iostream>

component_t::component_t() :
    lq_size(LQ_SIZE),
    sq_size(SQ_SIZE) {
    outlink = new link_t(this);
}

component_t::~component_t() {
    delete outlink;
}

void component_t::send(request_t* m_req) {
    outlink->send(m_req);
}

void component_t::set_outlink(component_t* other) {
    outlink->set_destination(other);
}

unsigned component_t::pending_requests() {
    return load_queue.size() + store_queue.size();
}

bool component_t::is_available(access_type_t m_type) {
    if(m_type == LOAD) {
        return load_queue.size() < lq_size;
    }
    else if(m_type == STORE) {
        return store_queue.size() < sq_size;
    }

    abort();
}

