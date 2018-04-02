# set(GLUT_INCLUDE_DIR "C:/includes")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
# find_package(GLM REQUIRED)

file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(project3 ${SOURCES})

include_directories( 
	${OPENGL_INCLUDE_DIRS} 
	${GLUT_INCLUDE_DIR} 
	${CMAKE_CURRENT_SOURCE_DIR}
	"C:/include"
)

add_custom_command(TARGET project3 PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/lib $<TARGET_FILE_DIR:project3>)

message(${GLUT_LIBRARY})
target_link_libraries(project3 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
