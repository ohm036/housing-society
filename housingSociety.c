#include <stdio.h>
#include <string.h>
#define building hS[(*lastBlankPos)].bd

//Housing Society is an array of spaces
//A space can be a type of building such as an apartment, a school, a park or a hospital
//Each type of building has its own struct of necessary info together
//Each instance of apartment or others are a struct with floors and other info
//Floors is an array of floor structs containing info about each floor

struct Space {
    //Apartment = 1, School = 2, Park = 3, Hospital = 4
    int identifier; 
    double size;

    struct Floor {
            int items; //How many types in a particular floor; At most 4 [Store, Parking, Flat, Office]
            //-100 for Flat, -200 for Store, -300 for Office, -400 for Parking
            double floorSize;
            int types[4];
            double individualSizes[4]; //Size of individual type
        };

    union Building {
        //Internal structures' definitions of the housing society:
        struct Apartment {
            char name[100]; //Prompt and prevent user from inputting more than 100 characters
            char address[200]; //Prompt and prevent user from inputting more than 200 chars
            int numberOfFloors;
            struct Floor floors[20];
        } ap;

        struct School {
            char name[100];
            char address[200];
            int numberOfFloors;
            struct Floor floors[6]; //At most 6 floors 
        } sc;

        struct Park {
            char name[100];
            char address[200];
            int hasKidsPlayground; //1 if yes, 0 if no
            //No floors input for a park
        } pk;

        struct Hospital {
            char name[100];
            char address[200];
            char type[50]; //Cardiac, Orthopedic, General, Diagnostic etc.
            int numberOfFloors;
            struct Floor floors[10]; //At most 10 floors
        } hs;
    } bd;
};

//Function prototypes:
void addApart(struct Space hS[], int * lastBlankPos), addSchool(struct Space hS[], int * lastBlankPos), addPark(struct Space hS[], int * lastBlankPos), addHospital(struct Space hS[], int * lastBlankPos), listItems(char*name, struct Space hS[], int * lastBlankPos), getInfo(char * name, struct Space hS[], int * lastBlankPos), search(char string[], struct Space hS[], int * lastBlankPos), stringInputter(char destination[]), stringInputterBufferClearerVersion(char destination[]);

double currentFloorSizeChecker(double arr[], int limit), sizeLeft(double originalFloorSize, double currentFloorSize);


