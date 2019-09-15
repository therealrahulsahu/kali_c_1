cmake_minimum_required(VERSION 3.14)
project(practice)

set(CMAKE_CXX_STANDARD 14)

add_executable(practice cnlab/12sep/cli.c cnlab/12sep/ser.c cnlab/tcp/tcpclient.c cnlab/tcp/tcpserver.c)
