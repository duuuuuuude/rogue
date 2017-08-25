#include <menu.h>
#include <stdlib.h>

#include "main_menu.h"

void close_menu(int numberItems, MENU * menu, ITEM ** items) {
    int i;
    unpost_menu(menu);
    free_menu(menu);
    for (i = 0; i < numberItems; i++) {
        free_item(items[i]);
    }
}

int main_menu(int numberItems, char * choices[]) {
    int i, ch;
    int value;

    MENU *menu;
    ITEM** items = malloc(sizeof(**items) * numberItems);
    ITEM *current;

    for (i = 0; i < numberItems; i++) {
    	items[i] = new_item(choices[i], "");
    }
    items[i] = (ITEM*)NULL;

    menu = new_menu((ITEM**)items);
    post_menu(menu);
    refresh();

    // menu loop
    while (true) {
        ch = getch();
        switch (ch) {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case 10: // enter key
                current = current_item(menu);
                value = item_index(current);
                close_menu(numberItems, menu, items);
                return value;
        }
    }
}
