#ifndef __COMPONENT_H__
#define __COMPONENT_H__

class link_t;
class message_t;

class component_t {
public:
    component_t();
    virtual ~component_t();

    // Progress time step.
    virtual void tick() = 0;

    // Set link to other component.
    void set_outlink(component_t* other);

    // Send message through outlink.
    void send(message_t* m_msg);

    // Data reception callback.
    virtual void recv(message_t* m_msg) = 0;

protected:
    unsigned level;
    link_t* outlink;
};

#endif
