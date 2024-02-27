#ifndef _Mysqlconn_
#define _Mysqlconn_
#include <iostream>
#include "include/mysql.h"
using namespace std;
class Mysqlconn
{
public:
  // 初始化连接
  Mysqlconn();
  // 释放连接
  ~Mysqlconn();
  // 连接数据库
  bool connect(string user, string passwd, string dbName, string ip, unsigned int port = 3306);
  // 更新数据库
  bool update(string sql);
  // 查询数据库
  bool query(string sql);
  // 遍历结果集
  bool next();
  // 获取字段名
  string value(int index);
  // 开启事务
  bool transaction();
  // 提交事务
  bool commit();
  // 回滚事务
  bool rollback();

private:
  void freeResult();
  MYSQL *m_conn = nullptr;
  MYSQL_RES *m_result = nullptr;
  MYSQL_ROW m_row = nullptr;
};
#endif