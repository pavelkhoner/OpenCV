project(labkr)
add_executable(labkr labkr.cpp labkr.report.md.in.txt)
target_link_libraries(labkr ${OpenCV_LIBS})

# prepare report md file
file(READ labkr.cpp cpp_source)
configure_file(labkr.report.md.in.txt ${CMAKE_CURRENT_BINARY_DIR}/labkr.report.md @ONLY)
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/labkr.report.md" "$<TARGET_FILE_DIR:${PROJECT_NAME}>")