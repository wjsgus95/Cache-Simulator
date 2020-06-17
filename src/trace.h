#ifndef __TRACE_H__
#define __TRACE_H__

#include <string>
#include <queue>

#include "defs.h"

class trace_t {
public:
    trace_t(std::string m_filename);
    ~trace_t();

    bool get_next_trace(unsigned long& m_address, access_type_t& m_type);

private:
    struct trace_line_t {
        trace_line_t(unsigned long m_address, access_type_t m_type):
            address(m_address),
            access_type(m_type) { }

        unsigned long address;
        access_type_t access_type;
    };

    std::string filename;
    std::queue<trace_line_t> traces;
};

#endif
