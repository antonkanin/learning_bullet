cmake_minimum_required(VERSION 3.13)

project(Chapter4.1_HandlingMultipleObjects)

file(GLOB sources "Chapter4.1/*.cpp" "Chapter4.1/*.h")
#file(COPY ${resources} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)

add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME}
        GL
        GLU
        glut
        BulletDynamics
        BulletCollision
        LinearMath)

target_include_directories(${PROJECT_NAME} PUBLIC
        /usr/include/bullet
        /usr/include/GL)

