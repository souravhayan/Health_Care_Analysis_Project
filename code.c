#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

void red () {
  printf("\033[1;31m");
}

void blue () {
  printf("\033[0;34m");
}

void purple () {
  printf("\033[0;35m");
}

void cyan () {
  printf("\033[0;36m");
}

void green () {
  printf("\033[0;32m");
}

void yellow () {
  printf("\033[0;33m");
}

struct Patient {
    char name[100];
    int age;
    float height;
    float weight;
    float bmi;
    struct Patient* next;
};

struct Event {
    char eventName[100];
    char date[20];
    char place[50];
    struct Event* next;
};

struct DonationInfo {
    char donorName[100];
    char bloodType[5];
    char donationDate[20];
    char location[50];
    char mobileNumber[15];
    struct DonationInfo* next;
};

struct StackNode {
    struct DonationInfo* donationInfo;
    struct StackNode* next;
};

struct StackNode* top = NULL;

struct Patient* createPatient(const char* name, int age, float height, float weight);
void insertPatient(struct Patient** head, struct Patient* newPatient);
void displayPatients(struct Patient* head);
void calculateBMI();
void calculateStepCount();

struct Event* createEvent(const char* eventName, const char* date, const char* place);
void pushEvent(struct Event** top, struct Event* newEvent);
struct Event* popEvent(struct Event** top);
void displayEvents(struct Event* top);

struct DonationInfo* createDonationInfo(const char* donorName, const char* bloodType, const char* donationDate,
                                        const char* location, const char* mobileNumber);
void push(struct DonationInfo* donationInfo);
struct DonationInfo* pop();
void display();
void searchAndDisplay(const char* searchTerm, int searchType);
void toLowercase(char* str);
void loadFromFile();
void saveToFile(struct Patient* patientRecords, struct Event* eventStack);
struct Patient* patientRecords = NULL;
struct Event* eventStack = NULL;


