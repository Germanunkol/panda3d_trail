
set(P3TRAIL_HEADERS
  trailNode.h
  trail.h
)

set(P3TRAIL_SOURCES
  trailNode.cxx
  trail.cxx
)

composite_sources(p3trail P3TRAIL_SOURCES)
add_library(p3trail ${P3TRAIL_HEADERS} ${P3TRAIL_SOURCES})
set_target_properties(p3trail PROPERTIES DEFINE_SYMBOL BUILDING_TRAIL)
target_link_libraries(p3trail panda)
  #target_link_libraries(p3trail panda
  #  PKG::OPENCV PKG::ARTOOLKIT)
set_target_properties(p3trail PROPERTIES CXX_EXCEPTIONS ON)
target_interrogate(p3trail ALL)

install(TARGETS p3trail
	EXPORT Trail COMPONENT Trail
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/panda3d
  ARCHIVE COMPONENT TrailDevel)
install(FILES ${P3TRAIL_HEADERS} COMPONENT TrailDevel DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/panda3d)

export_targets(Trail COMPONENT TrailDevel)

