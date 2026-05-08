cmake_minimum_required(VERSION 3.10)
project(DDG)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLUT
find_package(GLUT REQUIRED)

# SuiteSparse configuration
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")

find_path(SUITESPARSE_INCLUDE_DIR NAMES cholmod.h PATH_SUFFIXES suitesparse)
if(NOT SUITESPARSE_INCLUDE_DIR)
    message(FATAL_ERROR "SuiteSparse headers not found")
endif()

set(SUITESPARSE_LIBS spqr umfpack cholmod metis colamd ccolamd camd amd suitesparseconfig)
set(SUITESPARSE_LIBRARIES "")

foreach(LIB ${SUITESPARSE_LIBS})
    find_library(LIB_${LIB} NAMES ${LIB})
    if(LIB_${LIB})
        list(APPEND SUITESPARSE_LIBRARIES ${LIB_${LIB}})
    else()
        message(WARNING "Could not find library ${LIB}")
    endif()
endforeach()

if(APPLE)
    find_library(ACCELERATE_FRAMEWORK Accelerate)
    set(BLAS_LIBRARIES ${ACCELERATE_FRAMEWORK})
else()
    find_package(BLAS REQUIRED)
    find_package(LAPACK REQUIRED)
    set(BLAS_LIBRARIES ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})
endif()

find_library(TBB_LIBRARY tbb)
if(TBB_LIBRARY)
    list(APPEND SUITESPARSE_LIBRARIES ${TBB_LIBRARY})
endif()

include_directories(${SUITESPARSE_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLUT_INCLUDE_DIR})

add_definitions(-DUF_long=long\ long)
add_definitions(-DGL_SILENCE_DEPRECATION)

# Function to add a DDG subproject
function(add_ddg_project DIR_NAME)
    file(GLOB SOURCES "${DIR_NAME}/src/*.cpp")
    file(GLOB HEADERS "${DIR_NAME}/include/*.h")
    
    if(NOT SOURCES)
        return()
    endif()

    add_executable(${DIR_NAME} ${SOURCES} ${HEADERS})
    
    target_include_directories(${DIR_NAME} PRIVATE 
        ${DIR_NAME}/include
        ${DIR_NAME}/src
    )
    
    target_link_libraries(${DIR_NAME} PRIVATE
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
        ${SUITESPARSE_LIBRARIES}
        ${BLAS_LIBRARIES}
        m
    )
    
    if(APPLE)
        target_link_libraries(${DIR_NAME} PRIVATE "-framework OpenGL" "-framework GLUT")
    endif()
endfunction()

# Add subprojects
add_ddg_project(BaseCode)
add_ddg_project(Connection)
add_ddg_project(Elasticity)
add_ddg_project(Fairing)
add_ddg_project(Flatten)
add_ddg_project(Geodesics)
add_ddg_project(Hot2)

# Build all test executables
# Test: BaseCode
file(GLOB_RECURSE BASECODE_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_BaseCode.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/BaseCode/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/BaseCode/include/*.h"
)
list(REMOVE_ITEM BASECODE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/BaseCode/src/main.cpp")
add_executable(test_BaseCode ${BASECODE_SOURCES})
target_include_directories(test_BaseCode PRIVATE BaseCode/include BaseCode/src)
target_link_libraries(test_BaseCode PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${SUITESPARSE_LIBRARIES} ${BLAS_LIBRARIES} m)
if(APPLE)
    target_link_libraries(test_BaseCode PRIVATE "-framework OpenGL" "-framework GLUT")
endif()

# Test: Geodesics
file(GLOB_RECURSE GEODESICS_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_Geodesics.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Geodesics/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Geodesics/include/*.h"
)
list(REMOVE_ITEM GEODESICS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Geodesics/src/main.cpp")
add_executable(test_Geodesics ${GEODESICS_SOURCES})
target_include_directories(test_Geodesics PRIVATE Geodesics/include Geodesics/src)
target_link_libraries(test_Geodesics PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${SUITESPARSE_LIBRARIES} ${BLAS_LIBRARIES} m)
if(APPLE)
    target_link_libraries(test_Geodesics PRIVATE "-framework OpenGL" "-framework GLUT")
endif()

# Test: Fairing
file(GLOB_RECURSE FAIRING_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_Fairing.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Fairing/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Fairing/include/*.h"
)
list(REMOVE_ITEM FAIRING_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Fairing/src/main.cpp")
add_executable(test_Fairing ${FAIRING_SOURCES})
target_include_directories(test_Fairing PRIVATE Fairing/include Fairing/src)
target_link_libraries(test_Fairing PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${SUITESPARSE_LIBRARIES} ${BLAS_LIBRARIES} m)
if(APPLE)
    target_link_libraries(test_Fairing PRIVATE "-framework OpenGL" "-framework GLUT")
endif()

# Test: Flatten
file(GLOB_RECURSE FLATTEN_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_Flatten.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Flatten/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Flatten/include/*.h"
)
list(REMOVE_ITEM FLATTEN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Flatten/src/main.cpp")
add_executable(test_Flatten ${FLATTEN_SOURCES})
target_include_directories(test_Flatten PRIVATE Flatten/include Flatten/src)
target_link_libraries(test_Flatten PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${SUITESPARSE_LIBRARIES} ${BLAS_LIBRARIES} m)
if(APPLE)
    target_link_libraries(test_Flatten PRIVATE "-framework OpenGL" "-framework GLUT")
endif()

# Test: Connection
file(GLOB_RECURSE CONNECTION_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_Connection.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Connection/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Connection/include/*.h"
)
list(REMOVE_ITEM CONNECTION_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Connection/src/main.cpp")
add_executable(test_Connection ${CONNECTION_SOURCES})
target_include_directories(test_Connection PRIVATE Connection/include Connection/src)
target_link_libraries(test_Connection PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${SUITESPARSE_LIBRARIES} ${BLAS_LIBRARIES} m)
if(APPLE)
    target_link_libraries(test_Connection PRIVATE "-framework OpenGL" "-framework GLUT")
endif()

# Test: Elasticity
file(GLOB_RECURSE ELASTICITY_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_Elasticity.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Elasticity/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Elasticity/include/*.h"
)
list(REMOVE_ITEM ELASTICITY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Elasticity/src/main.cpp")
add_executable(test_Elasticity ${ELASTICITY_SOURCES})
target_include_directories(test_Elasticity PRIVATE Elasticity/include Elasticity/src)
target_link_libraries(test_Elasticity PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${SUITESPARSE_LIBRARIES} ${BLAS_LIBRARIES} m)
if(APPLE)
    target_link_libraries(test_Elasticity PRIVATE "-framework OpenGL" "-framework GLUT")
endif()

# Test: Hot2
file(GLOB_RECURSE HOT2_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_Hot2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Hot2/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Hot2/include/*.h"
)
list(REMOVE_ITEM HOT2_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Hot2/src/main.cpp")
add_executable(test_Hot2 ${HOT2_SOURCES})
target_include_directories(test_Hot2 PRIVATE Hot2/include Hot2/src)
target_link_libraries(test_Hot2 PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${SUITESPARSE_LIBRARIES} ${BLAS_LIBRARIES} m)
if(APPLE)
    target_link_libraries(test_Hot2 PRIVATE "-framework OpenGL" "-framework GLUT")
endif()