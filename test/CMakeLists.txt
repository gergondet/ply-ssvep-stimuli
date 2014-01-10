ADD_DEFINITIONS(${${PROJECT_NAME}_CXXFLAGS})

SET(EXEC_NAME testply-ssvep-stimuli)

SET(${EXEC_NAME}_src
    testply-ssvep-stimuli.cpp
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_INSTALL_PREFIX}/include)
LINK_DIRECTORIES(${${PROJECT_NAME}_BINARY_DIR}/src)
LINK_DIRECTORIES(${CMAKE_INSTALL_PREFIX}/lib)

ADD_EXECUTABLE(${EXEC_NAME}
  ${${EXEC_NAME}_src}
  )

SET_TARGET_PROPERTIES(${PROJECT_NAME_LIB}
  PROPERTIES
  COMPILE_FLAGS ${${PROJECT_NAME}_src_CXXFLAGS}
  LINK_FLAGS "${${PROJECT_NAME}_src_LDFLAGS} -pthread"}
)

IF(WIN32)
TARGET_LINK_LIBRARIES(${EXEC_NAME} "ply-ssvep-stimuli.lib;bci-interface.lib;sfml-graphics.lib;sfml-window.lib;sfml-system.lib;ws2_32.lib;OpenGL32.lib;glu32.lib")
ELSE(WIN32)
TARGET_LINK_LIBRARIES(${EXEC_NAME} ply-ssvep-stimuli bci-interface ${SFML_LIBRARIES} pthread)
ENDIF(WIN32)
TARGET_LINK_LIBRARIES(${EXEC_NAME} ${Boost_LIBRARIES})

SET(MODELS
${CMAKE_SOURCE_DIR}/test/models/can-00000.jpg
${CMAKE_SOURCE_DIR}/test/models/can-00001.jpg
${CMAKE_SOURCE_DIR}/test/models/can-00002.jpg
${CMAKE_SOURCE_DIR}/test/models/can-00003.jpg
${CMAKE_SOURCE_DIR}/test/models/can-00004.jpg
${CMAKE_SOURCE_DIR}/test/models/can-00005.jpg
${CMAKE_SOURCE_DIR}/test/models/can-00006.jpg
${CMAKE_SOURCE_DIR}/test/models/can.ply
)
FILE(COPY ${MODELS} DESTINATION ${CMAKE_BINARY_DIR}/test/models)
