#ifndef __CACHE_H__
#define __CACHE_H__

#include "config.h"
#include "trace.h"

class cache_t {
public:
    cache_t(config_t& m_config);
    virtual ~cache_t();

    // Create cache instance with given configuration.
    static cache_t* create(config_t& m_config);
    // Run traces.
    virtual void run(trace_t& m_trace) = 0;

private:

};

#endif
