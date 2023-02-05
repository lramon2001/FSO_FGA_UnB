#include<stdio.h>
#include<stdlib.h>

int comparaArquivos(char *f1, char *f2){
    FILE *file1 = fopen(f1, "rb"), *file2 = fopen(f2, "rb");
    if(!file1 || !file2) return 0;
    int c1, c2;
    do{
        c1 = fgetc(file1); c2 = fgetc(file2);
        if (c1 != c2) {fclose(file1); fclose(file2); return 0;}
    }while(c1 != EOF && c2 != EOF);
    fclose(file1); fclose(file2);
    return 1;
}

int main(int argc, char **argv){
    for(int i=1; i<argc-1; i++)
        for(int j=i+1; j<argc; j++)
            printf("%s %s %s\n", argv[i], argv[j], comparaArquivos(argv[i], argv[j]) ? "iguais" : "diferentes");
    return 0;
}
