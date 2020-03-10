

//Read a Folder A1 201908060947

/**/
#include <fstream> //printf
#include <vector> //read folder
#include <Windows.h> //read folder, system("PAUSE")

#define PI 3.14159
#define angle2radian 57.29


//
//Read a folder
/*
Include:
<vector>

input:
FolderName
Setting file type //the default is .wav

output:
folderList
fileList
folderList.size()
fileList.size()

*/
class Read_folder
{
public:
	std::string FolderName;
	std::string str, pattern, filename;
	std::vector<std::string> folderList, fileList;
	std::vector<std::string> fileNmaeCheckResult;
	Read_folder();
	//~Read_folder();
	void StrSplit();
	void GetFileNameListInDir();
	void main();
};
Read_folder::Read_folder()
{
}
void Read_folder::StrSplit()
{
	std::string::size_type pos;

	str = str + pattern;

	for (int i = 0; i < str.size(); i++)
	{
		pos = str.find(pattern, i);
		if (pos < str.size())
		{
			std::string s = str.substr(i, pos - 1);
			if (s.length() > 1)
			{
				s = s.substr(0, s.length() - 1);
			}

			if (i > 0)
			{
				fileNmaeCheckResult.push_back(s);
			}
			i = pos + pattern.size() - 1;
		}
	}

}
void Read_folder::GetFileNameListInDir()
{
	short buffer1(0);
	//windows x64
	std::string search_path = FolderName + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) //is fd not a folder? (is file)
			{
				filename = fd.cFileName;// FindFileData.cFileName;
				//For StrSplit()
				str = filename;
				pattern = ".";
				StrSplit();
				str = fileNmaeCheckResult[fileNmaeCheckResult.size() - 1];

				//
				/*Setting file type*/
				if (("raw" == str || "RAW" == str || "wav" == str || "WAV" == str))
				{

					filename = FolderName + "/" + filename;
					fileList.push_back(filename);
				}

				//nameList.push_back(fd.cFileName);


			}
			else //detecting the names of folder
			{

				//test 20190619
				filename = fd.cFileName;// FindFileData.cFileName;
				filename = FolderName + "/" + filename;
				//std::cout << vecImages.size() << std::endl;
				//folderList.push_back(filename);
				//printf("%s\n", fd.cFileName);
				if (buffer1 < 2)
				{
					buffer1++;
				}
				else
				{
					folderList.push_back(filename);
					//folderNumber++;
				}

			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}

	//return nameList;
}
void Read_folder::main()
{
	//int allFolderNumber(0);

	for (int i(0);; i++)
	{
		if (i == 0)
		{
			folderList.push_back(FolderName);
			//printf("%s\n", folderList[i].c_str());
			FolderName = folderList[0];
			GetFileNameListInDir();
			//printf("%s\n", folderList[i].c_str());
		}
		else
		{
			FolderName = folderList[i];
			GetFileNameListInDir();
			//printf("%s\n", folderList[i].c_str());
		}
		//allFolderNumber =allFolderNumber + folderNumber; 
		//allFileNumber = allFileNumber + fileNumber;
		//printf("%d %d\n", i,folderList.size());
		if (i == folderList.size() - 1)  // After read the last folder
			break;
		//if (i == allFolderNumber)  // After read the last folder 
		//	break;
	}
}


void ReadFolder(std::string strFileName)
{
	printf("In the Routine: %s\n", strFileName.c_str());
	
}
int main()
{
	Read_folder read1;
	read1.FolderName = "T3T4 A3";
	read1.main();
	/**/
	for (int i(0); i < read1.fileList.size(); i++)
	{
		printf("In the Main, Number:%d Name:%s\n", i+1, read1.fileList[i].c_str());
		ReadFolder(read1.fileList[i]);
		printf("\n");
	}
	return 0;
}


