#include <stdio.h>
#include<stdlib.h>

#include <sqlite3.h>


#define MENUMAX 5

// PRINTS MENU
void print_main_menu(char *menu[MENUMAX]){
    for (int i = 0; i < MENUMAX; i++){
        printf("%s\n", menu[i]);
    }
}

// PRINTS STORAGES
void print_storages(){
    system("clear");  
    sqlite3 *db;
    char *errMsg = 0;

    int rc = sqlite3_open("sandyq.db", &db);
    
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        const char *sql = "SELECT storages.id, storages.name FROM storages";
        sqlite3_stmt *stmt;

        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

        printf("\e[1m%-5s %s\e[m\n", "ID", "Storage Name");
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            const unsigned char *id = sqlite3_column_text(stmt, 0);
            const unsigned char *name = sqlite3_column_text(stmt, 1);

            printf("%-5s %s\n", id, name);
        }

        sqlite3_finalize(stmt);

        sqlite3_close(db);
    }
}
// PRINTS ITEMS
void print_items(){
    system("clear");  
    sqlite3 *db;
    char *errMsg = 0;

    int rc = sqlite3_open("sandyq.db", &db);
    
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        const char *sql = "SELECT items.id, items.name FROM items";
        sqlite3_stmt *stmt;

        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

        printf("\e[1m%-5s %s\e[m\n", "ID", "Item Name");
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            const unsigned char *id = sqlite3_column_text(stmt, 0);
            const unsigned char *name = sqlite3_column_text(stmt, 1);

            printf("%-5s %s\n", id, name);
        }

        sqlite3_finalize(stmt);

        sqlite3_close(db);
    }
}

// INSERTS SINGLE ITEM INTO items TABLE
void insert_item_to_items(char inputString[100]){
    sqlite3 *db;
    char *errMsg = 0;

    int rc = sqlite3_open("sandyq.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        const char *sql = "INSERT INTO items (name) VALUES (?)";
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        } else {
            sqlite3_bind_text(stmt, 1, inputString, -1, SQLITE_STATIC);

            rc = sqlite3_step(stmt);
            if (rc != SQLITE_DONE) {
                fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
            } else {
                printf("Item has been inserted successfully.\n");
            }
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}

void add_item_to_storage(){
    char inputString[100];
    int storage;
    int quantity;

    printf("Enter item's name: ");
    scanf("%s", inputString);

    printf("Enter item's quantity: ");
    scanf("%d", &quantity);

    print_storages();

    printf("Select storage: ");
    scanf("%d", &storage);

}





// MAIN FUNCTION
int main(void)
{
    char *main_menu[MENUMAX] = {
        "1. show storage",
        "2. add item",
        "3. remove item",
        "4. update item",
        "5. exit"
    };

    print_items();
    insert_item_to_items("fanta 1l");
    print_items();

    return 0;
}