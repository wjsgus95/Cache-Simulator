#include "component.h"
#include "link.h"

#include <iostream>

component_t::component_t() :
    lsq_size(LSQ_SIZE) {
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
    return lsq.size();
}

bool component_t::is_available() {
    return lsq.size() < lsq_size;
}

