<br>

<p align="center">
  <a href="https://github.com/v0-3">
    <img width="200" src="logo/cache.png" alt="cache logo">
  </a>
</p>

<br>

# mac-cacheinfo

A lightweight C++23 utility for macOS that retrieves detailed CPU and cache information using the BSD `sysctl` interface.
Designed for minimal overhead, clean output, and modern C++ coding practices.

---

## Features

- Retrieves CPU brand string
- Reads hardware cache sizes (L1i, L1d, L2)
- Obtains cache line size
- Uses safe, modern C++23 techniques (`std::optional`, `std::print`, RAII, strong typing)
- Clear, human-readable terminal output

---

## Supported Platforms

- macOS (Apple Silicon)
  Uses `sysctlbyname`, available only on BSD/macOS systems.

---

## Build & Run

### Requirements
- **macOS**
- **Clang 16+** or **Apple Clang (Xcode 15+)**

### Build with Make

```bash
git clone https://github.com/v0-3/mac-cacheinfo.git
cd mac-cacheinfo/src
make
./cache
```


### Example Output

```
Apple M3 Pro CPU Info
====================================
    Cache Line Size:       128  B
    L1i  Cache Size:        64 KiB
    L1d  Cache Size:        64 KiB
    L2   Cache Size:       4096 KiB
```

---

## License

© [Luis Maya Aranda](https://github.com/v0-3). All rights reserved.  
Licensed under the **MIT License**.