int main() {
    int choice, ch2;

    do {
        printf("\n");
        green();
        printf("Main Option:\n------------\n\n");
        cyan();
        printf("1. Calculate BMI\n");
        printf("2. Calculate Step Count\n");
        printf("3. Patient (Add and Display)\n");
        printf("4. Blood Donation Information\n");  // Moved Blood Donation Information to option 4
        printf("5. Events\n");  // Moved Events to option 5
        printf("6. Exit\n");
        yellow();
        printf("\nEnter your Choice (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                calculateBMI();
                break;
            case 2:
                calculateStepCount();
                break;
            case 3: {
                int subChoice;
                printf("\n");
                cyan();
                printf("1. Add Patient\n");
                printf("2. Display Patient Records\n");
                yellow();
                printf("\nEnter sub-choice (1-2): ");
                scanf("%d", &subChoice);

                switch (subChoice) {
                    case 1: {
                        char name[100];
                        int age;
                        float height, weight;

                        purple();
                        printf("\n");
                        printf("Enter patient name: ");
                        scanf(" %99[^\n]", name);
                        printf("Enter patient age: ");
                        scanf("%d", &age);
                        printf("Enter patient height (in cm): ");
                        scanf("%f", &height);
                        printf("Enter patient weight (in kg): ");
                        scanf("%f", &weight);

                        insertPatient(&patientRecords, createPatient(name, age, height, weight));
                        break;
                    }
                    case 2:
                        displayPatients(patientRecords);
                        break;
                    default:
                    red();
                        printf("Invalid sub-choice.\n");
                        break;
                }
                break;
            }
            case 4: {
                int subChoice;
                printf("1. Add Blood Donation Information\n");
                printf("2. Delete Blood Donation Information\n");
                printf("3. Display Blood Donation Information\n");
                printf("4. Search Blood Donation Information\n");
                printf("\nEnter sub-choice (1-4): ");
                scanf("%d", &subChoice);

                switch (subChoice) {
                    case 1: {
                        char donorName[100], bloodType[5], donationDate[20], location[50], mobileNumber[15];

                        printf("Enter donor name: ");
                        scanf(" %99[^\n]", donorName);

                        printf("Enter blood type (A+, A-, B+, B-, AB+, AB-, O+, O-): ");
                        scanf("%s", bloodType);

                        if (strcmp(bloodType, "A+") != 0 && strcmp(bloodType, "A-") != 0 &&
                            strcmp(bloodType, "B+") != 0 && strcmp(bloodType, "B-") != 0 &&
                            strcmp(bloodType, "AB+") != 0 && strcmp(bloodType, "AB-") != 0 &&
                            strcmp(bloodType, "O+") != 0 && strcmp(bloodType, "O-") != 0) {
                            printf("Invalid blood type. Please enter a valid blood type.\n");
                            continue;
                        }

                        printf("Enter donation date(DD-MM-YYYY): ");
                        scanf("%s", donationDate);

                        printf("Enter location: ");
                        scanf("%s", location);

                        toLowercase(location);

                        printf("Enter mobile number: ");
                        scanf("%s", mobileNumber);

                        struct DonationInfo* newDonation =
                            createDonationInfo(donorName, bloodType, donationDate, location, mobileNumber);
                        push(newDonation);
                        break;
                    }
                    case 2: {
                        struct DonationInfo* deletedDonation = pop();

                        if (deletedDonation != NULL) {
                            printf("Deleted Blood Donation Information:\n");
                            display();
                        }
                        break;
                    }
                    case 3:
                        display();
                        break;
                    case 4: {
                        int searchType;
        
                        printf("Press 1 to search by Blood Type, 2 for Location, or 3 for Mobile Number: ");
                        scanf("%d", &searchType);

                        char searchTerm[50];
                        printf("Enter search : ");
                        scanf("%s", searchTerm);

                        if (searchType == 2) {
                            toLowercase(searchTerm);
                        }

                        searchAndDisplay(searchTerm, searchType);
                        break;
                    }
                    default:
                        printf("Invalid sub-choice.\n");
                        break;
                }
                break;
    
}

            case 5: {
                int subChoice;
    printf("1. Create Event\n");
    printf("2. Delete Event\n");
    printf("3. Display Events\n");
    printf("\nEnter sub-choice (1-3): ");
    scanf("%d", &subChoice);

    switch (subChoice) {
        case 1: {
            char eventName[100], date[20], place[50];

            printf("Enter Event Name: ");
            scanf(" %99[^\n]", eventName);
            getchar();  // Consume the newline character

            printf("Enter Event Date: ");
            scanf(" %19[^\n]", date);
            getchar();  // Consume the newline character

            printf("Enter Event Place: ");
            scanf("%s", place);

            struct Event* newEvent = createEvent(eventName, date, place);
            pushEvent(&eventStack, newEvent);
            break;
        }
        case 2: {
            struct Event* poppedEvent = popEvent(&eventStack);
            if (poppedEvent != NULL) {
                printf("Popped Event from Stack:\n");
                printf("Event Name: %s\n", poppedEvent->eventName);
                printf("Date: %s\n", poppedEvent->date);
                printf("Place: %s\n", poppedEvent->place);
                printf("\n");
            }
            break;
        }
        case 3:
            displayEvents(eventStack);
            break;
        default:
            printf("Invalid sub-choice.\n");
            break;
    }
    break;
                
            }
            case 6: {
                saveToFile(patientRecords, eventStack);
                while (patientRecords != NULL) {
                    struct Patient* temp = patientRecords;
                    patientRecords = patientRecords->next;
                    free(temp);
                }

                while (eventStack != NULL) {
                    struct Event* temp = eventStack;
                    eventStack = eventStack->next;
                    free(temp);
                }

                while (top != NULL) {
                    struct StackNode* temp = top;
                    top = top->next;
                    free(temp->donationInfo);
                    free(temp);
                }

                exit(0);
            }
            default:
                printf("Invalid choice.\n");
        }

        red();
        printf("\nPress 1 for RUN Again or Press any key to EXIT!\n");
        scanf("%d", &ch2);
    } while (ch2 == 1);

    return 0;
}

