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

  getcwd(name,100); //get location
  //mydir = opendir(argv[1]);
  
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
 {
  if(strcmp(argv[1],"-a")== 0)
  {   mydir = opendir(name);
      int a=0; //for print dup3
      while((myfile = readdir(mydir)) != NULL)
      { sprintf(buf, "%s/%s", name, myfile->d_name);
        printf(" %-20s ", myfile->d_name);
        a++;
        if(a!=0 && a%3 ==0)
         printf("\n"); 
      }
  closedir(mydir);
  printf("\n");
  }
  else if(strcmp(argv[1],"-l")==0)
  {  
     int total = 0;
     mydir = opendir(name);
     while((myfile = readdir(mydir)) != NULL)
     {
       char buf3[512];
       sprintf(buf3, "%s/%s", name, myfile->d_name);
        if((strncmp(myfile->d_name,".",1)==0)||(strncmp(myfile->d_name,"..",2)==0))
            ;
        else{
        stat(buf3, &mystat);
        total = (mystat.st_blocks/2) + total; //
        }
     }
     printf("total : %d\n",total);
     closedir(mydir);

     mydir = opendir(name);
     while((myfile = readdir(mydir)) != NULL)
      { 
        sprintf(buf, "%s/%s", name, myfile->d_name);
        if((strncmp(myfile->d_name,".",1)==0)||(strncmp(myfile->d_name,"..",2)==0))
            ;
        else{    
        stat(buf, &mystat);
        char buf2[512]; //for time
        if(S_ISREG(mystat.st_mode))
             printf("-"); //regular
        else if(S_ISDIR(mystat.st_mode))
              printf("d");//dir
        else if(S_ISCHR(mystat.st_mode))
             printf("c"); //char
        else if(S_ISBLK(mystat.st_mode))
             printf("b");//block
        else if(S_ISFIFO(mystat.st_mode))
             printf("p");//fifo
        else if(S_ISLNK(mystat.st_mode))
             printf("l");//link
        else
             printf("s");//socket
        printf("%s%s%s",(mystat.st_mode & S_IRUSR)?"r":"-",(mystat.st_mode & S_IWUSR)?"w":"-",(mystat.st_mode &S_IXUSR)?"x":"-");
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
   printf("argv[1]:  %s\n",argv[1]);
   if((mydir = opendir(argv[1]))==NULL)
     {
        if(stat(argv[1],&mystat) == -1)
	 printf("wrong argument is passed \n");
        else
         printf("%s\n",argv[1]);       
     }
   else{
   while((myfile = readdir(mydir)) != NULL)
   {    sprintf(buf, "%s/%s", name, myfile->d_name);
        if((strncmp(myfile->d_name,".",1)==0)||(strncmp(myfile->d_name,"..",2)==0))
            ;
        else
         printf("%s   ", myfile->d_name);
   }
  closedir(mydir);
  printf("\n");
   }//else
   //file or directory name
  }//else about argc

 }
 else if(argc==2)
 {
  





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

