#include "component.h"
#include "link.h"

component_t::component_t() {
    outlink = new link_t(this);
}

component_t::~component_t() {
    delete outlink;
}

void component_t::send(message_t* m_msg) {
    outlink->send(m_msg);
}

void component_t::set_outlink(component_t* other) {
    outlink->set_destination(other);
}
