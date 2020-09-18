include(CMakePackageConfigHelpers)

set(exported_targets_name "${PROJECT_NAME}Targets")
set(exported_targets_filename "${exported_targets_name}.cmake")
set(export_dirpath "lib/cmake/safecppjson")
set(config_basename "${PROJECT_NAME}Config")
set(config_filename "${config_basename}.cmake")
set(version_filename "${config_basename}Version.cmake")

write_basic_package_version_file(
    ${version_filename}
    COMPATIBILITY SameMajorVersion
)

configure_file("cmake/${config_filename}.in" "${config_filename}" @ONLY)

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${exported_targets_name}
    ARCHIVE DESTINATION "lib"
)
install(
    EXPORT ${exported_targets_name}
    FILE ${exported_targets_filename}
    NAMESPACE safecppjson::
    DESTINATION ${export_dirpath}
)

file (GLOB_RECURSE headers "src/*.hpp")
install (
  FILES
    ${headers}
  DESTINATION
    "include/${PROJECT_NAME}"
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${config_filename}"
        "${CMAKE_CURRENT_BINARY_DIR}/${version_filename}"
    DESTINATION
        ${export_dirpath}
)
# install(
#     DIRECTORY
#         "${CMAKE_CURRENT_SOURCE_DIR}/include/safecppjson"
#         "${CMAKE_CURRENT_BINARY_DIR}/include/safecppjson"
#     DESTINATION
#         "include"
# )
