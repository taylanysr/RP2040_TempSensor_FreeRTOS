cmake_minimum_required(VERSION 3.19)

# initialize the SDK based on PICO_SDK_PATH
include(pico_sdk_import.cmake)
project(tempSensor)

# initialize the Pico SDK
pico_sdk_init()


add_executable(tempSensor
    src/main.c
)


FILE(GLOB FreeRTOS_src FreeRTOS-Kernel/*.c)

add_library( FreeRTOS STATIC
	${FreeRTOS_src}
	FreeRTOS-Kernel/portable/GCC/ARM_CM0/port.c
	FreeRTOS-Kernel/portable/MemMang/heap_4.c
)

target_include_directories( FreeRTOS PUBLIC
		FreeRTOS-Kernel/include
		include/
		FreeRTOS-Kernel/portable/GCC/ARM_CM0
	)

target_link_libraries( tempSensor 
	pico_stdlib 
	hardware_gpio 
	FreeRTOS
	)


target_link_libraries( tempSensor 
	pico_stdlib 
	hardware_adc
	FreeRTOS
	)

pico_add_extra_outputs(tempSensor)

pico_enable_stdio_usb(tempSensor 1)
pico_enable_stdio_uart(tempSensor 0)

pico_add_extra_outputs(tempSensor)
