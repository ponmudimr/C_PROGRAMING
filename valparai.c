#include <stdio.h>
#include <string.h>

#define MAX_CARS 100
#define MAX_BIKES 200

int carsIssued = 0;
int bikesIssued = 0;
int passCounter = 1000;

struct EPass {
    char name[50];
    int age;
    char mobile[15];
    char vehicleNumber[20];
    char vehicleType[20];
    char destination[50];
    char travelDate[20];
    int passID;
};

void generatePass(struct EPass user) {

    printf("\n=====================================\n");
    printf("         VALPARAI E-PASS\n");
    printf("=====================================\n");

    printf("Pass ID           : VP%d\n", user.passID);

    printf("Name              : %s\n", user.name);

    printf("Age               : %d\n", user.age);

    printf("Mobile Number     : %s\n", user.mobile);

    printf("Vehicle Number    : %s\n", user.vehicleNumber);

    printf("Vehicle Type      : %s\n", user.vehicleType);

    printf("Destination       : %s\n", user.destination);

    printf("Travel Date       : %s\n", user.travelDate);

    printf("Status            : APPROVED\n");

    printf("=====================================\n");
}

int main() {

    int choice;

    while(1) {

        struct EPass user;

        printf("\n========= VALPARAI E-PASS SYSTEM =========\n");

        printf("1. Apply E-Pass\n");
        printf("2. Show Remaining Slots\n");
        printf("3. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        getchar();

        if(choice == 1) {

            printf("\nEnter Full Name: ");
            fgets(user.name, sizeof(user.name), stdin);

            user.name[strcspn(user.name, "\n")] = 0;

            printf("Enter Age: ");
            scanf("%d", &user.age);

            getchar();

            printf("Enter Mobile Number: ");
            fgets(user.mobile, sizeof(user.mobile), stdin);

            user.mobile[strcspn(user.mobile, "\n")] = 0;

            printf("Enter Vehicle Number: ");
            fgets(user.vehicleNumber, sizeof(user.vehicleNumber), stdin);

            user.vehicleNumber[strcspn(user.vehicleNumber, "\n")] = 0;

            printf("Enter Vehicle Type (car/bike): ");
            fgets(user.vehicleType, sizeof(user.vehicleType), stdin);

            user.vehicleType[strcspn(user.vehicleType, "\n")] = 0;

            printf("Enter Destination: ");
            fgets(user.destination, sizeof(user.destination), stdin);

            user.destination[strcspn(user.destination, "\n")] = 0;

            printf("Enter Travel Date (DD/MM/YYYY): ");
            fgets(user.travelDate, sizeof(user.travelDate), stdin);

            user.travelDate[strcspn(user.travelDate, "\n")] = 0;

            if(strcmp(user.vehicleType, "car") == 0) {

                if(carsIssued >= MAX_CARS) {

                    printf("\nCar limit reached for today!\n");

                    continue;
                }

                carsIssued++;
            }

            else if(strcmp(user.vehicleType, "bike") == 0) {

                if(bikesIssued >= MAX_BIKES) {

                    printf("\nBike limit reached for today!\n");

                    continue;
                }

                bikesIssued++;
            }

            else {

                printf("\nInvalid vehicle type!\n");

                continue;
            }

            user.passID = passCounter++;

            generatePass(user);
        }

        else if(choice == 2) {

            printf("\n======= AVAILABLE SLOTS =======\n");

            printf("Remaining Cars  : %d\n", MAX_CARS - carsIssued);

            printf("Remaining Bikes : %d\n", MAX_BIKES - bikesIssued);
        }

        else if(choice == 3) {

            printf("\nThank  You!\n");

            break;
        }

        else {

            printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}