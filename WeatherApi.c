// Print the temperature of given city

#include <stdio.h>
#include <string.h>

#define MAXWEATHERURLLENGTH 200
#define MAXCITYNAMELENGTH 50

FILE *fp_weather;

void main()
{
    char weatherUrl[MAXWEATHERURLLENGTH], city[MAXCITYNAMELENGTH];
    int isCityFound = 0;

    printf("Printing the temperature of a given city.\n");

    printf("Enter city name: ");
    scanf("%s", city);
    
    sprintf(weatherUrl, "%s%s%s","curl \"https://api.openweathermap.org/data/2.5/weather?q=", city , "&appid=abe3a0f4d0b6cebfbe7393b4b4e3aa28&units=metric\" > weather.txt");
    
    printf("%s\n", weatherUrl);
    
    system(weatherUrl);

    fp_weather = fopen("weather.txt", "r");

    fseek(fp_weather, 0, SEEK_END);

    long fileSize = ftell(fp_weather);
    
    char weatherData[fileSize];
    
    fseek(fp_weather, 0, SEEK_SET);

    while (fgets(weatherData, sizeof(weatherData), fp_weather) != NULL) 
    {
        isCityFound = 1;

        char *token = strtok(weatherData, "\"");

        while (token != NULL) 
        {
            if (strcmp(token, "temp") == 0) 
            {
                token = strtok(NULL, "\"");
                printf("Temperature: %s °C\n", token);
                break;
            }
            token = strtok(NULL, "\"");
        }
    }

    if (isCityFound == 0)
    {
        printf("%s city not found.\n", city);
    }

    fclose(fp_weather);

}
