cmake_minimum_required(VERSION 3.13)

project(Chapter3.2_CreatingOutFirstPhysicsObject)

file(GLOB sources "Chapter3.2/*.cpp" "Chapter3.2/*.h")
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

