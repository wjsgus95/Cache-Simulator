#include "trace.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

trace_t::trace_t(string m_filename) :
    // Create input filestream.
    filename(m_filename) {
    ifstream trace_file(m_filename);     
    if(!trace_file.is_open()) {
        cerr << "Error: Cannot open file " << m_filename << endl;
        abort();
    }

    // Parse each line of the trace file.
    string line;
    while(getline(trace_file, line)) {
        // Skip comments and empty lines.
        if(line[0] == '#' || line[0] == '\0') { continue; }
        else {
            // Split address and access type.
            istringstream ss(line);
            string address_str, access_type_str;
            ss >> address_str;
            ss >> access_type_str;

            // Erase all underscores in address.
            address_str.erase(remove(address_str.begin(), address_str.end(), '_'), address_str.end());

            // Convert address string to integer. Assume hexadecimal if the string starts with "0x".
            unsigned long address;
            if(address_str[0] == '0' && address_str[1] == 'x') {
                address = stol(address_str, nullptr, 0); 
            }
            else { address = stol(address_str, nullptr, 10); }

            // Convert access type string to enum.
            access_type_t access_type;
            if(access_type_str.compare("R") == 0)
                access_type = READ;
            else if(access_type_str.compare("W") == 0)
                access_type = WRITE;
            else {
                cerr << "Error: Unidentified memory access type in " << m_filename << endl;
                abort();
            }
            
            // Push unit trace object in queue.
            trace_line_t trace_line(address, access_type);
            traces.push(trace_line);

            dprintf("Address: %lu, Access Type: %s\n", address, access_type_str.data());
        }
    }
}

trace_t::~trace_t() {
}

bool trace_t::get_next_trace(unsigned long& m_address, access_type_t& m_type) {
    // Return false if queue is empty.
    if(traces.empty()) { return false; }

    // Assign front of queue to references.
    trace_line_t trace_line = traces.front();
    m_address = trace_line.address;
    m_type = trace_line.access_type;

    // Remove front and return true.
    traces.pop();
    return true;

}

#ifdef UNIT_TEST
int main() {
    trace_t trace = trace_t("../traces/base.trace");
    unsigned long address;
    access_type_t type;

    while(trace.get_next_trace(address, type)) {
        cout << address << " " << type << endl;
    }
    exit(0);
}
#endif
