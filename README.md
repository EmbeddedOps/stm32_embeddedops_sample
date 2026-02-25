# STM32 EmbeddedOps Sample

[![CI](https://github.com/EmbeddedOps/stm32_embeddedops_sample/actions/workflows/ci.yml/badge.svg)](https://github.com/EmbeddedOps/stm32_embeddedops_sample/actions/workflows/ci.yml)

A professional, open-source CI/CD template for STM32 firmware built with **GitHub Actions**, **CMake**, **Ceedling**, and **Docker**.

**Target:** STM32F446RE (Nucleo-F446RE, Cortex-M4F)
**Sample app:** Temperature sensor logger — reads the on-chip ADC temperature sensor and outputs readings over UART.


---

## Project Structure

```
├── .github/workflows/ci.yml    # GitHub Actions CI/CD pipeline
├── cmake/
│   ├── arm-none-eabi-gcc.cmake # ARM cross-compilation toolchain file
│   └── stm32hal.cmake          # HAL/CMSIS static library CMake module
├── Core/                       # Hardware-dependent init (not unit-tested)
│   ├── Inc/                    # main.h, HAL config, interrupt prototypes
│   └── Src/                    # main.c, clock config, interrupts, syscalls
├── App/                        # Application logic (unit-tested with mocks)
│   ├── Inc/                    # app_temp_sensor.h, app_logger.h, app_led.h
│   └── Src/                    # Testable modules with HAL abstraction
├── Startup/                    # Startup assembly + linker script
├── Drivers/                    # Git submodules (ST HAL/CMSIS)
├── test/                       # Ceedling unit tests
│   ├── test_app_temp_sensor.c
│   ├── test_app_logger.c
│   ├── test_app_led.c
│   └── support/hal_stubs.h    # Minimal HAL types for host compilation
├── project.yml                 # Ceedling configuration
├── CMakeLists.txt              # Root CMake build
├── CMakePresets.json           # Debug/Release presets
├── Dockerfile                  # Reproducible build environment
└── docker-compose.yml          # One-command build/test/shell
```

**Key design decision:** `Core/` holds hardware init code that runs on the target. `App/` holds application logic that calls HAL functions through mockable interfaces — these are unit-tested on the host with Ceedling/CMock, no hardware required.

---

## Quick Start (Docker)

Build the firmware:
```bash
docker compose run build
```

Run unit tests:
```bash
docker compose run test
```

Interactive shell:
```bash
docker compose run shell
```

---

## Local Development

### Prerequisites

- **ARM GCC:** `arm-none-eabi-gcc` (10+ recommended)
- **CMake:** 3.22+
- **Ninja:** build system
- **Ruby:** 2.7+ with `gem install ceedling`

### Build

```bash
# Using CMake presets
cmake --preset release
cmake --build --preset release

# Or manually
cmake -B build -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi-gcc.cmake \
  -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Output files in `build/`:
- `stm32_temp_logger.elf` — Debug/flash image
- `stm32_temp_logger.hex` — Intel HEX
- `stm32_temp_logger.bin` — Raw binary
- `stm32_temp_logger.map` — Linker map

### Test

```bash
ceedling test:all
```

### Flash (ST-Link)

```bash
# Using OpenOCD
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
  -c "program build/stm32_temp_logger.elf verify reset exit"

# Or using STM32CubeProgrammer
STM32_Programmer_CLI -c port=SWD -w build/stm32_temp_logger.bin 0x08000000 -v -rst
```

---

## CI/CD Pipeline Explained

| Job | Trigger | What it does |
|---|---|---|
| **docker** | Every push & PR | Builds the Docker image and pushes to `ghcr.io/embeddedops/stm32_embeddedops_sample` (cached layers via GHA cache) |
| **test** | After docker | Runs `ceedling test:all` inside the container — no tool installation needed |
| **build** | After test | Checks out with submodules, runs CMake + Ninja inside the container — no tool installation needed |
| **release** | `v*` tags only | Downloads build artifacts, creates GitHub Release with `.elf`, `.hex`, `.bin` |

> **Pre-built image:** You can pull the CI image directly:
> ```bash
> docker pull ghcr.io/embeddedops/stm32_embeddedops_sample:latest
> ```

---

## Adapting This Template

1. **Change MCU:** Update `STM32F446xx` define, linker script memory sizes, startup file, and clock config
2. **Add peripherals:** Enable modules in `stm32f4xx_hal_conf.h`, add HAL sources in `cmake/stm32hal.cmake`
3. **Add application code:** Create new modules in `App/` with corresponding tests in `test/`
4. **Modify CI:** Edit `.github/workflows/ci.yml` to add static analysis, coverage, or deployment steps

---

## License

MIT — see [LICENSE](LICENSE).

Built with care by [EmbeddedOps](https://github.com/EmbeddedOps).
