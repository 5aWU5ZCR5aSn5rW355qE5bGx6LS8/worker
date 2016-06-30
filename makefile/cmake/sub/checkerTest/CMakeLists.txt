FILE(GLOB SOURCE_1 "${PROJECT_ROOT_PATH}/src/checkerTest/*.cpp")

ADD_EXECUTABLE(checkerTest ${SOURCE_1})
TARGET_LINK_LIBRARIES(checkerTest memDB checker)  
ADD_DEPENDENCIES(checkerTest checker memDB)

