////
// otl使用案例
////

#include <otlv4.h>

////定义一个连接数据库的连接实例，一个实例可以处理多个事务
otl_connect c; 
 
int con_pg_sql()
{
    ////初始化连接
    otl_connect::otl_initialize();
    try
    {
        ////
        // 建立连接，str_login具体看需要连接的数据库是什么，例如postgrepsql，user/pass@dsn
        // 开启自动提交，在otl头文件中的otl_connect类中可以看到连接可以设置的功能
        ////
        c.rlogon("str_login");
        c.auto_commit_on();
            
        //// 执行方式1，直接使用函数执行sql语句（通常用于DDL）
        otl_cursor::direct_exec(c, "str_sql");
        
        //// 执行方式2，使用流的方式（通常用于DML）
        otl_stream s; //// 使用open，或者是构造函数生成流，参考c++文件流
        s.open(bufsize, str_sql, c); 
        //// bufsize表示缓存多少条数据后执行操作（类似缓冲区）
        //// 这里有一个需要注意的地方，如果说执行的sql语句没有占位符（类似:column<char[xx]>>），
        //// 那么bufsize可能会表示这条sql语句执行bufsize次，而不是缓存后批量插入。
        
        s << idate //// 若为insert，插入数据
        s >> odate //// 若为select，读取数据
    }
    catch(otl_exception& e)
    {
        ////处理异常
    }
    //// 断开连接
    c.logoff();
}

