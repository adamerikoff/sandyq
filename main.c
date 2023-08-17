#include <stdio.h>
#include <sqlite3.h>


#define MENUMAX 5

void print_menu(char *menu[MENUMAX]){
    for (int i = 0; i < MENUMAX; i++)
    {
        printf("%s\n", menu[i]);
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

    print_menu(main_menu);

    char choice;

    
    choice = getchar();
    printf("%c\n", choice);
    
    return 0;
}