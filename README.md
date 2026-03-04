# ⚡ VoltCache

> **🚧 Active Development:** Building a high-performance in-memory caching engine from the ground up.

VoltCache is a lightweight, multithreaded in-memory key-value store built entirely in C++. Inspired by the core architecture of distributed caches like Redis, this project is designed to handle extremely low-latency data access by bypassing disk I/O bottlenecks. 

By managing raw POSIX sockets and implementing custom thread pools, VoltCache ensures high-throughput concurrent client connections. The architecture is intentionally kept minimal and zero-dependency, making it highly optimized for containerized deployments and rigorous performance profiling—including measuring throughput, latency, and hardware-level energy consumption under heavy concurrent loads.

### 1. Durability: Write-Ahead Logging (WAL)

In-memory data is lost if the power goes out. A real database writes every command to a simple text file (a "log") *before* updating memory.

* **The Task:** Create a `volt.log` file. Every time a `SET` command comes in, append it to the file before updating the `unordered_map`.
* **The Wow Factor:** Show the recruiter that if you stop and restart the server, it reads the log file and "replays" the commands to restore the data.

### 2. Efficiency: LRU Eviction Policy

RAM is expensive. If your cache gets too full, the server will crash. You need an **Eviction Policy** to delete old data automatically.

* **The Task:** Implement a **Least Recently Used (LRU)** cache.
* **The Wow Factor:** Use a combination of a `std::list` (to track order) and a `std::unordered_map` (for fast lookup). This is a classic "Senior Engineer" interview question.

### 3. Scalability: Lock Striping (Sharding)

A single `shared_mutex` for the whole database is a "bottleneck." If 1,000 threads try to access different keys, they still have to wait for that one lock.

* **The Task:** Instead of one map, create an array of 16 maps (buckets). Use a hash of the key to decide which bucket to use.
* **The Wow Factor:** This is called **Lock Striping**. It allows multiple threads to write to the database at the exact same time as long as they are hitting different buckets.

### 4. Professionalism: Testing & CI/CD

MNCs don't trust code that isn't tested.

* **The Task:** Integrate **Google Test (GTest)**. Write tests that simulate 100 clients hitting the server at once.
* **The Wow Factor:** Add a `.github/workflows/main.yml` file so that every time you push code, GitHub automatically compiles and runs your tests.

### Summary Checklist for your Resume:

| Feature | What it proves to an MNC |
| --- | --- |
| **RAII & Smart Pointers** | You don't have memory leaks. |
| **Write-Ahead Log** | You understand data integrity and durability. |
| **LRU Eviction** | You know how to manage limited hardware resources. |
| **CMake Build System** | You can manage professional, cross-platform C++ projects. |
| **Lock Striping** | You can architect for high-concurrency performance. |

By adding even just **one** of these (like the WAL or LRU), you move your project from "beginner" to "advanced."

Which of these sounds most interesting to you to try building first: making the data "survive" a restart (WAL), or making it "auto-delete" old data (LRU)?


folder strcture
VoltCache/
├── CMakeLists.txt             # The "Boss" file (Build System)
├── include/                   # Public API / Header files
│   └── VoltCache.h            # Engine declarations
├── src/                       # Implementation files
│   ├── main.cpp               # Server entry point & Socket logic
│   └── VoltCache.cpp          # Engine logic (SET/GET/WAL)
├── build/                     # Compiled binaries (Created by you)
├── data/                      # Persistent storage (WAL logs)
└── README.md                  # Project documentation



# 1. Enter the build folder (if you aren't already there)
cd build

# 2. Configure (This generates the "MinGW Makefiles")
cmake -G "MinGW Makefiles" ..

# 3. Build (This actually runs the compiler)
cmake --build .