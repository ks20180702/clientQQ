include_directories(../include)

include_directories(./correspondence/include)
include_directories(./connectDb/include)
include_directories(./commandObj/include)
include_directories(./dataObj/include)
include_directories(./myClient/include)

link_directories(${PROJECT_SOURCE_DIR}/lib)

#数据模块
set( DATAOBJ 
    ./dataObj/msg.cpp
    ./dataObj/user.cpp)

#指令模块
set( COMMANDOBJ 
    ./commandObj/cmdCreateFactory.cpp
    ./commandObj/loginCmd.cpp
    ./commandObj/dataMsgCmd.cpp
    ./commandObj/heartRequestCmd.cpp
    ./commandObj/heartMsgCmd.cpp
    ./commandObj/userChangeCmd.cpp
    ./commandObj/friendshipChangeCmd.cpp)

#客户端模块
set( MYCLIENT
    ./myClient/clientQQ.cpp)


set(OTHER
    ../include/srcInclude/k_clip.cpp
    ../include/srcInclude/other_funcation.cpp
)

if (MSVC)
    link_directories(${PROJECT_SOURCE_DIR}/libs)

elseif(UNIX)
    link_directories("/usr/local/psqlodbc/lib")
endif()

set(MAINFILE main.cpp)
set(MAINNAME main)

add_executable(${MAINNAME} ${MAINFILE} ${COMMANDOBJ} ${DATAOBJ} ${MYCLIENT} ${OTHER})

if (MSVC)
#    set(pgodbc_path ${PROJECT_SOURCE_DIR}/libs/psqlodbc)
#    target_link_libraries(${MAINNAME} ${pgodbc_path}/psqlodbc35w.dll)
#    target_link_libraries(${MAINNAME} ${pgodbc_path}/psqlodbc30a.dll)
#    target_link_libraries(${MAINNAME} ${pgodbc_path}/libpq.dll)
elseif(UNIX)
    target_link_libraries(${MAINNAME} /usr/local/psqlodbc/lib/psqlodbca.so)
endif()

#target_link_libraries(${MAINNAME} ${PROJECT_SOURCE_DIR}/libs/WS2_32.Lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
