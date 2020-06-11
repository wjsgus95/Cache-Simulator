#include "memory.h"
#include "message.h"

memory_t::memory_t(section_t& m_config) {

}

memory_t::~memory_t() {
}

void memory_t::tick() {

}

void memory_t::recv(message_t* m_msg) {
    queue.push_back(m_msg);
}
