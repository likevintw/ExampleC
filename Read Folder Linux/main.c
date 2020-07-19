



//Kevin, Read images form a folder
#include <stdio.h>
#include <stdlib.h>
#include <string> // string
#include "string.h" //strcpy, strcat, strcmp, memset
#include <dirent.h>
#include <unistd.h>
#include <vector>

using namespace std;

//Kevin, Read images form a folder
class ReadFolder
{
public:
    vector <string> fileNameList, filePathList;
    char *basePath;
    // vector <string> FileName, FilePath; // with namespace std
    // std::vector <std::string> FileName, FilePath; // without namespace std
    void readFileList(char *basePath);
};

void ReadFolder::readFileList(char *basePath)
{
    DIR *dir;
	struct dirent *ptr;
	char base[1000]; // string buffer
	// Name and Path vector
	// Open folder file
	if ((dir=opendir(basePath)) == NULL)
	{
		perror("Open dir error...");
		exit(1);
	}
	while ((ptr=readdir(dir)) != NULL)
	{
		// current dir OR parrent dir
		if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    
		{
			continue;
		}
		// File name and path
		else if(ptr->d_type == 8) 
		{
            
			strcpy (base, basePath);
			strcat (base, "/");
			strcat (base, ptr->d_name);

			// Show directory 
			//printf("directory: %s\n",basePath);
			// Show file name
			//printf("file: %s\n",ptr->d_name);
			// Show file path
			//printf("path: %s\n",base);

            filePathList.push_back(base);
            fileNameList.push_back(ptr->d_name);
		}   
		// Link File
		else if(ptr->d_type == 10)    
		{
			printf("link File:%s/%s\n",basePath,ptr->d_name);
		}
		// Folder
		else if(ptr->d_type == 4)    
		{
			memset(base,'\0',sizeof(base));
			strcpy(base,basePath);
			strcat(base,"/");
			strcat(base,ptr->d_name);
			readFileList(base);
		}
	}
	closedir(dir);
}




int main() 
{
	char FolderName[20]="LDS_taipei"; // LDS_taipei images
	char *basePath;
	basePath=FolderName;
    ReadFolder test;
	test.readFileList(basePath);

    // Show the Files Name and Path
    //fileNameList, filePathList
    //printf("size fileNameList: %zu\n",test.fileNameList.size()); // %zu unsigned int 32
    //printf("size filePathList: %zu\n",test.filePathList.size());
    //exit(0);
	for (int i(0); i < test.fileNameList.size(); i++)
	{
		//Show the File Name
		//printf("[%d]: %s\n", i + 1, test.fileNameList[i].c_str());
		
		//Show the File Path
		printf("[%d]: %s\n", i + 1, test.filePathList[i].c_str());
	
	}
	
	
	return 0;
}