#include "cache.h"
#include "message.h"

cache_t::cache_t(section_t& m_config) {

}

cache_t::~cache_t() {
}

/*
cache_t* cache_t::create(config_t& m_config) {

}
*/

void cache_t::tick() {

}

void cache_t::recv(message_t* m_msg) {
    queue.push_back(m_msg);
}
