/*
 *
 * (C) 2013-16 - ntop.org
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#ifndef _MYSQL_DB_CLASS_H_
#define _MYSQL_DB_CLASS_H_

#include "ntop_includes.h"

class MySQLDB : public DB {
 private:
  MYSQL mysql;
  bool db_operational;
  static volatile bool db_created;
  pthread_t queryThreadLoop;

  bool connectToDB(MYSQL *conn, bool select_db);
  char* get_last_db_error(MYSQL *conn) { return((char*)mysql_error(conn)); }
  char* get_insert_into_values(IPVersion vers);
  int insert_batch(MYSQL *conn, IPVersion vers);
  int exec_sql_query(MYSQL *conn, char *sql, bool doReconnect = true, bool ignoreErrors = false, bool doLock = true);

 public:
  MySQLDB(NetworkInterface *_iface = NULL);
  ~MySQLDB();

  void* queryLoop();
  bool createDBSchema();
  static volatile bool isDbCreated() {return db_created;};
  bool dumpFlow(time_t when, bool partial_dump, Flow *f, char *json);
  int exec_sql_query(lua_State *vm, char *sql, bool limitRows);
  void startDBLoop();
  bool select_hosts(char *iface, vector<vector<string> >& strVec);
};

#endif /* _MYSQL_DB_CLASS_H_ */
