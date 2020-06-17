
/*** debug printf ***/
#ifdef DEBUG
#define dprintf(format, args...) \
        fprintf(stderr, "[%s:%d:%s]:" format, \
                __FILE__, __LINE__, __func__, ##args)
#else
#define dprintf(fmt, args...)
#endif

enum access_type_t {
    READ = 0,
    WRITE,
};
