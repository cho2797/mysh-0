#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
void printdir(DIR *mydir, char *name)
{    DIR *a = mydir;
     struct dirent *myfile;
     struct stat mystat;
     int total = 0;    
     while((myfile = readdir(a)) != NULL)
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

};

void printoption_l(DIR *mydir, char *name)
{
     struct dirent *myfile;
     char buf[512];
     struct stat mystat;

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
        printf(" %s ",getpwuid(mystat.st_uid)->pw_name);           printf(" %s ",getgrgid(mystat.st_gid)->gr_name);
        printf("  %d", mystat.st_size);
        strftime(buf2,512,"%Y-%m-%d %H:%M",localtime(&mystat.st_mtime));
        printf(" %s", buf2);
        printf("  %s\n", myfile->d_name);
      }}

}

int main(int argc, char *argv[])
{
  DIR *mydir;
  struct dirent *myfile;
  struct stat mystat; 
  char buf[512];
  char name[512];

  getcwd(name,100); //get location

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
 }//
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
  } //option a
  else if(strcmp(argv[1],"-l")==0)
  {  
     mydir = opendir(name);
     printdir(mydir,name);
     closedir(mydir);

     mydir = opendir(name);
     printoption_l(mydir,name);
     closedir(mydir);
   //option l
  }
  else
  {
   if((mydir = opendir(argv[1]))==NULL)
     {
        if(stat(argv[1],&mystat) == -1)
	 printf("wrong argument is passed \n");
        else
         printf("%s\n",argv[1]);       
     }
   else{
     while((myfile = readdir(mydir)) != NULL)
     {  sprintf(buf, "%s/%s", name, myfile->d_name);
        if((strncmp(myfile->d_name,".",1)==0)||(strncmp(myfile->d_name,"..",2)==0))
            ;
        else
         printf("%s   ", myfile->d_name);
     }
    closedir(mydir);
    printf("\n");
   }
  }//no option, argument is diretocy name or file name
 }
 else if(argc==3)
 { //  .\b [option] [name]
   if(strcmp(argv[1],"-a") == 0)
   { if((mydir = opendir(argv[2]))==NULL)
     {
        if(stat(argv[2],&mystat) == -1)
         printf("wrong argument is passed \n");
        else
         printf("%s\n",argv[2]);       
     }
   else{
     int a=0;
     while((myfile = readdir(mydir)) != NULL)
     {  sprintf(buf, "%s/%s", name, myfile->d_name);
        printf(" %-10s ", myfile->d_name);
        a++;
        if(a!=0 && a%3 ==0)
         printf("\n");
     }
    closedir(mydir);
    printf("\n");
   }
   printf("option is -a\n"); 
   } //when option is -a
   else if(strcmp(argv[1],"-l") == 0)
     {
      if((mydir = opendir(argv[2]))==NULL)
      {
       if(stat(argv[2],&mystat) == -1)
           printf("wrong argument is passed \n");
       else //if file name
       {
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
        printf(" %s ",getpwuid(mystat.st_uid)->pw_name);           printf(" %s ",getgrgid(mystat.st_gid)->gr_name);
        printf("  %d", mystat.st_size);
        strftime(buf2,512,"%Y-%m-%d %H:%M",localtime(&mystat.st_mtime));
        printf(" %s", buf2);
        printf("  %s\n",argv[2]);//different
       }
      }
     else{
      printdir(mydir,argv[2]);
      closedir(mydir);

      mydir = opendir(argv[2]);
      printoption_l(mydir,argv[2]);
      closedir(mydir);
     }//directory
     }
  else
     printf("other options are not supported\n");
   printf("%s\n",argv[2]);
 }
}

