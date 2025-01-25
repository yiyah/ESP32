# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

# 运行 export.sh 脚本并导入环境变量
execute_process(
    COMMAND /bin/zsh -c "source /Users/yiya/tools/esp512/v5.1.2/esp-idf/export.sh > /dev/null && env"
    OUTPUT_VARIABLE ENV_VARS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
# 将换行符替换为分号
string(REPLACE "\n" ";" ENV_VARS_LIST ${ENV_VARS})

# 解析环境变量
foreach(VAR IN LISTS ENV_VARS_LIST)
    string(REPLACE "=" ";" VAR_LIST ${VAR})
    list(LENGTH VAR_LIST VAR_LIST_LENGTH)
    if(VAR_LIST_LENGTH EQUAL 2)
        list(GET VAR_LIST 0 VAR_NAME)
        list(GET VAR_LIST 1 VAR_VALUE)
        set(ENV{${VAR_NAME}} ${VAR_VALUE})
        message(STATUS "Set environment variable ${VAR_NAME}=${VAR_VALUE}")
    else()
        message(WARNING "Skipping invalid environment variable: ${VAR}")
    endif()
endforeach()

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(learn)

# Add the components directory
set(EXTRA_COMPONENT_DIRS ${CMAKE_SOURCE_DIR}/components/led)
