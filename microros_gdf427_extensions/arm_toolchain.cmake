include(CMakeForceCompiler)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(PLATFORM_NAME "LwIP")

# Makefile flags
set(ARCH_CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -DUSE_HAL_DRIVER -DGD32F427 -D_TIMEVAL_DEFINED -Og -Wall -fdata-sections -ffunction-sections")
set(ARCH_OPT_FLAGS "")

set(CMAKE_C_COMPILER /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/../../toolchain/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/../../toolchain/bin/arm-none-eabi-g++)

set(CMAKE_C_FLAGS_INIT "-std=c11 ${ARCH_CPU_FLAGS} ${ARCH_OPT_FLAGS} -DCLOCK_MONOTONIC=0" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_INIT "-std=c++14 ${ARCH_CPU_FLAGS} ${ARCH_OPT_FLAGS} -DCLOCK_MONOTONIC=0" CACHE STRING "" FORCE)

include_directories(SYSTEM 
	/home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/FreeRTOS-Plus-POSIX/include
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/include
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/include/private
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/include/FreeRTOS_POSIX
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/include/FreeRTOS_POSIX/sys
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/src/hal/interface
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/src/modules/interface
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/src/utils/interface
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/src/config
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/src/drivers/interface
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/Middlewares/Third_Party/LwIP/src/include/posix
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/Middlewares/Third_Party/LwIP/src/include
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/Inc
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/Drivers/GD32F4xx_standard_peripheral/Include
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/Drivers/CMSIS/Device/GD/GD32F4xx/Include
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/Drivers/CMSIS/Include
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/Middlewares/Third_Party/LwIP/system
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/Middlewares/Third_Party/LwIP/src/include/compat/posix
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/Middlewares/Third_Party/LwIP/src/include/compat/posix/net
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys
 /home/bowen/mros_ws/firmware/freertos_apps/microros_gdf427_extensions/Middlewares/Third_Party/LwIP/src/include/compat/stdc

    )
	
set(__BIG_ENDIAN__ 0)