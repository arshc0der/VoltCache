#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class voltcache
{
private:
    // This actaul "in-memory database"
    unordered_map<std::string, std::string> store;

public:
    // SET : Stores a key-value pair
    void set(const string &key, const string &value)
    {
        store[key] = value;
        cout << "ok\n";
    }

    // GET: Retrives a value its key
    string get(const string &key)
    {
        if (store.find(key) != store.end())
        {
            return store[key];
        }
        return "(nil)";
    }
};
int main()
{
    voltcache db;

    cout << "Starting VoltCache (Local Engine Test)\n";
    cout << "--------------------------------------\n";

    // Simulating storing some data
    db.set("user:101", "Arsh");
    db.set("role", "Developer");

    // Retrieving the data
    cout << "Value for user:101 -> " << db.get("user:101") << "\n";
    cout << "Value for invalid_user -> " << db.get("user:999") << "\n";
    return 0;
}