OPTION(VKVG_TEST_DIRECT_DRAW "(Experimental)Draw directly on backend surface, if off surface is blitted." OFF)
IF (VKVG_TEST_DIRECT_DRAW)
	ADD_DEFINITIONS (-DVKVG_TEST_DIRECT_DRAW)
ENDIF ()

OPTION(VKVG_TEST_OFFSCREEN "Draw offscreen without presenting result." OFF)
IF (VKVG_TEST_OFFSCREEN)
	ADD_DEFINITIONS (-DVKVG_TEST_OFFSCREEN)
ENDIF ()

FUNCTION (buildtest TEST_NAME)
	ADD_EXECUTABLE(test_${TEST_NAME} "${TEST_NAME}.c" )
	TARGET_INCLUDE_DIRECTORIES(test_${TEST_NAME} PRIVATE
		${Vulkan_INCLUDE_DIRS}
		${GLFW3_INCLUDE_DIR}
		${CMAKE_CURRENT_SOURCE_DIR}/../include
		${CMAKE_CURRENT_SOURCE_DIR}/../src
		${CMAKE_CURRENT_SOURCE_DIR}/common
		${CMAKE_CURRENT_SOURCE_DIR}/../vkh/include
		${CMAKE_CURRENT_SOURCE_DIR}/../vkh/src
	)
	TARGET_LINK_LIBRARIES(test_${TEST_NAME}
		tests_common
	)
ENDFUNCTION (buildtest)

ADD_LIBRARY("tests_common" STATIC common/vkengine.c common/test.c common/rnd.c)
TARGET_INCLUDE_DIRECTORIES(tests_common PRIVATE
	${Vulkan_INCLUDE_DIRS}
	${GLFW3_INCLUDE_DIR}
	"${CMAKE_CURRENT_SOURCE_DIR}/../include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../src"
	"${CMAKE_CURRENT_SOURCE_DIR}/../common"
	"${CMAKE_CURRENT_SOURCE_DIR}/../vkh/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../vkh/src"
	)
TARGET_LINK_LIBRARIES(tests_common
	${Vulkan_LIBRARIES}
	${GLFW3_LIBRARY}
	vkvg_static
	)

file(GLOB_RECURSE DATAS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "data/*")
FOREACH(DATA_FILE ${DATAS})
	GET_FILENAME_COMPONENT(copy-dest-dir ${CMAKE_CURRENT_BINARY_DIR}/${DATA_FILE} DIRECTORY)
	SET(copy-output ${CMAKE_CURRENT_BINARY_DIR}/${DATA_FILE})
	ADD_CUSTOM_COMMAND(
		OUTPUT  ${copy-output}
		COMMAND ${CMAKE_COMMAND} -E make_directory ${copy-dest-dir}
		COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/${DATA_FILE}" "${copy-output}"
		COMMENT "Copying ${DATA_FILE} to ${copy-output}"
		DEPENDS ${DATA_FILE}
		VERBATIM
		)
ENDFOREACH()
add_custom_target("${PROJECT_NAME}_DataCopy" ALL DEPENDS ${DATAS})

#build test apps
file(GLOB TESTS "*.c")
FOREACH(TEST ${TESTS})
GET_FILENAME_COMPONENT(testname ${TEST} NAME_WE)
buildtest(${testname})
ENDFOREACH()




