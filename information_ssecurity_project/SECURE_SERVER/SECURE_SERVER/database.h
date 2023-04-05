#ifndef database_H
#define database_H
#endif // !database_H
#include <string>


// virtual class describing the basic functionality of the database in operation
class DataBase
{
public:
	virtual bool FindFile_id(std::string id) = 0; // search for a file name by id
	virtual std::string FindFile_filename(std::string id) = 0; // search for a file name by filename
	virtual void AddFileInfo(std::string id, std::string file_name, std::string file_key) = 0; // adding file information
	virtual void DeleteDataFile_id(std::string id) = 0; // deleting a file entry by id
	virtual void DeleteDataFile_filename(std::string filename) = 0; // deleting a file entry by filename
};