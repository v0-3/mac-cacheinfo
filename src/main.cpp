#include <sys/sysctl.h>

#include <cstdlib>
#include <optional>
#include <print>
#include <stdexcept>
#include <string>
#include <string_view>

using std::size_t;

[[nodiscard]] std::string get_cpu_type() {
    // First call: query required buffer size
    size_t size{};
    if (sysctlbyname("machdep.cpu.brand_string", nullptr, &size, nullptr, 0) != 0 || size == 0) {
        throw std::runtime_error("Unable to retrieve CPU type (size query failed)");
    }

    // Second call: actually retrieve the string
    std::string buffer(size, '\0');
    if (sysctlbyname("machdep.cpu.brand_string", buffer.data(), &size, nullptr, 0) != 0) {
        throw std::runtime_error("Unable to retrieve CPU type (value query failed)");
    }

    // sysctl typically returns a null-terminated string; trim trailing '\0' if present
    if (!buffer.empty() && buffer.back() == '\0') {
        buffer.pop_back();
    }

    return buffer;
}

template <typename T>
[[nodiscard]] std::optional<T> get_sysctl_value(std::string_view name) {
    static_assert(std::is_trivially_copyable_v<T>,
                  "get_sysctl_value requires a trivially copyable type");

    T value{};
    size_t size = sizeof(T);

    if (sysctlbyname(name.data(), &value, &size, nullptr, 0) != 0 || size != sizeof(T)) {
        return std::nullopt;
    }

    return value;
}

template <typename T>
[[nodiscard]] T get_required_sysctl(std::string_view name, std::string_view error_message) {
    if (auto value = get_sysctl_value<T>(name)) {
        return *value;
    }

    throw std::runtime_error(std::string{error_message});
}

[[nodiscard]] size_t get_cache_line_size() {
    return get_required_sysctl<size_t>("hw.cachelinesize",
                                       "Unable to retrieve cache line size");
}

[[nodiscard]] size_t get_l1i_cache_size() {
    return get_required_sysctl<size_t>("hw.l1icachesize",
                                       "Unable to retrieve L1i cache size");
}

[[nodiscard]] size_t get_l1d_cache_size() {
    return get_required_sysctl<size_t>("hw.l1dcachesize",
                                       "Unable to retrieve L1d cache size");
}

[[nodiscard]] size_t get_l2_cache_size() {
    return get_required_sysctl<size_t>("hw.l2cachesize",
                                       "Unable to retrieve L2 cache size");
}

int main(int argc, char* argv[]) {
    if (argc != 1) {
        std::println("Usage:\n\t./cache");
        return EXIT_FAILURE;
    }

    try {
        const auto cpu_type        = get_cpu_type();
        const auto cache_line_size = get_cache_line_size();
        const auto l1i_size_bytes  = get_l1i_cache_size();
        const auto l1d_size_bytes  = get_l1d_cache_size();
        const auto l2_size_bytes   = get_l2_cache_size();

        constexpr double bytes_per_kibibyte = 1024.0;

        std::println("{} CPU Info\n{:=>36}", cpu_type, '=');
        std::println("\tCache Line Size: {:>8}  B", cache_line_size);
        std::println("\tL1i  Cache Size: {:>8.0f} KiB",
                     l1i_size_bytes / bytes_per_kibibyte);
        std::println("\tL1d  Cache Size: {:>8.0f} KiB",
                     l1d_size_bytes / bytes_per_kibibyte);
        std::println("\tL2   Cache Size: {:>8.0f} KiB",
                     l2_size_bytes / bytes_per_kibibyte);
    } catch (const std::exception& e) {
        std::println("[ERROR] {}", e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
