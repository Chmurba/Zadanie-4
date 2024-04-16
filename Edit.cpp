#include "edit.h"
#include <iostream>
#include <conio.h>

Edit::Edit()
    : position({ 0, 0 }), length(10), text(""), textColor(15), backgroundColor(0), hConsole(GetStdHandle(STD_OUTPUT_HANDLE)) {}

Edit::Edit(const Edit& other)
    : position(other.position), length(other.length), text(other.text),
    textColor(other.textColor), backgroundColor(other.backgroundColor), hConsole(GetStdHandle(STD_OUTPUT_HANDLE)) {}

Edit::~Edit() {}

void Edit::setPosition(int x, int y) {
    position.X = x;
    position.Y = y;
}

void Edit::setLength(int length) {
    this->length = length;
}

void Edit::setText(const std::string& text) {
    this->text = text.substr(0, length);
}

void Edit::setTextColor(Color color) {
    textColor = color;
    updateConsoleAttributes();
}

void Edit::setBackgroundColor(Color color) {
    backgroundColor = color;
    updateConsoleAttributes();
}

std::string Edit::getText() const {
    return text;
}

void Edit::userText() {
    drawText();
    char ch;
    std::string input;
    while (true) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 27) // ESC key
                break;
            else if (ch == '\r') // Enter key
                break;
            else if (ch == '\b' && !input.empty()) { // Backspace
                input.pop_back();
                std::cout << '\b' << ' ' << '\b';
            }
            else if (isprint(ch) && input.length() < length) {
                input += ch;
                std::cout << ch;
            }
        }
    }
    text = input;
    std::cout << std::endl;
}

void Edit::updateConsoleAttributes() {
    SetConsoleTextAttribute(hConsole, textColor | (backgroundColor << 4));
}

void Edit::drawText() {
    SetConsoleCursorPosition(hConsole, position);
    updateConsoleAttributes();
    std::cout << std::string(length, ' '); // Clear the area
    SetConsoleCursorPosition(hConsole, position);
    std::cout << text;
}