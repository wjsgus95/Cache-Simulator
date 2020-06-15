#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <sstream>
#include <string>
#include <iostream>
#include <map>


class section_t {
public:
    section_t();
    section_t(const section_t& other);
    section_t(std::string m_name);

    ~section_t();

    std::string& operator [] (std::string& m_key);

    // Add a key-value pair.
    void set_setting(std::string m_key, std::string m_value);

    // Get value from key.
    template <typename T>
    bool get_setting(std::string m_key, T& m_container) {
        // Return false if key does not exist.
        if(!scalars.count(m_key)) { return false; }

        std::stringstream ss(scalars[m_key]);
        ss >> m_container;

        return true;
    }

    std::string name;
    std::map<std::string, std::string> scalars;

    // Token constants.
    static const std::string delimiter;
    static const std::string comment;
};


class config_t {
public:
    // Default config
    config_t();
    // Input config
    config_t(std::string m_filename);

    ~config_t();

    bool exists(std::string m_name);
    section_t& get_section(std::string m_name);

private:
    void parse(std::string& m_filename);

    std::string filename;
    std::map<std::string, section_t> sections;
};


#endif
