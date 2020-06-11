#ifndef __LINK_H__
#define __LINK_H__

#include <iostream>

#include "component.h"

// Unidirectional link
class link_t {
public:
    link_t(component_t* m_source) :
        source(m_source),
        destination(0) {
    }
    ~link_t() {}

    // Set link's destination.
    void set_destination(component_t* m_destination) {
        destination = m_destination;
    }

    template <typename T>
    void send(T m_data) {
        if(!destination) {
            std::cerr << "Error: Link destination is not set." << std::endl;
            abort();
        }

        destination->recv(m_data);
    }

private:
    component_t* source;
    component_t* destination;
};

#endif
