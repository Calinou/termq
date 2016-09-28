#include <string>

#include "../game.h"
#include "MenuWindow.h"


MenuWindow::MenuWindow(rect dim) : Window(dim) {
    setBorder({ACS_BULLET, ACS_BULLET, ACS_BULLET, ACS_BULLET, '+', '+', '+', '+'});
    drawBorder();
};

/*
 * Highlight position in menu (default first)
 */
uint8_t MenuWindow::updateMenu() {
    clear();
    drawBorder();
    for (int i = 0; i < noItems; i++) {
        if (i == position) wattron(w, A_STANDOUT);
        else wattroff(w, A_STANDOUT);

        write({3, static_cast<uint_fast8_t>(i + 1)}, menuItems[i]);
    }
    refresh();
    return position;
};

uint8_t MenuWindow::updateMenu(int newPosition) {
    for (int i = 0; i < noItems; i++) {
        if (i == newPosition) wattron(w, A_STANDOUT);
        else wattroff(w, A_STANDOUT);

        write({3, static_cast<uint_fast8_t>(i + 1)}, menuItems[i]);
    }
    return position;
};

void MenuWindow::add(std::string item) {
    menuItems.push_back(item);
    noItems++;
};

void MenuWindow::clear() {
    werase(w);
}

void MenuWindow::setPosition(int newPosition) {
    position = newPosition;
}
std::string MenuWindow::getSelection() {
    int idx;
    bool itemSelected = false;
    while ( ! itemSelected) {

        switch (wgetch(w)) {
            case KEY_UP:
            case 56:
            case 'k':
                position = (position == 0) ? noItems - 1: position - 1;
                break;
            case KEY_DOWN:
            case 50:
            case 'j':
                position = (position == noItems - 1) ? 0 : position + 1;
                break;
            case KEY_ENTER: /* numpad enter */
            case '\n':      /* keyboard return */
                itemSelected = true;
                break;

        }
        // XXX debugging
        //std::string x = std::to_string(position);
        //mvwprintw(w, 0, 0, x.c_str());

        // TODO put these in method(s)
        idx        = (position % menuItems.size());
        selection  = menuItems[idx];

        updateMenu(idx);
    }

    return selection;
};

