//Read a Folder 201908291346

/**/
#include <fstream> //printf
#include <vector> //read folder
#include <Windows.h> //read folder, system("PAUSE")

//
//Read a folder
/*
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
    //std::vector<std::string> folderList, fileList;
    std::vector<std::string> WavFileName;
    std::vector<std::string> folderList, WavFilePath;
    std::vector<std::string> fileNmaeCheckResult;
    Read_folder();
    //~Read_folder();
    void StrSplit();
    void GetFileNameListInDir();
    void ReadFolder();
};
Read_folder::Read_folder()
{
}
void Read_folder::StrSplit()
{
    std::string::size_type pos;
    
    //printf("Name: %s\n", str.c_str());
    WavFileName.push_back(str.c_str());
    //filePath.push_back(filename);

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

                /*Setting file type*/
                //Set Search Wav File
                if (("raw" == str || "RAW" == str || "wav" == str || "WAV" == str))
                {
                    filename = FolderName + "/" + filename;
                    WavFilePath.push_back(filename);
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
void Read_folder::ReadFolder()
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
        //    break;
    }
}

void ReadFile(std::string strFileName)
{
    //printf("In the Routine: %s\n", strFileName.c_str());

}
int main()
{
    Read_folder ReadFolder_1;
    ReadFolder_1.FolderName = "test7";
    ReadFolder_1.ReadFolder();
    /**/
    for (int i(0); i < ReadFolder_1.WavFilePath.size(); i++)
    {
        //Show the File Path
        printf("Number: %d File Path: %s\n", i + 1, ReadFolder_1.WavFilePath[i].c_str());
        //Show the File Name
        printf("Number: %d File Name: %s\n", i + 1, ReadFolder_1.WavFileName[i].c_str());
        
        //Read a File
        ReadFile(ReadFolder_1.WavFilePath[i]);
    }
    return 0;
}
