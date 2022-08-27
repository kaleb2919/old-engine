cmake_minimum_required(VERSION 3.23)

project(old-engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build)

set(BASE_EXTERNAL_DIR ${CMAKE_BINARY_DIR}/external)

include(ExternalProject)

# GLM

set(GLM_ROOT_DIR ${BASE_EXTERNAL_DIR}/glm)
set(GLM_INCLUDE_DIR ${GLM_ROOT_DIR}/include)

ExternalProject_Add(glm
    PREFIX ${BASE_EXTERNAL_DIR}
    GIT_REPOSITORY "https://github.com/g-truc/glm.git"
    GIT_TAG "0.9.9.8"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    UPDATE_COMMAND ""
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/glm ${GLM_INCLUDE_DIR}/glm

    LOG_DOWNLOAD ON LOG_UPDATE ON LOG_CONFIGURE ON LOG_BUILD ON LOG_INSTALL ON
)

# GLFW

set(GLFW_ROOT_DIR ${BASE_EXTERNAL_DIR}/glwf)
set(GLFW_LIB_DIR ${GLFW_ROOT_DIR}/lib)
set(GLFW_INCLUDE_DIR ${GLFW_ROOT_DIR}/include)

ExternalProject_add(glwf
    PREFIX ${BASE_EXTERNAL_DIR}
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "3.3.8"
    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=Release
        -DGLFW_BUILD_DOCS=OFF
        -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_INSTALL=ON
        -DBUILD_SHARED_LIBS=OFF
        -DCMAKE_INSTALL_PREFIX:PATH=${GLFW_ROOT_DIR}
    BUILD_BYPRODUCTS ${GLFW_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3${CMAKE_STATIC_LIBRARY_SUFFIX}

    LOG_DOWNLOAD ON LOG_UPDATE ON LOG_CONFIGURE ON LOG_BUILD ON LOG_INSTALL ON
)

add_library(libglwf STATIC IMPORTED)
add_dependencies(libglwf glwf)
file(MAKE_DIRECTORY ${GLFW_LIB_DIR})
file(MAKE_DIRECTORY ${GLFW_INCLUDE_DIR})
set_target_properties(libglwf PROPERTIES
    IMPORTED_LOCATION ${GLFW_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3${CMAKE_STATIC_LIBRARY_SUFFIX}
    INTERFACE_INCLUDE_DIRECTORIES ${GLFW_INCLUDE_DIR}
)

# GLAD

set(GLAD_ROOT_DIR ${BASE_EXTERNAL_DIR}/glad)
set(GLAD_SRC_DIR ${GLAD_ROOT_DIR}/src)
set(GLAD_LIB_DIR ${GLAD_ROOT_DIR}/lib)
set(GLAD_INCLUDE_DIR ${GLAD_ROOT_DIR}/include)

ExternalProject_add(glad
    PREFIX ${BASE_EXTERNAL_DIR}
    GIT_REPOSITORY "https://github.com/Dav1dde/glad.git"
    GIT_TAG "v0.1.36"
    CMAKE_ARGS ${CMAKE_ARGS}
        -DGLAD_OUT_DIR=${GLAD_ROOT_DIR}
        -DGLAD_PROFILE=core
        -DGLAD_API=gl=3.3
        -DGLAD_INSTALL=On
        -DCMAKE_INSTALL_PREFIX:PATH=${GLAD_ROOT_DIR}
    BUILD_BYPRODUCTS ${GLAD_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}glad${CMAKE_STATIC_LIBRARY_SUFFIX}

    LOG_DOWNLOAD ON LOG_UPDATE ON LOG_CONFIGURE ON LOG_BUILD ON LOG_INSTALL ON
)

add_library(libglad STATIC IMPORTED)
add_dependencies(libglad glad)
file(MAKE_DIRECTORY ${GLAD_LIB_DIR})
file(MAKE_DIRECTORY ${GLAD_INCLUDE_DIR})
set_target_properties(libglad PROPERTIES
    IMPORTED_LOCATION ${GLAD_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}glad${CMAKE_STATIC_LIBRARY_SUFFIX}
    INTERFACE_INCLUDE_DIRECTORIES ${GLAD_INCLUDE_DIR}
)

# tomlPlusPlus

set(TPP_ROOT_DIR ${BASE_EXTERNAL_DIR}/tpp)
set(TPP_INCLUDE_DIR ${TPP_ROOT_DIR}/include)

ExternalProject_add(tpp
    PREFIX ${BASE_EXTERNAL_DIR}
    GIT_REPOSITORY "https://github.com/marzer/tomlplusplus.git"
    GIT_TAG "v3.1.0"
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${TPP_ROOT_DIR}

    LOG_DOWNLOAD ON LOG_UPDATE ON LOG_CONFIGURE ON LOG_BUILD ON LOG_INSTALL ON
)

# EnTT

set(ENTT_ROOT_DIR ${BASE_EXTERNAL_DIR}/entt)
set(ENTT_INCLUDE_DIR ${ENTT_ROOT_DIR}/include)

ExternalProject_add(entt
    PREFIX ${BASE_EXTERNAL_DIR}
    GIT_REPOSITORY "https://github.com/skypjack/entt.git"
    GIT_TAG "v3.10.3"
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${ENTT_ROOT_DIR}

    LOG_DOWNLOAD ON LOG_UPDATE ON LOG_CONFIGURE ON LOG_BUILD ON LOG_INSTALL ON
)

# MAIN
file(GLOB_RECURSE old-engine_src src/*)
add_executable(old-engine ${old-engine_src})

add_dependencies(old-engine glm glad tpp entt)

target_link_libraries(old-engine opengl32 libglwf libglad)

target_include_directories(old-engine AFTER PUBLIC "${GLM_INCLUDE_DIR}")
target_include_directories(old-engine AFTER PUBLIC "${TPP_INCLUDE_DIR}")
target_include_directories(old-engine AFTER PUBLIC "${ENTT_INCLUDE_DIR}")

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
)
