#ifndef SQLdata_H
#define SQLdata_H
#endif // !SQLdata_H
#include "database.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>



class SQLDatabase : public DataBase
{
public:
	const std::string server = "";
	const std::string username = "";
	const std::string password = "";

	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;


	SQLDatabase();

	bool FindFile_id(std::string id) override; // search for a file name by id

	std::string FindFile_filename(std::string id) override; // search for a file name by filename

	void AddFileInfo(std::string id, std::string file_name, std::string file_key)  override; // adding file information

	void DeleteDataFile_id(std::string id) override; // deleting a file entry by id

	void DeleteDataFile_filename(std::string filename) override; // deleting a file entry by filename
};