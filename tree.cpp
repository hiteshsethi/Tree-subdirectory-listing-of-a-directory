//Developed By : Hitesh Sethi 18th Oct,14
//updation . .. ko hatana ha
#include <iostream>
#include <vector>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
using namespace std;
int getDirec (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "There is a error :(" << errno << ") somewhere " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}
static int direcNum=0;
static int fileNum=0;
int listing(string dir,int space)
{
     vector<string> files = vector<string>();
    getDirec(dir,files);

    for (unsigned int i = 0;i < files.size();i++) {
      if(files[i].find(".")!=-1)//checking if its a normal file
      {
          //its a normal file
          if(files[i].compare(".")>0 and files[i].compare("..")>0)
          {

          for(unsigned int k=0;k<space;k++)
          {
              cout<<" ";
          }
          cout << " |--  "<< files[i] << endl;
          fileNum++;
          }
      }
      else
      {
          //its a directory
          cout << " |--  "<< files[i] << endl;
          direcNum++;
            //recurrence for sub-directories
          listing(files[i],space+6);
      }
    }
    files.clear();
}
int main(int argc, char* argv[])
{
    if(argc>1)
    {
        if(strcmp(argv[1],".")==0)
        {
            if(argv[2]!=NULL)
            {

            string dir=string(argv[2]);
            cout<<dir<<endl;
            listing(dir,2);
            }
            else
            {
                string dir = string(".");
                cout<<dir<<endl;
                listing(dir,2);
            }
        }
    }
    else
    {
        string dir = string(".");
        cout<<dir<<endl;
        listing(dir,2);
    }
    cout<<endl<<direcNum<<" Directories and "<<fileNum<<" files."<<endl;
    return 0;
}
