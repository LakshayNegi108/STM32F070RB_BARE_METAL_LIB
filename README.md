# STM32F070RB_BARE_METAL_LIB

Basic library for stm32f070rb made using register-level programming.

##======= Creating Project ========##
1)New Project -> use the STMcube_HAL lib
2)Clear all code in main.c
3)Create new folder "Library" -> Two new folders
4) First folder "Inc" -> Create Header File "Header_name.h"
5) Second folder "Src" -> Create source file "SourceFile_name.c"
6) Right-click Library -> Properties -> C/C++ Build -> Un-click "Exclude file from compiler"
7) Right click on Project -> Properties -> c/c++ build -> Settings -> MCU GCC Compiler -> Include paths -> Navigate to the Inc created in Library folder
8) Apply and Close
9) Build and Run
