#include "config.h"

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <fstream>
#include <iostream>

using namespace std;

const string section_t::delimiter = ":";
const string section_t::comment = "#";

// Trim from start. (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// Trim from end. (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// Trim from both ends. (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}


section_t::section_t() {
}

section_t::section_t(const section_t& other) {
    name = other.name;
    scalars = other.scalars;
}

section_t::section_t(string m_name) : name(m_name) {
     
}

section_t::~section_t() {
}

string& section_t::operator [] (string& m_key) {
    return scalars[m_key];
}

void section_t::set_setting(string m_key, string m_value) {
    scalars[m_key] = m_value;
}


// Default config.
config_t::config_t() {
    section_t& general = sections["general"] = section_t("general");
    general.set_setting("word_size", "4");
    general.set_setting("block_size", "16");
    general.set_setting("write_back", "true");

    section_t& cache1 = sections["cache1"] = section_t("cache1");
    cache1.set_setting("blocks", "16");
    cache1.set_setting("associativity", "1");
    cache1.set_setting("hit_time", "1");

    section_t& memory = sections["memory"] = section_t("memory");
    memory.set_setting("hit_time", "1000");
}

// Parse input config.
config_t::config_t(string m_filename) {
    parse(m_filename);
}

config_t::~config_t() {
}

bool config_t::exists(string m_name) {
    return sections.count(m_name);
}

section_t& config_t::get_section(string m_name) {
    // Assert section with given name exists.
    if(!sections.count(m_name)) {
        cerr << "Error: Given section name " << m_name
             << " does not exist." << endl;
        abort();
    }

    return sections[m_name];
}


void config_t::parse(string& m_filename) {
    ifstream config_file(m_filename); 
    if(!config_file.is_open()) {
        cerr << "Error: Cannot open file " << m_filename << endl;
        abort();
    }

    string line;
    while(getline(config_file, line)) {
        // Skip comments and new lines.
        if(line[0] == '#' || line[0] == '\0') { continue; }
        else {
            string name = line.substr(0, line.find(section_t::delimiter));
            sections[name] = section_t(name);
            section_t& section = sections[name];

            while(getline(config_file, line)) {
                if(line[0] != ' ' && line[0] != '\t') {
                    break;
                }

                const size_t count = line.find(section_t::comment) - line.find(section_t::delimiter) - 1;

                // Split key and value by delimiter.
                string key, value;
                key = line.substr(0, line.find(section_t::delimiter));
                value = line.substr(line.find(section_t::delimiter)+1, count);

                // Trim whitespace.
                trim(key);
                trim(value);

                section.set_setting(key, value);
            }
        }
    }
}

#ifdef UNIT_TEST
int main() {
    config_t config("../configs/base.yaml");
    
    section_t& section = config.get_section("general");
    int word_size;
    section.get_setting("word_size", word_size);
    cout << word_size << endl;
}
#endif
