cmake_minimum_required(VERSION 3.16)
project(GameDevelopment LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(GameDevelopment src/main.cpp "include/Game.h" "src/Game.cpp" "include/Window.h" "src/Window.cpp")
target_link_libraries(GameDevelopment PRIVATE sfml-graphics)
target_compile_features(GameDevelopment PRIVATE cxx_std_17)

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(resources)

if(WIN32)
    add_custom_command(
        TARGET GameDevelopment
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:GameDevelopment>
        VERBATIM)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)


install(TARGETS GameDevelopment)