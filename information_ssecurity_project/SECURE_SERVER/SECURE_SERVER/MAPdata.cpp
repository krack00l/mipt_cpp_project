#include "MAPdata.h"


class MAPData : public DataBase
{
private:
	int kaka = 0;
public:
	std::map <std::string, std::string> id_path_data;
	std::map <std::string, std::string> id_keys_data;
	std::string folder_files; 
	std::string folder_keys; 
	std::string file_backup; 

	MAPData()
	{
		this->folder_files = "C:\\Project\\DataBase_keys\\";
		this->folder_keys = "C:\\Project\\DataBase_data\\";
		this->file_backup = "C:\\Project\\backup.txt";
	}

	bool FindFile_id(std::string id) override
	{
		std::map <std::string, std::string>::iterator it = id_path_data.find(id);
		if (it == id_path_data.end())
			return false;
		return true;
	}

	std::string FindFile_filename(std::string id) override
	{
		std::map <std::string, std::string>::iterator it = id_path_data.find(id);
		if (it == id_path_data.end())
			return "";
		return it->second;
	}

	void AddFileInfo(std::string id, std::string file_name, std::string file_key) 
	{
		this->id_path_data.insert(std::make_pair(id, this->folder_files + file_name));
		this->id_keys_data.insert(std::make_pair(id, this->folder_keys + file_key));
	}

	void DeleteDataFile_id(std::string id)
	{
		if (FindFile_id(id))
		{
			std::map <std::string, std::string>::iterator it_files = this->id_path_data.find(id);
			std::map <std::string, std::string>::iterator it_keys = this->id_keys_data.find(id);
			this->id_path_data.erase(it_files);
			this->id_keys_data.erase(it_keys);
		}
		else
		{
			std::cout << "file already delete" << std::endl;
		}
	}

	void DeleteDataFile_filename(std::string filename) 
	{

	}

	void download() // loading data from backup
	{
		std::fstream file;
		file.open(this->file_backup, std::ios::in | std::ios::binary);
		while (!file.eof())
		{
			std::string buff[3];
			for (int i = 0; i <= 3; i++)
				file >> buff[i];
			this->id_path_data.insert(std::make_pair(buff[0], this->folder_files + buff[1]));
			this->id_keys_data.insert(std::make_pair(buff[0], this->folder_keys + buff[2]));
		}
		std::cout << "poka tak download data" << std::endl;
	}

	void backup() // saving data when the server is turned off
	{
		std::map <std::string, std::string>::iterator it_file = this->id_path_data.begin(); 
		std::map <std::string, std::string>::iterator it_key = this->id_keys_data.begin(); 
		std::fstream file;
		file.open(this->file_backup, std::ios_base::out | std::ios_base::binary);
		for (int i = 0; it_file != id_path_data.end(); i++, it_file++, it_key++)
		{
			std::string buff;
			buff = it_file->first + " " + it_file->second + " " + it_key->second + "\n";
			file.write(buff.c_str(), buff.size());
		}
		std::cout << "poka tak backup data" << std::endl;
	}

	~MAPData()
	{
		std::cout << "poka tak descriptor" << std::endl;
	}
};