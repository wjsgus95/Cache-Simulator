#ifndef __TRACE_H__
#define __TRACE_H__

#include <string>

class trace_t {
public:
    trace_t(std::string m_filename);
    ~trace_t();

private:
    std::string filename;
};

#endif
