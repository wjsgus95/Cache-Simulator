#ifndef __DEFS_H__
#define __DEFS_H__

/*** debug printf ***/
#ifdef DEBUG
#define debug_printf(fmt, args...) \
        fprintf(stderr, "[%s:%d:%s]: " fmt, \
                __FILE__, __LINE__, __func__, ##args)
#else
#define debug_printf(fmt, args...)
#endif

#define LSQ_SIZE 32

enum access_type_t {
    LOAD= 0,
    STORE,
};

#endif
