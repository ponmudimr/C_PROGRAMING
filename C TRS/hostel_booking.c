#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_ROOMS 10
#define MAX_MEMBERS 2
#define NAME_LEN 50
#define REG_LEN 20

typedef struct {
    char name[NAME_LEN];
    char reg_no[REG_LEN];
    int year;
} Student;

typedef struct {
    int room_no;
    Student members[MAX_MEMBERS];
    int occupied;  // number of members currently in room
    int booked;    // 0 = available, 1 = full
} Room;

Room hostel[TOTAL_ROOMS];

void init_rooms() {
    for (int i = 0; i < TOTAL_ROOMS; i++) {
        hostel[i].room_no = 200 + i + 1;  // Rooms: 201 to 210
        hostel[i].occupied = 0;
        hostel[i].booked = 0;
        memset(hostel[i].members, 0, sizeof(hostel[i].members));
    }
}

void display_rooms() {
    printf("\n========== HOSTEL 2 - ROOM STATUS ==========\n");
    printf("%-8s %-12s %-10s\n", "Room No", "Occupancy", "Status");
    printf("---------------------------------------------\n");
    for (int i = 0; i < TOTAL_ROOMS; i++) {
        printf("%-8d %-12d %-10s\n",
               hostel[i].room_no,
               hostel[i].occupied,
               hostel[i].booked ? "FULL" : "AVAILABLE");
    }
    printf("=============================================\n");
}

int find_room(int room_no) {
    for (int i = 0; i < TOTAL_ROOMS; i++) {
        if (hostel[i].room_no == room_no)
            return i;
    }
    return -1;
}

void book_room() {
    int room_no;
    printf("\n--- BOOK A ROOM ---\n");
    display_rooms();

    printf("Enter Room Number to book (201-210): ");
    scanf("%d", &room_no);

    int idx = find_room(room_no);
    if (idx == -1) {
        printf("[ERROR] Room %d does not exist.\n", room_no);
        return;
    }
    if (hostel[idx].booked) {
        printf("[ERROR] Room %d is already full.\n", room_no);
        return;
    }

    Student s;
    printf("Enter Student Name       : ");
    scanf(" %[^\n]", s.name);
    printf("Enter Registration Number: ");
    scanf(" %s", s.reg_no);
    printf("Enter Year of Study      : ");
    scanf("%d", &s.year);

    if (s.year != 1) {
        printf("[ERROR] Hostel 2 is only for 1st year students.\n");
        return;
    }

    hostel[idx].members[hostel[idx].occupied] = s;
    hostel[idx].occupied++;

    if (hostel[idx].occupied == MAX_MEMBERS)
        hostel[idx].booked = 1;

    printf("\n[SUCCESS] %s booked in Room %d. (%d/%d members)\n",
           s.name, room_no, hostel[idx].occupied, MAX_MEMBERS);
}

void view_bookings() {
    printf("\n========== HOSTEL 2 - BOOKING DETAILS ==========\n");
    int found = 0;
    for (int i = 0; i < TOTAL_ROOMS; i++) {
        if (hostel[i].occupied > 0) {
            found = 1;
            printf("\nRoom No : %d  (%d/%d members)\n",
                   hostel[i].room_no, hostel[i].occupied, MAX_MEMBERS);
            printf("  %-5s %-25s %-15s %s\n", "Slot", "Name", "Reg No", "Year");
            printf("  -------------------------------------------------------\n");
            for (int j = 0; j < hostel[i].occupied; j++) {
                printf("  %-5d %-25s %-15s %d\n",
                       j + 1,
                       hostel[i].members[j].name,
                       hostel[i].members[j].reg_no,
                       hostel[i].members[j].year);
            }
        }
    }
    if (!found)
        printf("No bookings found.\n");
    printf("=================================================\n");
}

void cancel_booking() {
    int room_no;
    char reg_no[REG_LEN];

    printf("\n--- CANCEL BOOKING ---\n");
    printf("Enter Room Number         : ");
    scanf("%d", &room_no);
    printf("Enter Registration Number : ");
    scanf(" %s", reg_no);

    int idx = find_room(room_no);
    if (idx == -1) {
        printf("[ERROR] Room %d does not exist.\n", room_no);
        return;
    }

    int found = -1;
    for (int j = 0; j < hostel[idx].occupied; j++) {
        if (strcmp(hostel[idx].members[j].reg_no, reg_no) == 0) {
            found = j;
            break;
        }
    }

    if (found == -1) {
        printf("[ERROR] No booking found for Reg No: %s in Room %d.\n", reg_no, room_no);
        return;
    }

    char name[NAME_LEN];
    strcpy(name, hostel[idx].members[found].name);

    // Shift remaining members up
    for (int j = found; j < hostel[idx].occupied - 1; j++) {
        hostel[idx].members[j] = hostel[idx].members[j + 1];
    }
    memset(&hostel[idx].members[hostel[idx].occupied - 1], 0, sizeof(Student));
    hostel[idx].occupied--;
    hostel[idx].booked = 0;

    printf("[SUCCESS] Booking for %s (Reg: %s) in Room %d has been cancelled.\n",
           name, reg_no, room_no);
}

void search_student() {
    char reg_no[REG_LEN];
    printf("\n--- SEARCH STUDENT ---\n");
    printf("Enter Registration Number: ");
    scanf(" %s", reg_no);

    int found = 0;
    for (int i = 0; i < TOTAL_ROOMS; i++) {
        for (int j = 0; j < hostel[i].occupied; j++) {
            if (strcmp(hostel[i].members[j].reg_no, reg_no) == 0) {
                printf("\n[FOUND] Student Details:\n");
                printf("  Name   : %s\n", hostel[i].members[j].name);
                printf("  Reg No : %s\n", hostel[i].members[j].reg_no);
                printf("  Year   : %d\n", hostel[i].members[j].year);
                printf("  Room   : %d\n", hostel[i].room_no);
                found = 1;
            }
        }
    }
    if (!found)
        printf("[NOT FOUND] No student with Reg No: %s\n", reg_no);
}

int main() {
    init_rooms();

    int choice;
    printf("\n====================================\n");
    printf("  HOSTEL 2 - ROOM BOOKING SYSTEM\n");
    printf("    (For 1st Year Students Only)\n");
    printf("====================================\n");

    do {
        printf("\n--- MAIN MENU ---\n");
        printf("1. View All Rooms\n");
        printf("2. Book a Room\n");
        printf("3. View All Bookings\n");
        printf("4. Cancel Booking\n");
        printf("5. Search Student\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: display_rooms();  break;
            case 2: book_room();      break;
            case 3: view_bookings();  break;
            case 4: cancel_booking(); break;
            case 5: search_student(); break;
            case 0: printf("\nExiting... Goodbye!\n"); break;
            default: printf("[ERROR] Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
