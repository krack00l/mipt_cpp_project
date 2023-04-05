#ifndef MAPdata_H
#define MAPdata_H
#endif // !MAPdata_H
#include "database.h"
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>


class MAPData : public DataBase
{
private:
	int kaka = 0;
public:
	std::map <std::string, std::string> id_path_data; // id and file path
	std::map <std::string, std::string> id_keys_data; // id and key path
	std::string folder_files; // the path to the folder where all files are stored
	std::string folder_keys; // the path to the folder where the keys are stored
	std::string file_backup; // the path to the file where the backup is saved

	MAPData();

	bool FindFile_id(std::string id) override;

	std::string FindFile_filename(std::string id) override;

	void AddFileInfo(std::string id, std::string file_name, std::string file_key) override;

	void DeleteDataFile_id(std::string id) override;

	void DeleteDataFile_filename(std::string filename) override;

	void download();

	void backup();

	~MAPData();
};