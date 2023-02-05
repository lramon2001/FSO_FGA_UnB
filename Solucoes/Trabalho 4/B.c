#include <stdio.h>
#include <stdlib.h>

int comparaBytes(char *f1, char *f2){
    FILE *file1 = fopen(f1, "r"), *file2 = fopen(f2, "r");
    if(!file1 || !file2) return 1;
    fseek(file1, 0, SEEK_END); fseek(file2, 0, SEEK_END);
    int size1 = ftell(file1), size2 = ftell(file2);
    rewind(file1); rewind(file2);
    if(size1 != size2) return 1;
    char tmp1, tmp2;
    for(int i=0; i<size1; i++) {
        fread(&tmp1, 1, 1, file1); fread(&tmp2, 1, 1, file2);
        if (tmp1 != tmp2) {
            fclose(file1); fclose(file2);
            return 1;
        }
    }
    fclose(file1); fclose(file2);
    return 0;
}

int main(int argc, char **argv){
    for (int i=1; i < argc; i++)
        for(int j=i+1; j < argc; j++)
            printf("%s %s %s\n", argv[i], argv[j], comparaBytes(argv[i], argv[j]) ? "diferentes" : "iguais");
    return 0;
}
