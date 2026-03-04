
# ⚡ VoltCache

<p align="left"> <img src="https://img.shields.io/badge/status-Stable-brightgreen.svg" /> <img src="https://img.shields.io/github/license/arshc0der/VoltCache?color=green" /> <img src="https://img.shields.io/github/stars/arshc0der/VoltCache?style=social" /> <img src="https://img.shields.io/github/forks/arshc0der/VoltCache?style=social" /> <img src="https://img.shields.io/github/issues/arshc0der/VoltCache" /> <img src="https://img.shields.io/github/last-commit/arshc0der/VoltCache" /> <img src="https://img.shields.io/badge/language-C%2B%2B17-00599C?logo=c%2B%2B&logoColor=white" /> <img src="https://img.shields.io/badge/build-CMake-064F8C?logo=cmake&logoColor=white" /> <img src="https://img.shields.io/badge/platform-Windows%20%7C%20Linux-lightgrey" /> <img src="https://img.shields.io/badge/threading-std::shared__mutex-blue" /> <img src="https://img.shields.io/badge/persistence-Write--Ahead%20Logging-orange" /> <img src="https://img.shields.io/badge/testing-Python%20Integration%20Suite-yellow" /> <img src="https://img.shields.io/badge/dependencies-Zero-success" /> </p>

<p align="center">
  <img src="https://raw.githubusercontent.com/arshc0der/VoltCache/refs/heads/main/Testing/preview/logo.png" width="100%" alt="VoltCache"/>
</p>

> **Status:** High-performance in-memory engine with completed Durability (WAL) and Thread-Safe Concurrency layers.

VoltCache is a lightweight, multithreaded in-memory key-value store built with **C++17**. It is designed to handle low-latency data access while ensuring data integrity through a Write-Ahead Logging system. By utilizing modern C++ synchronization primitives, VoltCache supports high-throughput concurrent client connections.

---

### 🚀 Core Features (Implemented)

* **Thread-Safe Engine:** Implements a **Reader-Writer Lock pattern** using `std::shared_mutex`. This allows unlimited concurrent reads while ensuring exclusive access for writes, maximizing throughput.
* **Durability (Write-Ahead Logging):** Every `SET` operation is flushed to `data/volt.log` before memory update. On system restart, the engine automatically replays the log to restore the state.
* **Structured Data Support:** Advanced tokenization allows for storing complex strings and **JSON** objects (handling spaces and delimiters correctly).
* **Zero-Dependency Build:** Managed entirely via **CMake**, ensuring the project is portable and easy to compile in any C++ environment.

---

### 🛠️ Technical Deep-Dive

#### **Concurrency & RAII**

The system uses RAII (Resource Acquisition Is Initialization) to manage thread safety.

* **Writes:** Handled via `std::unique_lock` for exclusive access.
* **Reads:** Handled via `std::shared_lock` for concurrent access.

#### **Data Recovery**

The `load_from_wal()` sequence ensures that the database is fault-tolerant:

1. Check for existing `data/volt.log`.
2. Parse commands and tokens line-by-line.
3. Inject data into the hash map without re-logging, preventing log recursion.

---

### 📂 Project Structure

```text
VoltCache/
├── include/           # Header files (Engine declarations)
├── src/               # Core Implementation (Server & Engine logic)
├── Testing/           # Python-based Integration Test Suite
├── data/              # Persistent WAL storage (ignored by git)
├── CMakeLists.txt     # Cross-platform build configuration
└── .gitignore         # Configured to keep build/ and logs out of repo

```

---

### ⚙️ Installation & Build

**Prerequisites:**

* CMake 3.10+
* MinGW-w64 (UCRT64 recommended) or GCC

**Building:**

```bash
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .

```

**Running the Server:**

```bash
.\VoltCache.exe

```

**Running Tests:**

```bash
python Testing/test_volt.py

```

---

### 🗺️ Roadmap (Upcoming Features)

* [ ] **LRU Eviction Policy:** Implement `std::list` + `std::unordered_map` for O(1) eviction of least recently used keys when memory limits are reached.
* [ ] **Lock Striping:** Horizontal partitioning (sharding) of the database into 16 discrete buckets to reduce lock contention.
* [ ] **Google Test Integration:** Unit testing for core engine components to ensure 100% logic coverage.

---

### 🏆 Why this project?

This project demonstrates proficiency in **System Design**, **Modern C++ synchronization**, and **File I/O performance**. It is built to simulate real-world constraints found in systems like Redis and Memcached.

---