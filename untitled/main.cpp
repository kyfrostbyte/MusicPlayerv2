#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
using namespace std;
int main() {
    cout << "Before PlaySound" << endl;

    // Print the current working directory (optional)
    char buffer[FILENAME_MAX];
    GetCurrentDirectoryA(FILENAME_MAX, buffer);
    cout << "Current Directory: " << buffer << endl;

    PlaySound(TEXT("down.wav"), NULL, SND_SYNC);

    cout << "After PlaySound" << endl;

    system("pause");

    return 0;
}