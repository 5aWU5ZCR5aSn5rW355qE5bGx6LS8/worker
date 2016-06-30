FILE(GLOB SOURCE_1 "${PROJECT_ROOT_PATH}/src/serverWorker/*.cpp")

ADD_LIBRARY(serverWorker STATIC ${SOURCE_1})  
ADD_DEPENDENCIES(serverWorker memDB mysql checker)

