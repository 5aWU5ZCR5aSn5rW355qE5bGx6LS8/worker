FILE(GLOB SOURCE_1 "${PROJECT_ROOT_PATH}/src/serverAddCarTest/*.cpp")

ADD_EXECUTABLE(serverAddCarTest ${SOURCE_1})
TARGET_LINK_LIBRARIES(serverAddCarTest memDB)  
TARGET_LINK_LIBRARIES(serverAddCarTest serverAddCar)  
TARGET_LINK_LIBRARIES(serverAddCarTest mysql)  
TARGET_LINK_LIBRARIES(serverAddCarTest mysqlcppconn)  
TARGET_LINK_LIBRARIES (serverAddCarTest ${Boost_LIBRARIES} boost_log)
ADD_DEPENDENCIES(serverAddCarTest memDB serverAddCar mysql)

