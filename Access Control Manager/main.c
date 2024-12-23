#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_USERNAME 20
#define MAX_PASSWORD 20

// Role definitions
#define ROLE_ADMIN 1
#define ROLE_USER 2

// User structure
typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int role; // 1 = Admin, 2 = User
} User;

// Database of users
User users[MAX_USERS] = {
    {"admin", "admin123", ROLE_ADMIN},
    {"user1", "user123", ROLE_USER}
};

int user_count = 2; // Current number of users

// Function prototypes
int authenticate(char *username, char *password, int *role);
void admin_panel();
void user_panel();
void add_user();
void view_users();

// Authentication function
int authenticate(char *username, char *password, int *role) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            *role = users[i].role;
            return 1; // Success
        }
    }
    return 0; // Failure
}

// Admin panel
void admin_panel() {
    int choice;
    do {
        printf("\n--- Admin Panel ---\n");
        printf("1. Add User\n");
        printf("2. View Users\n");
        printf("3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_user();
                break;
            case 2:
                view_users();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice!\n");
        }
    } while (1);
}

// User panel
void user_panel() {
    printf("\nWelcome, User! You have limited access.\n");
}

// Add a new user
void add_user() {
    if (user_count >= MAX_USERS) {
        printf("User limit reached! Cannot add more users.\n");
        return;
    }

    User new_user;
    printf("Enter username: ");
    scanf("%s", new_user.username);
    printf("Enter password: ");
    scanf("%s", new_user.password);
    printf("Enter role (1=Admin, 2=User): ");
    scanf("%d", &new_user.role);

    users[user_count++] = new_user;
    printf("User added successfully!\n");
}

// View all users
void view_users() {
    printf("\n--- User List ---\n");
    for (int i = 0; i < user_count; i++) {
        printf("Username: %s, Role: %s\n", users[i].username,
               users[i].role == ROLE_ADMIN ? "Admin" : "User");
    }
}

// Main function
int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int role;

    printf("\n--- Access Control Manager ---\n");
    printf("Login\nUsername: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (authenticate(username, password, &role)) {
        printf("Login successful!\n");
        if (role == ROLE_ADMIN) {
            admin_panel();
        } else if (role == ROLE_USER) {
            user_panel();
        }
    } else {
        printf("Login failed! Invalid username or password.\n");
    }

    return 0;
}
