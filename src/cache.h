#ifndef __CACHE_H__
#define __CACHE_H__

#include <vector>

#include "config.h"
#include "component.h"

class cache_line_t {
public:
    cache_line_t(unsigned m_associativity);
    ~cache_line_t();

private:
    unsigned associativity;
};


class cache_t : public component_t {
public:
    cache_t(section_t& m_config);
    ~cache_t();

    void tick();
    // Request reception callback.
    void recv(request_t* m_req);

private:
    std::vector<cache_line_t*> cache_lines;

    unsigned associativity;
    unsigned latency;
};

#endif