struct Patient* createPatient(const char* name, int age, float height, float weight) {
    struct Patient* newPatient = (struct Patient*)malloc(sizeof(struct Patient));
    if (newPatient == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strcpy(newPatient->name, name);
    newPatient->age = age;
    newPatient->height = height;
    newPatient->weight = weight;
    newPatient->bmi = (weight / ((height / 100) * (height / 100)));
    newPatient->next = NULL;

    return newPatient;
}

void insertPatient(struct Patient** head, struct Patient* newPatient) {
    if (*head == NULL) {
        *head = newPatient;
    } else {
        struct Patient* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newPatient;
    }
}

void displayPatients(struct Patient* head) {
    struct Patient* current = head;
    printf("\n\nPatient Records:\n----------------\n\n");
    while (current != NULL) {
        printf("Name: %s\n", current->name);
        printf("Age: %d\n", current->age);
        printf("Height: %.2f cm\n", current->height);
        printf("Weight: %.2f kg\n", current->weight);
        printf("BMI: %.2f\n", current->bmi);
        printf("\n");
        current = current->next;
    }
}

void calculateBMI() {
     float weight, height, result, bmi;
    printf("+---------------------+\n| BMI Report Analysis |\n+---------------------+\n\n");
    printf("BMI-range scale_\n");
    printf("-----!-----!-------!------!------!---\n     15  18.5      25     30     35\n\n");
    printf("Enter your weight (kg): ");
    scanf("%f", &weight);

    printf("Enter your height (m): ");
    scanf("%f", &height);

    result = pow(height, 2);

    bmi = (weight / result);
    printf("Your BMI is: %.1f --> ", bmi);

    if (bmi < 18.5) {
        printf("Bad Health\n\n");
        if (bmi >= 17) {
            printf("-+-!-----!-------!------!------!---\n     15  18.5    25     30     35\n");
        } else {
            printf("+--!-----!-------!------!------!---\n     15  18.5    25     30     35\n");
        }
    } else if (bmi > 18.4 && bmi < 25.1) {
        printf("Good Health\n\n");
        if (bmi <= 20) {
            printf("-----!-----!-+----!------!------!---\n     15  18.5    25     30     35\n");
        } else {
            printf("-----!-----!----+-!------!------!---\n     15  18.5    25     30     35\n");
        }
    } else if (bmi > 25 && bmi < 30) {
        printf("Bad Health \n");
        printf("-----!-----!------!--+---!------!---\n     15  18.5    25     30     35\n");
    } else {
        printf("Bad Health\n");
    }

    printf("Thank You!\n");

}

void calculateStepCount() {
    int limit = 8000;
    float step, km, kmf = 5.30, percent;

    printf("\n\n+---------------------+\n|  Step Count Report  |  1. km. to step_\n+---------------------+\n");

    printf("Today's target 8000 step count_\n\n");

    printf("Enter your km: ");
    scanf("%f", &km);

    step = (km * limit) / kmf;

    printf("Your step counted: %.0f steps (approximate)\n", step);

    percent = (step * 100) / limit;

    if (step >= limit) {
        printf("Your target fulfilled 100%%\n\n");
    } else {
        printf("Your target fulfilled %.2f%%\n\n", percent);
    }

    printf("Thank you!\n");
}

struct Event* createEvent(const char* eventName, const char* date, const char* place) {
    struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));
    if (newEvent == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strcpy(newEvent->eventName, eventName);
    strcpy(newEvent->date, date);
    strcpy(newEvent->place, place);
    newEvent->next = NULL;

    return newEvent;
}

void pushEvent(struct Event** top, struct Event* newEvent) {
    newEvent->next = *top;
    *top = newEvent;
}

struct Event* popEvent(struct Event** top) {
     if (*top == NULL) {
        printf("STACK UNDERFLOW!\n");
        return NULL;
    }

    struct Event* poppedEvent = *top;
    *top = (*top)->next;
    poppedEvent->next = NULL;

    return poppedEvent;
}

void displayEvents(struct Event* top) {
     struct Event* current = top;
    printf("\nUpcoming Events:\n");
    while (current != NULL) {
        printf("Event Name: %s\n", current->eventName);
        printf("Date: %s\n", current->date);
        printf("Place: %s\n", current->place);
        printf("\n");
        current = current->next;
    }
}


struct DonationInfo* createDonationInfo(const char* donorName, const char* bloodType, const char* donationDate,
                                        const char* location, const char* mobileNumber) {
    struct DonationInfo* newDonation = (struct DonationInfo*)malloc(sizeof(struct DonationInfo));
    if (newDonation == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strcpy(newDonation->donorName, donorName);
    strcpy(newDonation->bloodType, bloodType);
    strcpy(newDonation->donationDate, donationDate);
    strcpy(newDonation->location, location);
    strcpy(newDonation->mobileNumber, mobileNumber);
    newDonation->next = NULL;

    return newDonation;
}

void push(struct DonationInfo* donationInfo) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->donationInfo = donationInfo;
    newNode->next = top;
    top = newNode;
}

struct DonationInfo* pop() {
    if (top == NULL) {
        printf("STACK UNDERFLOW!\n");
        return NULL;
    }

    struct StackNode* temp = top;
    struct DonationInfo* poppedDonation = temp->donationInfo;
    top = temp->next;
    free(temp);

    return poppedDonation;
}

void display() {
    struct StackNode* current = top;
    
    green();
    printf("\nBlood Donation Information:\n---------------------------\n\n");

    while (current != NULL) {
        printf("Donor Name: %s\n", current->donationInfo->donorName);
        printf("Blood Type: %s\n", current->donationInfo->bloodType);
        printf("Donation Date: %s\n", current->donationInfo->donationDate);
        printf("Location: %s\n", current->donationInfo->location);
        printf("Mobile Number: %s\n", current->donationInfo->mobileNumber);
        printf("\n");

        current = current->next;
    }
}

