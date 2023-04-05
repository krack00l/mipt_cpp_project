#include "SQLdata.h"


class SQLDatabase : public DataBase
{
public:
	const std::string server = "tcp://yourservername.mysql.database.azure.com:3306";
	const std::string username = "username@servername";
	const std::string password = "yourpassword";

	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;

	SQLDatabase()
	{
		try
		{
			driver = get_driver_instance();
			con = driver->connect(server, username, password);
		}
		catch (sql::SQLException e)
		{
			std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
			system("pause");
			exit(1);
		}
		stmt = con->createStatement();
		stmt->execute("DROP TABLE IF EXISTS users");
		stmt->execute("CREATE TABLE users (id VARCHAR(50) PRIMARY KEY, file_path VARCHAR(50), key_path VARCHAR(50));");
		delete stmt;
	}

	bool FindFile_id(std::string id) override
	{}

	std::string FindFile_filename(std::string id) override 
	{}

	void AddFileInfo(std::string id, std::string file_name, std::string file_key)  override 
	{
		pstmt = con->prepareStatement("INSERT INTO users(id, file_path, key_path) VALUES(?,?,&)");
		pstmt->setString(1, id);
		pstmt->setString(2, file_name);
		pstmt->setString(3, file_key);
		pstmt->execute();
		std::cout << "One row inserted." << std::endl;
	}

	void DeleteDataFile_id(std::string id) override 
	{}

	void DeleteDataFile_filename(std::string filename) override 
	{}
};