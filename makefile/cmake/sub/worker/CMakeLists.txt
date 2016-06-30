FILE(GLOB SOURCE_1 "${PROJECT_ROOT_PATH}/src/worker/*.cpp" "${PROJECT_ROOT_PATH}/src/common/global.cpp" "${PROJECT_ROOT_PATH}/src/common/iniReader.cpp")

ADD_EXECUTABLE(worker ${SOURCE_1})
TARGET_LINK_LIBRARIES(worker boost_log boost_log_setup boost_system boost_thread serverAddCar serverWorker memDB mysql checker mysqlcppconn)  
ADD_DEPENDENCIES(worker serverAddCar serverWorker memDB mysql checker)

