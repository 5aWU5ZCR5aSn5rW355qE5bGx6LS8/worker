FILE(GLOB SOURCE_1 "${PROJECT_ROOT_PATH}/src/serverAddCar/*.cpp")

ADD_LIBRARY(serverAddCar STATIC ${SOURCE_1})  
