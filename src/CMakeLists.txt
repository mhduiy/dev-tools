find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(DDEShell REQUIRED)

add_library(shell-dev-tools SHARED
    devtoolsitem.cpp
    devtoolsitem.h
    fastitemmodel.cpp
    fastitemmodel.h
)

ds_install_package(PACKAGE org.deepin.ds.dock.devtools TARGET shell-dev-tools)

target_link_libraries(shell-dev-tools
    PRIVATE Qt6::Quick
    Dde::Shell
)
