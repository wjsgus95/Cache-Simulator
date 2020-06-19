#ifndef __REQUEST_H__
#define __REQUEST_H__

#include "defs.h"

class request_t {
public:
    request_t(unsigned long m_address, access_type_t m_type) :
        address(m_address),
        type(m_type) { }

    unsigned long address;
    access_type_t type;
private:
};


#endif
