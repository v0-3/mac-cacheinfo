<br>

<p align="center">
  <a href="https://github.com/v0-3">
    <img width="200" src="logo/cache.png" alt="cache logo">
  </a>
</p>

<br>

# mac-cacheinfo

**mac-cacheinfo** is a lightweight C++ utility for retrieving CPU cache information (L1i, L1d, L2, etc.) on Apple Silicon–based macOS systems.  
It provides a simple command-line interface that queries system-level parameters using macOS APIs.

If you have questions or would like to discuss the project, feel free to contact me here or on **Discord: `v0.3`**.

---

## Features

- Retrieves cache line size  
- Reports L1 instruction cache size  
- Reports L1 data cache size  
- Reports L2 cache size  
- Supports Apple Silicon processors (e.g., M1, M2, M3 families)

---

## Build & Run

```bash
git clone https://github.com/3SUM/mac-cacheinfo.git
cd mac-cacheinfo/src
make
./cache

Apple M3 Pro CPU Info
====================================
        Cache Line Size:      128  B
        L1i  Cache Size:  131.072 KB
        L1d  Cache Size:   65.536 KB
        L2   Cache Size: 4194.304 KB
```

---

## License

© Luis Maya Aranda￼. All rights reserved.
Licensed under the MIT License.
