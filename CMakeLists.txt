cmake_minimum_required(VERSION 3.15)

project(SFMLProject LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


add_executable(SFMLProject
    src/main.cpp
    data/shader.frag
)

target_link_libraries(SFMLProject sfml-graphics
                                       sfml-audio
                                       sfml-network
                                       sfml-system
                                       sfml-window
)
target_compile_features(SFMLProject PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()
install(TARGETS SFMLProject
        RUNTIME DESTINATION .)
install(DIRECTORY data
        DESTINATION .)
