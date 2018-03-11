#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
int main(int argc, char *argv[])
{
  DIR *mydir;
  struct dirent *myfile;
  struct stat mystat;
  
  char buf[512];
  char name[512];

  getcwd(name,100);
  //mydir = opendir(argv[1]);
  //printf("name: %s\n",name);
  
 if(argc==1) //basic
 {
  mydir = opendir(name);
  while((myfile = readdir(mydir)) != NULL)
  {     sprintf(buf, "%s/%s", name, myfile->d_name);
 	if((strncmp(myfile->d_name,".",1)==0)||(strncmp(myfile->d_name,"..",2)==0))
	    ;
        else
         printf("%s   ", myfile->d_name);
  }
  closedir(mydir);
  printf("\n");
 }// command     .\b 
 else if(argc ==2)
 {printf("argc is 2\n");
  printf("argv[1] is %s\n",argv[1]);
  if(strcmp(argv[1],"-a")== 0)
  {   printf("option -a\n");
      mydir = opendir(name);
      while((myfile = readdir(mydir)) != NULL)
      { sprintf(buf, "%s/%s", name, myfile->d_name);
        printf("%s    ", myfile->d_name);
      }
  closedir(mydir);
  printf("\n");
  }
  else if(strcmp(argv[1],"-l")==0)
  {  printf("option -l\n");
     mydir = opendir(name);
     while((myfile = readdir(mydir)) != NULL)
      { 
        sprintf(buf, "%s/%s", name, myfile->d_name);
        if((strncmp(myfile->d_name,".",1)==0)||(strncmp(myfile->d_name,"..",2)==0))
            ;
        else{    
        stat(buf, &mystat);
        char buf2[512];
        printf("%s%s%s",(mystat.st_mode & S_IRUSR)?"r":"-",(mystat.st_mode & S_IWUSR)?"w":"-",(mystat.st_mode &S_IXUSR)?"xi":"-");
	printf("%s%s%s",(mystat.st_mode & S_IRGRP)?"r":"-",(mystat.st_mode & S_IWGRP)?"w":"-",(mystat.st_mode &S_IXGRP)?"x":"-");
	printf("%s%s%s",(mystat.st_mode & S_IROTH)?"r":"-",(mystat.st_mode & S_IWOTH)?"w":"-",(mystat.st_mode &S_IXOTH)?"x":"-");
        
     
        printf(" %d ", mystat.st_nlink);
        printf(" %s ",getpwuid(mystat.st_uid)->pw_name);     
        printf(" %s ",getgrgid(mystat.st_gid)->gr_name);
        printf("  %d", mystat.st_size);
       // printf("  %s", ctime(&mystat.st_mtime));
        strftime(buf2,512,"%Y-%M-%d %H:%M",localtime(&mystat.st_mtime));
        printf(" %s", buf2);

        printf("  %s\n", myfile->d_name);
      }}
      closedir(mydir);
  }
  else
  {
   //file or directory name
  }

 }
 /*
  while((myfile = readdir(mydir)) != NULL)
  {     sprintf(buf, "%s/%s", name, myfile->d_name);
	stat(buf, &mystat);
	
        printf("%d", mystat.st_size);
        printf("  %s", ctime(&mystat.st_atime));
	printf("  %s\n", myfile->d_name);

  }
  closedir(mydir);
*/
}

