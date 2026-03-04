#include "VoltCache.h"
#include <iostream>
#include <sstream>
#include <mutex>       
#include <filesystem>  

namespace fs = std::filesystem;

VoltCache::VoltCache() {
    if (!fs::exists("data")) {
        fs::create_directory("data");
    }

    wal_file.open("data/volt.log", std::ios::app);
    if (!wal_file.is_open()) {
        std::cerr << "Critical Error: Could not open WAL file!" << std::endl;
    }
    load_from_wal();
}

VoltCache::~VoltCache() {
    if (wal_file.is_open()) {
        wal_file.close();
    }
}

void VoltCache::set(const std::string& key, const std::string& value, bool log) {
    std::unique_lock<std::shared_mutex> lock(rw_lock); 
    store[key] = value;
    
    if (log && wal_file.is_open()) {
        wal_file << "SET " << key << " " << value << std::endl;
        wal_file.flush(); 
    }
}

std::string VoltCache::get(const std::string& key) {
    std::shared_lock<std::shared_mutex> lock(rw_lock); 
    auto it = store.find(key);
    return (it != store.end()) ? it->second : "(nil)";
}

void VoltCache::load_from_wal() {
    std::ifstream log("data/volt.log");
    if (!log.is_open()) return;

    std::string line;
    while (std::getline(log, line)) {
        if (line.empty()) continue;
        auto tokens = tokenize(line);
        if (tokens.size() >= 3 && tokens[0] == "SET") {
            // Internal set: false ensures we don't duplicate logs during recovery
            set(tokens[1], tokens[2], false); 
        }
    }
}

// BUG FIXED: Now handles values with spaces (like JSON or sentences)
std::vector<std::string> VoltCache::tokenize(const std::string& str) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string cmd, key, value;

    // 1. Get the Command (SET/GET)
    if (!(ss >> cmd)) return tokens;
    tokens.push_back(cmd);

    // 2. Get the Key
    if (!(ss >> key)) return tokens;
    tokens.push_back(key);

    // 3. Get the REST of the string as the Value
    // This allows "SET user {'id': 1}" to work instead of cutting off at the space
    std::getline(ss >> std::ws, value); 
    if (!value.empty()) {
        tokens.push_back(value);
    }
    return tokens;
}