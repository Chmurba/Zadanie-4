#ifndef EDIT_H
#define EDIT_H

#include <string>
#include <windows.h>

class Edit {
public:
    enum Color {
        Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray,
        DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
    };

    Edit();
    Edit(const Edit& other);
    ~Edit();

    void setPosition(int x, int y);
    void setLength(int length);
    void setText(const std::string& text);
    void setTextColor(Color color);
    void setBackgroundColor(Color color);
    std::string getText() const;

    void userText(); // Handles user input in the console

private:
    void updateConsoleAttributes();
    void drawText();

    COORD position;
    int length;
    std::string text;
    WORD textColor;
    WORD backgroundColor;
    HANDLE hConsole;
};

#endif // EDIT_H