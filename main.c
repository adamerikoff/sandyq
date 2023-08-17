#include <stdio.h>
#include <sqlite3.h>


#define MENUMAX 5

void print_menu(char *menu[MENUMAX]){
    for (int i = 0; i < MENUMAX; i++)
    {
        printf("%s\n", menu[i]);
    }
}

void print_storages(){
    sqlite3 *db;
    char *errMsg = 0;

    // Open a database connection (or create if it doesn't exist)
    int rc = sqlite3_open("sandyq.db", &db);
    
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    else{
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

int main(void)
{
    char *main_menu[MENUMAX] = {
        "1. show storage",
        "2. add item",
        "3. remove item",
        "4. update item",
        "5. exit"
    };

    //print_menu(main_menu);

    // char inputString[100];
    // int storage;

    // printf("Enter a string: ");
    // scanf("%s\n", inputString);

    // printf("Select storage: ");
    // scanf("%d\n", &storage);

    // printf("You entered: %s and %d", inputString, storage);
    
    print_storages();

    return 0;
}