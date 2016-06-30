FILE(GLOB SOURCE_1 "${PROJECT_ROOT_PATH}/src/mysqlTest/*.cpp")

ADD_EXECUTABLE(mysqlTest ${SOURCE_1})
TARGET_LINK_LIBRARIES(mysqlTest mysql mysqlcppconn)  
ADD_DEPENDENCIES(mysqlTest mysql)

