#ifndef __CACHE_H__
#define __CACHE_H__

#include <vector>

#include "config.h"
#include "component.h"


class cache_t : public component_t {
public:
    cache_t(section_t& m_config);
    ~cache_t();

    /*
    // Create cache instance with given configuration.
    static cache_t* create(config_t& m_config);
    */

    void tick();

    // Request reception callback.
    void recv(message_t* m_msg);

private:
    std::vector<message_t*> queue;
};

#endif
