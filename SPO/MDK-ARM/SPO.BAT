SET PATH=C:\Keil_v5\ARM\ARMCLANG\Bin;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files\Git LFS;C:\Program Files\CMake\bin;C:\MinGW\bin;C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility;C:\Program Files\Docker\Docker\resources\bin;C:\ProgramData\DockerDesktop\version-bin;C:\Program Files\Microchip\xc8\v2.31\bin;C:\Program Files\Git\cmd;C:\Program Files\nodejs\;C:\Program Files\MySQL\MySQL Shell 8.0\bin\;C:\Users\Андрей\AppData\Local\Microsoft\WindowsApps;C:\Program Files\JetBrains\IntelliJ IDEA Community Edition 2020.2\bin;C:\Program Files\Microsoft VS Code\bin;C:\Program Files (x86)\Jar2Exe Wizard\;C:\Users\Андрей\AppData\Local\GitHubDesktop\bin;C:\Program Files\JetBrains\CLion 2022.1.3\bin;C:\Users\Андрей\AppData\Roaming\npm;C:\Users\Андрей\AppData\Local\atom\bin
SET CPU_TYPE=STM32F103RC
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=SPO
SET CPU_CLOCK=0x007A1200
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmAsm" --Via "spo\startup_stm32f103xe._ia"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\main.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\gpio.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\rtc.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\spi.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\tim.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\usart.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\stm32f1xx_it.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\stm32f1xx_ll_gpio.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\stm32f1xx_ll_rtc.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\stm32f1xx_ll_rcc.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\stm32f1xx_ll_utils.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\stm32f1xx_ll_exti.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\stm32f1xx_ll_spi.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\stm32f1xx_ll_dma.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\stm32f1xx_ll_pwr.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\stm32f1xx_ll_tim.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\stm32f1xx_ll_usart.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\system_stm32f1xx.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\tft.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\spi_handler.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\fifo.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"spo\wtc_logic.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmLink" --Via "SPO\SPO.lnp"
