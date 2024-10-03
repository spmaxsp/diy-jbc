cmake_minimum_required(VERSION 3.22)

# Setup compiler settings
set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)
set(PROJ_PATH                       ${CMAKE_CURRENT_SOURCE_DIR})
message("Build type: "              ${CMAKE_BUILD_TYPE})

#
# Core project settings
#
project(diy-jbc)
enable_language(C CXX ASM)

#
# Core MCU flags, CPU, instruction set and FPU setup
# Needs to be set properly for your MCU
#
set(CPU_PARAMETERS
    -mthumb

    -mcpu=cortex-m0plus
    -mfloat-abi=soft
)

# Set linker script
set(linker_script_SRC               ${PROJ_PATH}/STM32G071GBUXN_FLASH.ld)
set(EXECUTABLE                      ${CMAKE_PROJECT_NAME})

#
# List of source files to compile
#
set(sources_SRCS
    # System / Hardware
    ${PROJ_PATH}/Core/Hardware/Src/stm32g0xx_it.c 
    ${PROJ_PATH}/Core/Hardware/Src/syscalls.c 
    ${PROJ_PATH}/Core/Hardware/Src/sysclock.c 
    ${PROJ_PATH}/Core/Hardware/Src/sysmem.c 
    ${PROJ_PATH}/Core/Hardware/Src/system_stm32g0xx.c 

    ${PROJ_PATH}/Core/Hardware/Src/dma_ser_ui.c 
    ${PROJ_PATH}/Core/Hardware/Src/dma_ws2812b.c 
    ${PROJ_PATH}/Core/Hardware/Src/gpio_button.c
    ${PROJ_PATH}/Core/Hardware/Src/i2c.c 
    ${PROJ_PATH}/Core/Hardware/Src/spi.c 
    ${PROJ_PATH}/Core/Hardware/Src/tim_encoder.c 
    ${PROJ_PATH}/Core/Hardware/Src/tim_ws2812b.c 
    ${PROJ_PATH}/Core/Hardware/Src/usart_ser_ui.c

    ${PROJ_PATH}/Core/Startup/startup_stm32g071g8uxn.s

    # Application / Main
    ${PROJ_PATH}/Core/Src/main.c 
    
    ${PROJ_PATH}/Core/Src/encoder.c

    ${PROJ_PATH}/Core/Src/display.c
    ${PROJ_PATH}/Core/Src/display_s_graph.c
    ${PROJ_PATH}/Core/Src/display_s_menu.c
    ${PROJ_PATH}/Core/Src/display_s_main.c

    ${PROJ_PATH}/Core/Src/ser_ui.c
    ${PROJ_PATH}/Core/Src/temperature.c
    ${PROJ_PATH}/Core/Src/ws2812b.c

    # PID
    ${PROJ_PATH}/Core/Src/pid/pid.c

    # U8G2
    ${PROJ_PATH}/Core/Src/u8g2_stm32g0xx_helper.c

    ${PROJ_PATH}/Core/Src/u8g2/mui.c 
    ${PROJ_PATH}/Core/Src/u8g2/mui_u8g2.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_arc.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_bitmap.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_box.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_buffer.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_button.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_circle.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_cleardisplay.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_d_memory.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_d_setup.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_font.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_fonts.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_hvline.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_input_value.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_intersection.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_kerning.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_line.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_ll_hvline.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_message.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_polygon.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_selection_list.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8g2_setup.c
    ${PROJ_PATH}/Core/Src/u8g2/u8log_u8g2.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8log_u8x8.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8log.c 

    ${PROJ_PATH}/Core/Src/u8g2/u8x8_8x8.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8x8_byte.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8x8_cad.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8x8_capture.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8x8_debounce.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8x8_display.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8x8_fonts.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8x8_gpio.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8x8_input_value.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8x8_message.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8x8_selection_list.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8x8_setup.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8x8_string.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8x8_u8toa.c 
    ${PROJ_PATH}/Core/Src/u8g2/u8x8_u16toa.c 
    
    ${PROJ_PATH}/Core/Src/u8g2/u8x8_d_ssd1306_128x64_noname.c

    # HAL/LL drivers
    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_dma.c
    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_exti.c     
    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_gpio.c
    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_i2c.c
    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_pwr.c 
    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_rcc.c 
    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_spi.c
    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_tim.c
    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_usart.c
    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_utils.c 
)

#
# Include directories
#
set(include_path_DIRS
    ${PROJ_PATH}/Core/Inc
    ${PROJ_PATH}/Core/Hardware/Inc
    ${PROJ_PATH}/Core/Src/u8g2
    ${PROJ_PATH}/Core/Src/pid
    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Inc
    ${PROJ_PATH}/Drivers/CMSIS/Include
    ${PROJ_PATH}/Drivers/CMSIS/Device/ST/STM32G0xx/Include
)

#
# Symbols definition
#
set(symbols_SYMB
"DEBUG"
"STM32G071xx"   # MCU family
"USE_FULL_LL_DRIVER"
"HSE_VALUE=16000000" #external crystal frequency (in Hz)
)

# Executable files
add_executable(${EXECUTABLE} ${sources_SRCS})

# Include paths
target_include_directories(${EXECUTABLE} PRIVATE ${include_path_DIRS})

# Project symbols
target_compile_definitions(${EXECUTABLE} PRIVATE ${symbols_SYMB})

# Compiler options
target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    # Full debug configuration
    -O0 -g3 -ggdb
)

# Linker options
target_link_options(${EXECUTABLE} PRIVATE
    -T${linker_script_SRC}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    --specs=nosys.specs
    -u _printf_float                # STDIO float formatting support
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -lsupc++
    -Wl,--end-group
    -Wl,--print-memory-usage
)

# Execute post-build to print size
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
)

# Convert output to hex and binary
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
)

# Convert to bin file -> add conditional check?
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin
)