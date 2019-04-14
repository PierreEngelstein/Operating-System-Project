#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define bool char
#define true 1
#define false 0
#define MaxLine 128
#define CONFIG 0

typedef struct
{
        char fileInput[100];        // The file to be compiled
        char fileOutput[100];       // The output file of the compilation
        char compiler[100];         // The compiler to be used
        char options[100];          // What options will be used for the compilation
        char includes[100];         // Where are the includes located
}TBuild;

typedef struct
{
        bool clean_after_compile;
        char *build_options;
        char *linker_options;
        char *bin_folder;
        char *includes;
        char *main_output;
        char *output_kernel;
}options;

typedef struct
{
        TBuild *ListOfOut;
        int listSize;
        char *outputFile;
}LinkList;

void Command(char *command, bool warnings);
void BuildFile(char *fileIn, char *fileOut, char *type, char **config);
int AddToLink(LinkList *list, TBuild buildFile);
int CreateLink(LinkList *list, const char *outputFile);
int CreateBuildFile(TBuild *build, const char *fileIn, const char *fileOut, const char *compiler, const char *options, const char *includes);

int main(int argc, char **argv)
{
        if(argc != 2)
        {
                printf("please indicate what build file you are using !\n");
                return 0;
        }
        FILE *file = fopen(argv[1], "r");
        if(file == NULL)
        {
                printf("Failed to read input file !\n");
                return 0;
        }
        printf("Using %s as build file\n", argv[1]);

        TBuild buildTest;
        int res = CreateBuildFile(&buildTest, "testFileIn", "testFileOut", "gcc", " -Wall", "src/includes");
        if(res == -1)
        {
                printf("Error !\n");
                return -1;
        }
        printf("build = '%s'\n", buildTest.compiler);
        char line[MaxLine];
        char type;
        /* Parse each line of the build file */
        while( fgets(line, sizeof(line), file) != NULL)
        {
                if(strstr(line, "[config]"))
                {
                        printf("Configuration section...\n");
                        type = CONFIG;
                        continue;
                }
                else if(strstr(line, "["))
                {
                        printf("File compilation list\n");

                }
        }
        fclose(file);
}

void Command(char *command, bool warnings){}

void BuildFile(char *fileIn, char *fileOut, char *type, char **config){}

int CreateLink(LinkList *list, const char *outputFile)
{
        list = (LinkList *)malloc(sizeof(LinkList));
        if(list == NULL)
                return -1;
        list->ListOfOut = NULL;
        strcpy(list->outputFile, outputFile);
        return 0;
}

int AddToLink(LinkList *list, TBuild buildFile)
{
        list->listSize++;
        list->ListOfOut = (TBuild*)realloc(list->ListOfOut, list->listSize * sizeof(buildFile));
        if(list->ListOfOut == NULL)
                return -1;
        return 0;
}

int CreateBuildFile(TBuild *build, const char *fileIn, const char *fileOut, const char *compiler, const char *options, const char *includes)
{
        build = (TBuild *)malloc(sizeof(TBuild));
        if(build == NULL)
        {
                printf("ah !\n");
                return -1;
        }
        strcpy(build->fileInput, fileIn);
        strcpy(build->fileOutput, fileOut);
        strcpy(build->compiler, compiler);
        strcpy(build->options, options);
        strcpy(build->includes, includes);
        return 0;
}