void searchAndDisplay(const char* searchTerm, int searchType) {
     struct StackNode* current = top;
    int found = 0;

    printf("\nBlood Donation Information for ");

    switch (searchType) {
        case 1:
            printf("Blood Type %s:\n", searchTerm);
            while (current != NULL) {
                if (strcmp(current->donationInfo->bloodType, searchTerm) == 0) {
                    printf("Donor Name: %s\n", current->donationInfo->donorName);
                    printf("Blood Type: %s\n", current->donationInfo->bloodType);
                    printf("Donation Date: %s\n", current->donationInfo->donationDate);
                    printf("Location: %s\n", current->donationInfo->location);
                    printf("Mobile Number: %s\n", current->donationInfo->mobileNumber);
                    printf("\n");

                    found = 1;
                }
                current = current->next;
            }
            break;
        
        case 2:
            printf("Location %s:\n", searchTerm);
            while (current != NULL) {
                if (strcmp(current->donationInfo->location, searchTerm) == 0) {
                    printf("Donor Name: %s\n", current->donationInfo->donorName);
                    printf("Blood Type: %s\n", current->donationInfo->bloodType);
                    printf("Donation Date: %s\n", current->donationInfo->donationDate);
                    printf("Location: %s\n", current->donationInfo->location);
                    printf("Mobile Number: %s\n", current->donationInfo->mobileNumber);
                    printf("\n");

                    found = 1;
                }
                current = current->next;
            }
            break;
        
        case 3:
            printf("Mobile Number %s:\n", searchTerm);
            while (current != NULL) {
                if (strcmp(current->donationInfo->mobileNumber, searchTerm) == 0) {
                    printf("Donor Name: %s\n", current->donationInfo->donorName);
                    printf("Blood Type: %s\n", current->donationInfo->bloodType);
                    printf("Donation Date: %s\n", current->donationInfo->donationDate);
                    printf("Location: %s\n", current->donationInfo->location);
                    printf("Mobile Number: %s\n", current->donationInfo->mobileNumber);
                    printf("\n");

                    found = 1;
                }
                current = current->next;
            }
            break;

        default:
            red();
            printf("Invalid search type.\n");
            return;
    }

    if (!found) {
        red();
        printf("No matching records found.\n");
    }
}

void toLowercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void saveToFile(struct Patient* patientRecords, struct Event* eventStack) {
    FILE* file = fopen("health_records.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Save patient information
    struct Patient* currentPatient = patientRecords;
    while (currentPatient != NULL) {
        fprintf(file, "Patient %s %d %.2f %.2f %.2f\n", currentPatient->name, currentPatient->age,
                currentPatient->height, currentPatient->weight, currentPatient->bmi);

        currentPatient = currentPatient->next;
    }

    // Save event information
    struct Event* currentEvent = eventStack;
    while (currentEvent != NULL) {
        fprintf(file, "Event %s %s %s\n", currentEvent->eventName, currentEvent->date, currentEvent->place);

        currentEvent = currentEvent->next;
    }

    // Save blood donor information
    struct StackNode* currentDonation = top;
    while (currentDonation != NULL) {
        fprintf(file, "Donor %s %s %s %s %s\n", currentDonation->donationInfo->donorName,
                currentDonation->donationInfo->bloodType, currentDonation->donationInfo->donationDate,
                currentDonation->donationInfo->location, currentDonation->donationInfo->mobileNumber);

        currentDonation = currentDonation->next;
    }

    fclose(file);

    printf("Data saved to health_records.txt\n");
}



void loadFromFile() {
    FILE* file = fopen("health_records.txt", "r");
    if (file == NULL) {
        printf("No existing data file found.\n");
        return;
    }

    while (true) {
        char type[10], name[100], bloodType[5], date[20], place[50], mobileNumber[15];
        int age;
        float height, weight, bmi;

        if (fscanf(file, "%s", type) == EOF) {
            break;
        }

        if (strcmp(type, "Patient") == 0) {
            fscanf(file, "%s %d %f %f %f", name, &age, &height, &weight, &bmi);
            struct Patient* newPatient = createPatient(name, age, height, weight);
            insertPatient(&patientRecords, newPatient);
        } else if (strcmp(type, "Event") == 0) {
            fscanf(file, "%s %s %s", name, date, place);
            struct Event* newEvent = createEvent(name, date, place);
            pushEvent(&eventStack, newEvent);
        } else if (strcmp(type, "Donor") == 0) {
            fscanf(file, "%s %s %s %s %s", name, bloodType, date, place, mobileNumber);
            struct DonationInfo* newDonation = createDonationInfo(name, bloodType, date, place, mobileNumber);
            push(newDonation);
        }
    }

    fclose(file);
}

