#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <vector>

#include "config.h"
#include "component.h"


class memory_t : public component_t {
public:
    memory_t(section_t& m_config);
    ~memory_t();

    void tick();
    // Reqeust reception callback.
    void recv(request_t* m_req);
    
private:
};

#endif
