include_directories(${CMAKE_CURRENT_LIST_DIR}/../../)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

## micropython-common with deletions
# Essential
include(pimoroni_i2c/micropython)
include(pimoroni_bus/micropython)

# Pico Graphics Essential
include(hershey_fonts/micropython)
include(bitmap_fonts/micropython)
include(picographics/micropython)

# Pico Graphics Extra
# include(jpegdec/micropython)
# include(qrcode/micropython/micropython)

# Sensors & Breakouts
# include(micropython-common-breakouts)

# Packs & Bases
# include(pico_unicorn/micropython)
# include(pico_scroll/micropython)
# include(pico_rgb_keypad/micropython)
# include(pico_explorer/micropython)

# LEDs & Matrices
# include(plasma/micropython)
include(hub75/micropython)

# Servos & Motors
# include(pwm/micropython)
# include(servo/micropython)
# include(encoder/micropython)
# include(motor/micropython)

# Utility
include(adcfft/micropython)

include(modules_py/modules_py)

# Most board specific ports wont need all of these
copy_module(gfx_pack.py)
copy_module(interstate75.py)

# Must call `enable_ulab()` to enable
include(micropython-common-ulab)
enable_ulab()

# C++ Magic Memory
include(cppmem/micropython)
