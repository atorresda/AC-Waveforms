cmake_minimum_required(VERSION 3.21)
project(AC_Waveforms C)

set(CMAKE_C_STANDARD 99)

add_executable(AC_Waveforms main.c waveform.c)
