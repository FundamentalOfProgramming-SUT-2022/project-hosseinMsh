cmake_minimum_required(VERSION 3.23)
project(project_hosseinMsh)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(.idea)

add_executable(project_hosseinMsh
        .idea/modules.xml
        .idea/project-hosseinMsh.iml
        .idea/vcs.xml
        .idea/workspace.xml
        main.c)
