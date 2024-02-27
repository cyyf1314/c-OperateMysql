#include "Mysqlconn.h"

Mysqlconn::Mysqlconn()
{
  m_conn = mysql_init(nullptr);
  mysql_set_character_set(m_conn, "utf8");
}

Mysqlconn::~Mysqlconn()
{
  // 判断是否连接成功，如果没有成功会造成重复释放
  if (m_conn != nullptr)
  {
    mysql_close(m_conn);
  }
  freeResult();
}

bool Mysqlconn::connect(string user, string passwd, string dbName, string ip, unsigned int port)
{

  MYSQL *ptr = mysql_real_connect(m_conn, ip.c_str(), user.c_str(), passwd.c_str(), dbName.c_str(), port, nullptr, 0);
  return ptr != nullptr;
}

bool Mysqlconn::update(string sql)
{
  if (mysql_query(m_conn, sql.c_str()))
  {
    return false;
  }
  return true;
}

bool Mysqlconn::query(string sql)
{
  freeResult();
  if (mysql_query(m_conn, sql.c_str()))
  {
    return false;
  }
  m_result = mysql_store_result(m_conn);
  return true;
}

bool Mysqlconn::next()
{
  if (m_result != nullptr)
  {
    m_row = mysql_fetch_row(m_result);
  }
  return false;
}

string Mysqlconn::value(int index)
{
  int rowCount = mysql_num_fields(m_result);
  if (index >= rowCount || index < 0)
  {
    return string();
  }
  char *val = m_row[index];
  unsigned long length = mysql_fetch_lengths(m_result)[index];
  return string(val, length);
}

bool Mysqlconn::transaction()
{
  return mysql_autocommit(m_conn, false);
}

bool Mysqlconn::commit()
{
  return mysql_commit(m_conn);
}

bool Mysqlconn::rollback()
{
  return mysql_rollback(m_conn);
}

void Mysqlconn::freeResult()
{
  if (m_result)
  {
    mysql_free_result(m_result);
    m_result = nullptr;
  }
}

int main()
{
  cout << "n" << endl;
  system("pause");
  return 0;
}