#include <stdio.h>
#include<stdlib.h>

#include <sqlite3.h>

// PRINTS STORAGES
void print_storages(){
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

void print_storage_items(int storage_id){
    sqlite3 *db;
    char *errMsg = 0;

    int rc = sqlite3_open("sandyq.db", &db);
    
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        const char *sql = "SELECT storages.name, items.name, quantity FROM storage_item INNER JOIN items ON storage_item.item_id = items.id INNER JOIN storages ON storage_item.storage_id = storages.id WHERE storages.id = ?";
        
        sqlite3_stmt *stmt;

        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        sqlite3_bind_int(stmt, 1, storage_id);
        printf("\e[1m%-15s %-15s %-15s\e[m\n", "Storage Name", "Item Name", "Quantity");
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            const unsigned char *storage_name = sqlite3_column_text(stmt, 0);
            const unsigned char *item_name = sqlite3_column_text(stmt, 1);
            int item_quantity = sqlite3_column_int(stmt, 2);

            printf("%-15s %-15s %-5d\n", storage_name, item_name, item_quantity);
        }

        sqlite3_finalize(stmt);

        sqlite3_close(db);
    }
}

// PRINTS ITEMS
void print_items(){
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
                //fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
            } else {
                //printf("Item has been inserted successfully.\n");
            }
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}

// GET ID OF THE ITEM
int get_id_of_item(char inputString[100]){
    int productID;

    sqlite3 *db;
    char *errMsg = 0;

    int rc = sqlite3_open("sandyq.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    const char *sql = "SELECT id FROM items WHERE name = ?";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, inputString, -1, SQLITE_STATIC);

    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        productID = sqlite3_column_int(stmt, 0);
    } else {
        return 0;
    }

    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return productID;
}

void insert_item_to_storage(){
    char inputString[100];
    int storage;
    int quantity;
    int item_id;

    printf("Enter item's name: ");
    scanf("%s", inputString);
    
    insert_item_to_items(inputString);

    printf("Enter item's quantity: ");
    scanf("%d", &quantity);

    print_storages();

    printf("Select storage: ");
    scanf("%d", &storage);

    item_id = get_id_of_item(inputString);

    //printf("%d %s %d %d", item_id, inputString, quantity, storage);
    // INSERT NEW ITEM INTO storage_item table

    sqlite3 *db;
    char *errMsg = 0;

    int rc = sqlite3_open("sandyq.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        const char *sql = "INSERT INTO storage_item (storage_id, item_id, quantity) VALUES (?, ?, ?)";
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        } else {
            sqlite3_bind_int(stmt, 1, storage);
            sqlite3_bind_int(stmt, 2, item_id);
            sqlite3_bind_int(stmt, 3, quantity);

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






// MAIN FUNCTION
int main(void)
{
    int choice = 0;
    int storage_choice = 0;

    do {
        printf("1. show storages\n");
        printf("2. show items\n");
        printf("3. add item\n");
        printf("4. remove item\n");
        printf("5. update item\n");
        printf("6. exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                print_storages();
                getchar();
                break;
            
            case 2:
                print_storages();
                printf("Enter your choice: ");
                scanf("%d", &storage_choice);
                print_storage_items(storage_choice);
                break;

            case 3:
                insert_item_to_storage();
                break;
            
            case 4:
                printf("updated");
                getchar();
                break;
            
            case 5:
                break;
            
            case 6:
                break;

            default:
                printf("Wrong choice!\n");
                break;
        }
    } while (choice != 6);
    return 0;
}