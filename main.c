#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct App {
    bool running;
};

struct App* new_app() {
    struct App *app = malloc(sizeof(struct App));
    app->running = true;
    return app;
}

enum Command {
    EXIT,
    BALANCE,
    WITHDRAW,
    DEPOSIT,
    UNKNOWN
};

enum Command request_command_from_user() {
    printf("\nPlease select a command from the following:\n");
    printf("(1) Balance - View your current account balance.\n");
    printf("(2) Withdraw - Withdraw funds from your account.\n");
    printf("(3) Deposit - Deposit funds into your account.\n");
    printf("(0) Exit - Exit the banking system.\n");

    // fgets reads up to (sizeof(buffer) - 1)
    // 0 = command int, 1 = \n
    char buffer[3];
    printf("\nSelection: ");
    fgets(buffer, sizeof(buffer), stdin);

    enum Command cmd = UNKNOWN;
    switch (buffer[0] - '0') { // convert to int
        case BALANCE:
            return BALANCE;
        case WITHDRAW:
            return WITHDRAW;
        case DEPOSIT:
            return DEPOSIT;
        case EXIT:
            return EXIT;
    }

    if (strchr(buffer, '\n') == NULL) {
        // if the captured input doesn't contain NULL we know we overflowed
        // clear the stdin input buffer up to the new line char
        while (fgetc(stdin) != '\n');
    }

    return cmd;
}


void display_welcome_message() {
    printf("\n/*******************************/");
    printf("\n/ Welcome to The Banking System /");
    printf("\n/*******************************/\n");
}

void handle_balance(struct App *app) {
    printf("Handling balance...\n");
}

void handle_withdraw(struct App *app) {
    printf("Handling withdrawal...\n");
}

void handle_deposit(struct App *app) {
    printf("Handling deposit...\n");
}

void handle_exit(struct App *app) {
    printf("Goodbye!\n\n");
    app->running = false;
}

void handle_unknown(struct App *app) {
    printf("Command unknown...\n");
}

int main(int argc, char *argv[]) {
    // setup application
    struct App *app = new_app();

    display_welcome_message();

    do {
        switch (request_command_from_user()) {
            case BALANCE:
                handle_balance(app);
                break;
            case WITHDRAW:
                handle_withdraw(app);
                break;
            case DEPOSIT:
                handle_deposit(app);
                break;
            case EXIT:
                handle_exit(app);
                break;
            case UNKNOWN:
                handle_unknown(app);
                break;
        }
    } while (app->running);

    free(app);
    app = NULL;

    return 0;
}
