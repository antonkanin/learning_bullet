cmake_minimum_required(VERSION 3.13)

project(Chapter5.2_Constraints)

file(GLOB sources "Chapter5.2/*.cpp" "Chapter5.2/*.h")
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