int main () {
    printf("\t\tWelcome to your Housing Society\n");
    for (int i = 0; i < 70; i++) {
        printf("-");
    }
    printf("\nEnter a name for your Housing Society (At most 100 characters): ");

    char name[100]; //Name of the housing society. At most 100 

    stringInputter(name); //Custom string inputting function to prevent uncertain behaviours of the program

    printf("\nName successfully saved!\n");

    int beginningInput, lastBlankPos = 0;
    struct Space hS[100]; //At most 100 spaces in our housing society. Housing Society to be called hS in short.

    while (1) {
        printf("\n");
        printf("[1] Add a Space\n");
        printf("[2] List Items\n");
        printf("[3] Get Info\n");
        printf("[4] Search for a Building\n");
        printf("[5] Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &beginningInput);

        switch (beginningInput) {
            case 1:
                if (lastBlankPos >= 100) {
                    printf("Sorry, no more space available.\n");
                } else {
                    while (1) {
                        printf("\nWhat type of space do you want to add?\n");
                        printf("[1] Add an Apartment Building\n"); //Max floors: 20
                        printf("[2] Add a School\n"); //Max Floors: 6
                        printf("[3] Add a Park\n"); //No floors
                        printf("[4] Add a Hospital\n"); //Max Floors: 10
                        printf("[5] Go Back\n");
                        printf("Enter your choice: ");
            
                        int caseOneBegInput;
                        scanf("%d", &caseOneBegInput);

                        switch (caseOneBegInput) {
                            case 1:
                            //Initialize all floor array values as -1 and number of floors = 0
                                hS[(lastBlankPos)].bd.ap.numberOfFloors = 0;
                                memset(hS[(lastBlankPos)].bd.ap.floors->individualSizes, 0, sizeof(hS[(lastBlankPos)].bd.ap.floors->individualSizes));
                                memset(hS[(lastBlankPos)].bd.ap.floors->types, -1, sizeof(hS[(lastBlankPos)].bd.ap.floors->types));
                        
                                addApart(hS, &lastBlankPos);
                                break;
                            case 2:
                                hS[(lastBlankPos)].bd.sc.numberOfFloors = 0;
                                memset(hS[(lastBlankPos)].bd.sc.floors, 0, sizeof(hS[(lastBlankPos)].bd.sc.floors));

                                addSchool(hS, &lastBlankPos);
                                break;
                            case 3:
                                addPark(hS, &lastBlankPos);
                                break;
                            case 4:
                                hS[(lastBlankPos)].bd.hs.numberOfFloors = 0;
                                memset(hS[(lastBlankPos)].bd.hs.floors, 0, sizeof(hS[(lastBlankPos)].bd.hs.floors));

                                addHospital(hS, &lastBlankPos);
                                break;
                            case 5:
                                printf("\nGoing back...\n");
                                break;
                            default:
                                printf("\nInvalid input! Taking you back...\n");
                                continue;
                        }

                        break;
                    }
                }
                
                continue;
            case 2:
                listItems(name, hS, &lastBlankPos);
                continue;
            case 3:
                getInfo(name, hS, &lastBlankPos);
                continue;
            case 4:
                printf("Enter a name or address of a building to search for it: ");
                char nameOrAddr[200];
                stringInputterBufferClearerVersion(nameOrAddr);
                search(nameOrAddr, hS, &lastBlankPos);
                continue;
            case 5:
                goto Exit;
                break;
            default:
                printf("Invalid input! Going back...\n");
                continue;
        }

        break; // Exit the loop if a valid choice is made
    }

    Exit:
        printf("\nSuccessfully exited %s\n", name);
        return 0;
}

//Function Definitions:
void addApart(struct Space hS[], int * lastBlankPos) {
    //Required info: identifier, name, address, size, number of floors
    hS[(*lastBlankPos)].identifier = 1;
    printf("\nEnter a name for your apartment (At most 100 characters): \n");

    stringInputterBufferClearerVersion(building.ap.name);

    printf("\nEnter the address of your apartment (At most 200 characters): \n");

    stringInputter(building.ap.address);

    
    printf("\nEnter the size of your apartment in sq. ft.: ");

    double sz;

    scanf("%lf", &sz);

    while (1) {
        if (sz <= 0) {
        //Size can't be zero or less
            printf("\nSize cannot be negative! Please enter again: ");
            scanf("%lf", &sz);
        } else {
            hS[(*lastBlankPos)].size = sz;
            break;
        }
    }

    printf("\nEnter number of floors (At most 20): ");

    int f;

    scanf("%d", &f);

    while (1) {
        if (f <= 20 && f > 0) {
        //At least one floor and not more than 20
            building.ap.numberOfFloors = f;
            break;
        } else {
            printf("\nUnexpected input! Please enter again: ");
            scanf("%d", &f);
        }
    }


    //i is the floor iterator
    //j is types and individualSizes iterator
    for (int i = 0; i < f; i++) {
        printf("\nEnter floor - %d info: \n", i+1);
        
        int floorChoice;

        printf("\nHow many items do you want to have in this floor? Items include flats, stores, offices and parkings. [Max: 4]\n");
        printf("Enter the number of items: ");
        int items;
        scanf("%d", &items);

        while (1) {
            if (items > 0 && items <= 4) {
                break;
            } else {
                printf("Unexpected input. Please enter again: ");
                scanf("%d", &items);
            }
        }

        for (int j = 0; j < items; j++) {
            if (currentFloorSizeChecker(building.ap.floors[i].individualSizes, items) >= sz) {
                //If sum of the sizes of items already exceeds the original apartment size
                break;
            } else {
                int floorExit = 0;
                while (floorExit == 0) {
                    printf("\nAdd item - %d:\n", j+1);
                    printf("[1] Add a Flat\n");
                    printf("[2] Add a Store\n");
                    printf("[3] Add an Office\n");
                    printf("[4] Add a parking\n");
                    printf("Enter your choice: ");

                    scanf("%d", &floorChoice);

                    double sizeOfFlat;

                    if (floorChoice == 1 || floorChoice == 2 || floorChoice == 3 || floorChoice == 4) {
                        switch (floorChoice) {
                            case 1:
                                printf("Enter size of the flat: ");
                                scanf("%lf", &sizeOfFlat);

                                //Filter for negative inputs
                                while (1) {
                                    if ((sizeOfFlat < 0) || (sizeLeft(sz, (currentFloorSizeChecker(building.ap.floors[i].individualSizes, items) + sizeOfFlat)) < 0)) {
                                        if (sizeOfFlat < 0) {
                                            printf("Flat size can't be negative! Enter again: ");
                                            scanf("%lf", &sizeOfFlat);
                                        } else {
                                            printf("\nToo big! Enter again: ");
                                            scanf("%lf", &sizeOfFlat);
                                        }
                                    } else {
                                        break;
                                    }
                                }

                                building.ap.floors[i].individualSizes[j] = sizeOfFlat;
                                building.ap.floors[i].types[j] = -100; //-100 for flat type

                                break;
                            case 2:
                                printf("Enter size of the store: ");
                                scanf("%lf", &sizeOfFlat);

                                while (1) {
                                    if ((sizeOfFlat < 0) || (sizeLeft(sz, (currentFloorSizeChecker(building.ap.floors[i].individualSizes, items) + sizeOfFlat)) < 0)) {
                                        if (sizeOfFlat < 0) {
                                            printf("Store size can't be negative! Enter again: ");
                                            scanf("%lf", &sizeOfFlat);
                                        } else {
                                            printf("\nToo big! Enter again: ");
                                            scanf("%lf", &sizeOfFlat);
                                        }
                                    } else {
                                        break;
                                    }
                                }

                                building.ap.floors[i].individualSizes[j] = sizeOfFlat;
                                building.ap.floors[i].types[j] = -200; 

                                break;
                            case 3:
                                printf("Enter size of the office: ");
                                scanf("%lf", &sizeOfFlat);

                                while (1) {
                                    if ((sizeOfFlat < 0) || (sizeLeft(sz, (currentFloorSizeChecker(building.ap.floors[i].individualSizes, items) + sizeOfFlat)) < 0)) {
                                        if (sizeOfFlat < 0) {
                                            printf("Office size can't be negative! Enter again: ");
                                            scanf("%lf", &sizeOfFlat);
                                        } else {
                                            printf("\nToo big! Enter again: ");
                                            scanf("%lf", &sizeOfFlat);
                                        }
                                    } else {
                                        break;
                                    }
                                }

                                building.ap.floors[i].individualSizes[j] = sizeOfFlat;
                                building.ap.floors[i].types[j] = -300; 

                                break;
                            case 4:
                                printf("Enter size of the parking: ");
                                scanf("%lf", &sizeOfFlat);

                                while (1) {
                                    if ((sizeOfFlat < 0) || (sizeLeft(sz, (currentFloorSizeChecker(building.ap.floors[i].individualSizes, items) + sizeOfFlat)) < 0)) {
                                        if (sizeOfFlat < 0) {
                                            printf("Parking size can't be negative! Enter again: ");
                                            scanf("%lf", &sizeOfFlat);
                                        } else {
                                            printf("\nToo big! Enter again: ");
                                            scanf("%lf", &sizeOfFlat);
                                        }
                                    } else {
                                        break;
                                    }
                                }

                                building.ap.floors[i].individualSizes[j] = sizeOfFlat;
                                building.ap.floors[i].types[j] = -400;
                                building.ap.floors->floorSize = currentFloorSizeChecker(building.ap.floors->individualSizes, items); //Store the floor size. It can be smaller than actual space size. Because the user can leave some floor space empty. 

                                break;
                            default:
                                break;
                        }

                        floorExit = 1;
                    } else {
                        printf("Unexpected input. Please enter again: ");
                        scanf("%d", &floorChoice);
                    }
                }
            }
        }
    }

    printf("\nSuccessfully added the apartment: %s\n", building.ap.name);
    (*lastBlankPos) += 1; //Set the new blank position in the housing society array to be the next position
}

void addSchool(struct Space hS[], int * lastBlankPos) {
    hS[(*lastBlankPos)].identifier = 2;
    printf("\nEnter a name for your school (At most 100 characters): \n");

    stringInputterBufferClearerVersion(building.sc.name);

    printf("\nEnter the address of your school (At most 200 characters): \n");

    stringInputter(building.sc.address);

    
    printf("\nEnter the size of your school in sq. ft.: ");

    double sz;

    scanf("%lf", &sz);

    while (1) {
        if (sz <= 0) {
        //Size can't be zero or less
            printf("\nInvalid size. Enter again: ");
            scanf("%lf", &sz);
        } else {
            hS[(*lastBlankPos)].size = sz;
            break;
        }
    }

    printf("\nEnter number of floors (At most 6): ");

    int f;

    scanf("%d", &f);

    while (1) {
        if (f <= 6 && f > 0) {
        //At least one floor and not more than 6
            building.sc.numberOfFloors = f;
            break;
        } else {
            printf("\nInvalid number. Enter again: ");
            scanf("%d", &f);
        }
    }

    printf("Successfully added a school.\n");
    (*lastBlankPos) += 1;
}

void addPark(struct Space hS[], int * lastBlankPos) {
    hS[(*lastBlankPos)].identifier = 3;
    printf("\nEnter a name for your park (At most 100 characters): \n");

    stringInputterBufferClearerVersion(building.pk.name);

    printf("\nEnter the address of your park (At most 200 characters): \n");

    stringInputter(building.pk.address);

    
    printf("\nEnter the size of your park in sq. ft.: ");

    double sz;

    scanf("%lf", &sz);

    while (1) {
        if (sz <= 0) {
        //Size can't be zero or less
            printf("\nInvalid size. Enter again: ");
            scanf("%lf", &sz);
        } else {
            hS[(*lastBlankPos)].size = sz;
            break;
        }
    }

    int kidsPlayGround;
    printf("Does the park have Kids' Playground?\n");
    printf("[1] Yes\n[2] No\nEnter your choice: ");
    scanf("%d", &kidsPlayGround);

    while (1) {
        if (kidsPlayGround == 1 || kidsPlayGround == 2) {
            if (kidsPlayGround == 1) {
                hS[(*lastBlankPos)].bd.pk.hasKidsPlayground = 1;
                printf("\nSaved the information.\n");
                break;
            } else {
                hS[(*lastBlankPos)].bd.pk.hasKidsPlayground = 0;
                printf("\nSaved the information.\n");
                break;
            }
        } else {
            printf("Unexpected input!\nDoes the park have Kids' Playground?\n");
            printf("[1] Yes\n[2] No\nEnter your choice: ");
            scanf("%d", &kidsPlayGround);
        }
    }

    printf("Successfully added a park.\n");
    (*lastBlankPos) += 1;
}

void addHospital(struct Space hS[], int * lastBlankPos) {
hS[(*lastBlankPos)].identifier = 4;
    printf("\nEnter a name for your hospital (At most 100 characters): \n");

    stringInputterBufferClearerVersion(building.hs.name);

    printf("\nEnter the address of your hospital (At most 200 characters): \n");

    stringInputter(building.hs.address);

    
    printf("\nEnter the size of your hospital in sq. ft.: ");

    double sz;

    scanf("%lf", &sz);

    while (1) {
        if (sz <= 0) {
        //Size can't be zero or less
            printf("\nInvalid size. Enter again: ");
            scanf("%lf", &sz);
        } else {
            hS[(*lastBlankPos)].size = sz;
            break;
        }
    }

    printf("\nWhat does the hospital specializes in? (i.e. General, Cardiac, Orthopedic etc.)\n");
    printf("Enter: ");
    scanf("%s", &hS[(*lastBlankPos)].bd.hs.type);

    printf("\nEnter number of floors (At most 10): ");

    int f;

    scanf("%d", &f);

    while (1) {
        if (f <= 10 && f > 0) {
        //At least one floor and not more than 10
            building.hs.numberOfFloors = f;
            break;
        } else {
            printf("\nInvalid number. Enter again: ");
            scanf("%d", &f);
        }
    }

    printf("Successfully added a hospital.\n");
    (*lastBlankPos) += 1;
}

void listItems(char * name, struct Space hS[], int * lastBlankPos) {
    if ((*lastBlankPos) == 0) {
        printf("\n%s is empty.\n", name);
    } else {
        printf("\nItems of %s\n", name);
        printf("Total number of occupied spaces: %d\n", (*lastBlankPos));

        printf("\tSerial\t\tType\t\t\tName\t\tSize\t\t\tFeatures\n");

        for (int i = 0; i < 100; i++) {
            printf("-");
        }

        printf("\n");

        for (int i = 0; i < (*lastBlankPos); i++) {
            if (hS[i].identifier == 1) {
                printf("\t%d\t\tApartment\t%s\t%.2lf\t\t\tFloor(s): %d\n", i+1, hS[i].bd.ap.name, hS[i].size, hS[i].bd.ap.numberOfFloors);
            } else if (hS[i].identifier == 2) {
                printf("\t%d\t\tSchool\t\t%s\t\t%.2lf\t\t\tFloor(s): %d\n", i+1, hS[i].bd.sc.name, hS[i].size, hS[i].bd.sc.numberOfFloors);
            } else if (hS[i].identifier == 3) {
                if (hS[i].bd.pk.hasKidsPlayground == 0) {
                    printf("\t%d\t\tPark\t\t\t%s\t\t%.2lf\t\t\tIncludes Kids' Playground\n", i+1, hS[i].bd.pk.name, hS[i].size);
                } else if (hS[i].bd.pk.hasKidsPlayground == 1) {
                    printf("\t%d\t\tPark\t\t%s\t\t%.2lf\t\t\tNo Kids' Playground\n", i+1, hS[i].bd.pk.name, hS[i].size);
                }
            } else if (hS[i].identifier == 4) {
                printf("\t%d\t\tHospital\t%s\t\t%lf\t\t%s\n", i+1, hS[i].bd.hs.name, hS[i].size, hS[i].bd.hs.type);
            }
        }
    }
}

void getInfo(char * name, struct Space hS[], int * lastBlankPos) {
    if ((*lastBlankPos) == 0) {
        printf("\n%s is empty.\n", name);
    } else {
        int aparts = 0, schools = 0, hospitals = 0, parks = 0;
        double totalApSize = 0, totalScSize = 0, totalPkSize = 0, totalHsSize = 0, totalHousingSize = 0;
        float percent1 = 0, percent2 = 0, percent3 = 0, percent4 = 0;
        
        for (int i = 0; i <= (*lastBlankPos); i++) {
            if (hS[i].identifier == 1) {
                aparts += 1;
                totalApSize += hS[i].size;
                totalHousingSize += hS[i].size;
            } else if (hS[i].identifier == 2) {
                schools += 1;
                totalScSize += hS[i].size;
                totalHousingSize += hS[i].size;
            } else if (hS[i].identifier == 3) {
                parks += 1;
                totalPkSize += hS[i].size;
                totalHousingSize += hS[i].size;
            } else if (hS[i].identifier == 4) {
                hospitals += 1;
                totalHsSize += hS[i].size;
                totalHousingSize += hS[i].size;
            }
        }

        if (totalApSize > 0) {
            percent1 = (totalApSize/totalHousingSize) * 100;
        }

        if (totalScSize > 0) {
            percent2 = (totalScSize/totalHousingSize) * 100;
        }

        if (totalPkSize > 0) {
            percent3 = (totalPkSize/totalHousingSize) * 100;
        }

        if (totalHsSize > 0) {
            percent4 = (totalHsSize/totalHousingSize) * 100;
        }

        printf("\nHousing Society Name: %s\n", name);
        printf("Total size: %.2lf\n", totalHousingSize); //%lf for long double
        printf("Occupied spaces: %d\n", (*lastBlankPos));

        printf("Apartments:\n");
        printf("Total number of apartments: %d\n", aparts);
        printf("Total size of apartments: %.2lf (%.2f percent)\n", totalApSize, percent1);
        //More to add about individual apartments

        printf("Schools:\n");
        printf("Total number of schools: %d\n", schools);
        printf("Total size of schools: %.2lf (%.2f percent)\n", totalScSize, percent2);

        printf("Parks:\n");
        printf("Total number of parks: %d\n", parks);
        printf("Total size of parks: %.2lf (%.2f percent)\n", totalPkSize, percent3);

        printf("Hospitals:\n");
        printf("Total number of hospitals: %d\n", hospitals);
        printf("Total size of hospitals: %.2lf (%.2f percent)\n", totalHsSize, percent4);
    
    }
}

void search(char string[], struct Space hS[], int * lastBlankPos) {
    int atLeastOneMatchFound = 0;

    for (int i = 0; i <= (*lastBlankPos); i++) {

    //If ientifier matches to certain value search accordingly in the union members. For identifier-1, apartment struct of the building union is active, if identifier is 2, then school struct is active and so on. Thus check for matches in respective name or address fields.
    
        if (hS[i].identifier == 1 && (strcmp(hS[i].bd.ap.name, string) == 0 || strcmp(hS[i].bd.ap.address, string) == 0)) {
            printf("\nAn apartment named %s was found at the address: %s\nIt is in Space - %d of the housing society\n", hS[i].bd.ap.name, hS[i].bd.ap.address, i+1);
            atLeastOneMatchFound = 1;
        } else if (hS[i].identifier == 2 && (strcmp(hS[i].bd.sc.name, string) == 0 || strcmp(hS[i].bd.sc.address, string) == 0)) {
            printf("\nA school named %s was found at the address: %s\nIt is in Space - %d of the housing society\n", hS[i].bd.sc.name, hS[i].bd.sc.address, i+1);
            atLeastOneMatchFound = 1;
        } else if (hS[i].identifier == 3 && (strcmp(hS[i].bd.pk.name, string) == 0 || strcmp(hS[i].bd.pk.address, string) == 0)) {
            printf("\nA park named %s was found at the address: %s\nIt is in Space - %d of the housing society\n", hS[i].bd.pk.name, hS[i].bd.pk.address, i+1);
            atLeastOneMatchFound = 1;
        } else if (hS[i].identifier == 4 && (strcmp(hS[i].bd.hs.name, string) == 0 || strcmp(hS[i].bd.hs.address, string) == 0)) {
            printf("\nA hospital named %s was found at the address: %s\nIt is in Space - %d of the housing society\n", hS[i].bd.hs.name, hS[i].bd.hs.address, i+1);
            atLeastOneMatchFound = 1;
        }
    }

    //If the program finishes the for loop with atLeastOneMatchFound = 0, that means no results were found.
    if (atLeastOneMatchFound == 0) {
        printf("\n\nNo results found!\n");
        return;
    }
}

double currentFloorSizeChecker(double arr[], int limit) {
    double totalSize = 0;

    for (int i = 0; i < limit; i++) {
        totalSize += arr[i];
    }

    return totalSize;
}

double sizeLeft(double originalFloorSize, double currentFloorSize) {
    return originalFloorSize - currentFloorSize;
}

void stringInputter(char destination[]) {
    char ch;
    int it;

    for (it = 0; it < 99; it++) {
        ch = getchar();
        if (ch == '\n' && it == 0) {
            while (ch == '\n') {
                printf("This field cannot be blank! Enter again: ");
                ch = getchar();
            }
        } else if (ch == '\n') {
            break;
        } else {
            destination[it] = ch;
        }
    }

    destination[it] = '\0';
}

void stringInputterBufferClearerVersion(char destination[]) {
    char ch;
    int it;

    while ((ch = getchar()) != '\n');

    for (it = 0; it < 99; it++) {
        ch = getchar();
        if (ch == '\n' && it == 0) {
            while (ch == '\n') {
                printf("This field cannot be blank! Enter again: ");
                ch = getchar();
            }
        } else if (ch == '\n') {
            break;
        } else {
            destination[it] = ch;
        }
    }

    destination[it] = '\0';
}
