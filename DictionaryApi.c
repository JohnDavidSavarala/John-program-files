// Print the meaning of a given word

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDLENGTH 50
#define MAXURLLENGTH 100
#define MAXDEFINITIONLENGTH 200
#define MAXAUDIOURLLENGTH 200

char  *audioUrl, word[MAXWORDLENGTH], *definition;
FILE *fp_dictionary;
int dictonaryFileSize;
void playPronunciation(char *);
char* getDefinition(char *);
char* getAudioUrl(char *);

void main()
{

	char url[MAXURLLENGTH];
    while (1)
    {
        printf("Enter '0' to exit.\n");
        printf("Printing the meaning of given word.\n");
    	printf("Enter a word: ");
    	scanf("%s", word);

        if (strcmp(word, "0") == 0)
        {
            exit(0);
        }

    	sprintf(url, "%s%s%s", "curl -s \"https://api.dictionaryapi.dev/api/v2/entries/en/", word, "\" > dictionaryApi.txt");
    	system(url);

    	fp_dictionary = fopen("dictionaryApi.txt", "r");
    	fseek(fp_dictionary, 0, SEEK_END);
    	dictonaryFileSize = ftell(fp_dictionary);
    	fseek(fp_dictionary, 0, SEEK_SET);
    	char dictionaryApi[dictonaryFileSize];
    	fgets(dictionaryApi, sizeof(dictionaryApi), fp_dictionary);

    	definition = malloc(MAXDEFINITIONLENGTH);
    	definition = getDefinition(dictionaryApi);
        
    	if (strcmp(definition, "Not found") == 0)
    	{
    		printf("%s not found in the dictionary.\n", word);
    	}
    	else
    	{
    		printf("\nDefinition of %s: %s\n", word, definition);
    	}

    	fseek(fp_dictionary, 0, SEEK_SET);
    	fgets(dictionaryApi, dictonaryFileSize, fp_dictionary);
    	audioUrl = malloc(MAXAUDIOURLLENGTH);
    	audioUrl = getAudioUrl(dictionaryApi);
    	if (strcmp(audioUrl, "Not found") == 0)
    	{
    		printf("%s pronunciation not found in the dictionary.\n", word);
    	}
    	else
    	{
    		playPronunciation(audioUrl);
    	}
    }
	fclose(fp_dictionary);
}

char* getAudioUrl(char *dictionaryApi)
{
	int isAudioFound = 0;
	strcpy(audioUrl, "Not found");

    char *token = strtok(dictionaryApi, "\"");
    while (token != NULL) 
    {
        if (strcmp(token, "audio") == 0) 
        {
            token = strtok(NULL, "\"");
            token = strtok(NULL, "\"");
            strcpy(audioUrl, token);
            if (strlen(audioUrl) < 10) 
            {
                token = strtok(NULL, "\"");
	            isAudioFound = 1;
                continue;
            } 
            else 
            {
                isAudioFound = 0;
                break;
            }
        }
        token = strtok(NULL, "\"");
    }
    if (isAudioFound == 1)
    {
    	fseek(fp_dictionary, 0, SEEK_SET);
		fgets(dictionaryApi, dictonaryFileSize, fp_dictionary);
        char *token = strtok(dictionaryApi, ":");
        while (token != NULL) 
        {
            if (strcmp(token, "[{\"audio\"") == 0) 
            {
                token = strtok(NULL, "\"");
                strcpy(audioUrl, token);
                break;
            }
            token = strtok(NULL, ":");
        }
    }
    return audioUrl;
}

char* getDefinition(char *dictionaryApi)
{
	strcpy(definition, "Not found");
	char *token = (char *)strtok(dictionaryApi, ":");
    while (token != NULL) 
    {
        if (strcmp(token, "[{\"definition\"") == 0) 
        {
            token = strtok(NULL, ";.");
            strcpy(definition, token);
            break;
        }
        token = strtok(NULL, ":");
    }
    return definition;
}

void playPronunciation(char *audioUrl)
{
    printf("\nPlaying %s pronunciation...\n", word);
    char playCommand[MAXURLLENGTH];
    sprintf(playCommand, "start %s", audioUrl);
    printf("%s\n", playCommand);
    system(playCommand);
}
