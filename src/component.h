#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <vector>

#include "defs.h"

class link_t;
class request_t;

class component_t {
public:
    component_t();
    virtual ~component_t();

    // Progress time step.
    virtual void tick() = 0;

    // Set link to other component.
    void set_outlink(component_t* other);

    // Send request through outlink.
    void send(request_t* m_req);
    // Data reception callback.
    virtual void recv(request_t* m_req) = 0;

    // Check if component is available to queue given type of request.
    bool is_available(access_type_t m_type);

    // Get number of pending requests.
    unsigned pending_requests();

protected:
    unsigned level;
    link_t* outlink;

    size_t lq_size;
    size_t sq_size;

    std::vector<request_t*> load_queue;
    std::vector<request_t*> store_queue;
};

#endif
