#ifndef VOLTCACHE_H
#define VOLTCACHE_H

#include <string>
#include <unordered_map>
#include <shared_mutex>
#include <fstream>
#include <vector>

class VoltCache {
private:
    std::unordered_map<std::string, std::string> store;
    mutable std::shared_mutex rw_lock;
    std::ofstream wal_file; // Write-Ahead Log

public:
    VoltCache();
    ~VoltCache();
    
    // Core Engine commands
    void set(const std::string& key, const std::string& value, bool log = true);
    std::string get(const std::string& key);
    
    // Persistence
    void load_from_wal();
    std::vector<std::string> tokenize(const std::string& str);
};

#endif