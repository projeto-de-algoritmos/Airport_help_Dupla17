#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    float x;
    float y;
    char name[100];
} Airport;

double calculateDistance(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

void findNearestAirport(Airport* airports, int numAirports, float myX, float myY) {
    double minDistance = -1;
    int closestAirportIndex = -1;
    int i;
    
    for (i = 0; i < numAirports; i++) {
        double distance = calculateDistance(myX, myY, airports[i].x, airports[i].y);
        if (minDistance == -1 || distance < minDistance) {
            minDistance = distance;
            closestAirportIndex = i;
        }
    }
    
    if (closestAirportIndex != -1) {
        printf("Nome do Aeroporto: %s\n", airports[closestAirportIndex].name);
        printf("Distancia: %.2f\n Km", minDistance*100);
    }
    else {
        printf("No airports found.\n");
    }
}

int main() {
    FILE* file = fopen("./Airports.csv", "r");
    if (file == NULL) {
        printf("Failed to open the CSV file.\n");
        return 1;
    }
    
    int numAirports = 0;
    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) {
        numAirports++;
    }
    
    Airport* airports = malloc(numAirports * sizeof(Airport));
    if (airports == NULL) {
        printf("Failed to allocate memory.\n");
        return 1;
    }
    
    fseek(file, 0, SEEK_SET);
    
    int airportIndex = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char* token = strtok(line, ",");
        airports[airportIndex].x = atof(token);
        
        token = strtok(NULL, ",");
        airports[airportIndex].y = atof(token);
        
        token = strtok(NULL, ",");
        strncpy(airports[airportIndex].name, token, sizeof(airports[airportIndex].name));
        
        airportIndex++;
    }
    
    fclose(file);
    
    // Assuming your location is (myX, myY)
    float myX = 10.5;
    float myY = 20.7;
    
    findNearestAirport(airports, numAirports, myX, myY);
    
    free(airports);
    
    return 0;
}
