
---

# ⚡ VoltCache

### High-Performance In-Memory Key-Value Engine (C++17)
<p align="center"> <img src="https://raw.githubusercontent.com/arshc0der/VoltCache/refs/heads/main/Testing/preview/logo.png" width="100%" alt="VoltCache"/> </p>
<p align="left">
  <img src="https://img.shields.io/badge/status-Stable-brightgreen.svg" />
  <img src="https://img.shields.io/github/license/arshc0der/VoltCache?color=green" />
  <img src="https://img.shields.io/github/stars/arshc0der/VoltCache?style=social" />
  <img src="https://img.shields.io/github/forks/arshc0der/VoltCache?style=social" />
  <img src="https://img.shields.io/github/issues/arshc0der/VoltCache" />
  <img src="https://img.shields.io/github/last-commit/arshc0der/VoltCache" />
  <img src="https://img.shields.io/badge/language-C%2B%2B17-00599C?logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/build-CMake-064F8C?logo=cmake&logoColor=white" />
  <img src="https://img.shields.io/badge/architecture-Multithreaded-critical" />
  <img src="https://img.shields.io/badge/concurrency-Reader--Writer%20Lock-blueviolet" />
  <img src="https://img.shields.io/badge/persistence-Write--Ahead%20Logging-orange" />
  <img src="https://img.shields.io/badge/dependencies-Zero-success" />
</p>

---

## 🚀 Overview

**VoltCache** is a lightweight, high-performance, multithreaded in-memory key-value store built in **C++17**.

It is engineered to deliver:

* ⚡ Ultra-low latency reads
* 🔒 Thread-safe concurrent access
* 💾 Durable persistence via Write-Ahead Logging (WAL)
* 🧵 Modern C++ synchronization using RAII

Designed to simulate production-grade caching systems like Redis — but implemented from scratch to demonstrate deep systems-level understanding.

---

## ✨ Key Features

### 🧵 Thread-Safe Concurrency

* Implements **Reader-Writer Lock pattern**
* Uses `std::shared_mutex`
* Unlimited concurrent reads
* Exclusive writes via `std::unique_lock`
* RAII-based lock safety

### 💾 Durability with Write-Ahead Logging

* Every `SET` operation is logged before memory mutation
* Log file: `data/volt.log`
* Crash recovery via automatic WAL replay
* Prevents recursive re-logging during restore

### 📦 Structured Data Support

* Advanced token parsing
* Stores:

  * Strings with spaces
  * Delimiter-safe values
  * JSON payloads

### ⚙️ Zero Dependency Build

* Fully managed via **CMake**
* No external libraries
* Portable across Windows & Linux

---

## 🏗 Architecture

```
Client Threads
      │
      ▼
┌───────────────────────┐
│  Shared Hash Map      │
│  (std::unordered_map) │
└───────────────────────┘
      ▲
      │
 Reader-Writer Lock
      │
      ▼
 Write-Ahead Log (WAL)
```

### Concurrency Model

| Operation | Lock Type   | Behavior    |
| --------- | ----------- | ----------- |
| GET       | shared_lock | Concurrent  |
| SET       | unique_lock | Exclusive   |
| WAL Flush | File I/O    | Synchronous |

---

## 🔄 Crash Recovery Flow

1. Detect `data/volt.log`
2. Parse commands line-by-line
3. Inject data directly into memory
4. Skip logging during recovery phase
5. Restore complete state

---

## 📂 Project Structure

```text
VoltCache/
├── include/           # Engine declarations
├── src/               # Server & engine implementation
├── Testing/           # Python integration tests
├── data/              # WAL persistence layer
├── CMakeLists.txt
└── README.md
```

---

## ⚙️ Installation

### 🔧 Requirements

* CMake 3.10+
* GCC / MinGW-w64 (UCRT64 recommended)
* Python 3 (for integration tests)

### 🏗 Build

```bash
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

### ▶ Run Server

```bash
./VoltCache
```

### 🧪 Run Integration Tests

```bash
python Testing/test_volt.py
```

---

## 📈 Performance Goals

* O(1) average lookup (hash map)
* Minimal lock contention
* WAL durability with low overhead
* Safe concurrent client simulation

---

## 🗺 Roadmap

* [ ] LRU Eviction Policy (O(1) eviction via list + hashmap)
* [ ] Lock Striping (16 bucket sharding)
* [ ] GoogleTest unit coverage
* [ ] Benchmark suite (throughput + latency metrics)
* [ ] Optional async WAL mode
* [ ] Snapshotting mechanism

---

## 🧠 Design Philosophy

VoltCache is built to demonstrate:

* Advanced C++17 mastery
* RAII-driven concurrency safety
* File I/O durability guarantees
* Real-world system design principles

This is not just a CRUD store — it’s a **mini database engine**.

---

## 🏆 Why VoltCache Stands Out

✔ Fully thread-safe architecture

✔ Persistent durability layer

✔ Clean modular structure

✔ Zero third-party dependencies

Built as a foundational stepping stone toward distributed caching and database engines.

---

## 🤝 Contributing

Contributions are welcome.
If you'd like to improve performance, add benchmarking, or implement eviction strategies — open a PR.

---
