if(CMAKE_FILE_PATH)
    message("CMAKE_FILE_PATH = ${CMAKE_FILE_PATH} ")

    include_directories(${CMAKE_FILE_PATH}/../3rdLib)
    include_directories(${CMAKE_FILE_PATH}/../include)

    include_directories(${CMAKE_FILE_PATH}/correspondence/include)
    include_directories(${CMAKE_FILE_PATH}/connectDb/include)
    include_directories(${CMAKE_FILE_PATH}/commandObj/include)
    include_directories(${CMAKE_FILE_PATH}/dataObj/include)
    include_directories(${CMAKE_FILE_PATH}/myClient/include)

    link_directories(${CMAKE_FILE_PATH}/../libs)

    #数据模块
    set( DATAOBJ 
        ${CMAKE_FILE_PATH}/dataObj/msg.cpp
        ${CMAKE_FILE_PATH}/dataObj/user.cpp)

    #指令模块
    set( COMMANDOBJ 
        ${CMAKE_FILE_PATH}/commandObj/cmdCreateFactory.cpp
        ${CMAKE_FILE_PATH}/commandObj/dataMsgCmd.cpp
        ${CMAKE_FILE_PATH}/commandObj/heartRequestCmd.cpp
        ${CMAKE_FILE_PATH}/commandObj/heartMsgCmd.cpp
        ${CMAKE_FILE_PATH}/commandObj/loginCmd.cpp
        ${CMAKE_FILE_PATH}/commandObj/userChangeCmd.cpp
        ${CMAKE_FILE_PATH}/commandObj/friendshipChangeCmd.cpp)

    #客户端模块
    set( MYCLIENT
        ${CMAKE_FILE_PATH}/myClient/clientQQ.cpp)

    set(OTHER
        ${CMAKE_FILE_PATH}/../include/srcInclude/k_clip.cpp
        ${CMAKE_FILE_PATH}/../include/srcInclude/qt_clip.cpp
        ${CMAKE_FILE_PATH}/../include/srcInclude/other_funcation.cpp)

    #将需要的包设置给CLIENT
    set(CLIENT ${COMMANDOBJ} ${DATAOBJ} ${MYCLIENT} ${OTHER})

else()
    message("not set CMAKE_FILE_PATH")
endif()
        