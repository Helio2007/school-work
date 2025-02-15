#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cctype>

using namespace std;

class Hangman {
private:
    string fjalaFshehur;
    vector<char> shkronjatESupozuara;
    int numriIProvave;
    int Gabimet;

public:
    Hangman(string fjala, int numriIProvave) : fjalaFshehur(fjala), numriIProvave(numriIProvave), Gabimet(0) {}

    void shfaqFjalen() {
        for (char shkronje : fjalaFshehur) {
            if (find(shkronjatESupozuara.begin(), shkronjatESupozuara.end(), tolower(shkronje)) != shkronjatESupozuara.end() ||
                find(shkronjatESupozuara.begin(), shkronjatESupozuara.end(), toupper(shkronje)) != shkronjatESupozuara.end()) {
                cout << shkronje << " ";
            } else {
                cout << "_ ";
            }
        }
        cout << endl;
    }

    void shfaqShkronjatEGjetura() {
        cout << "Shkronjat e supozuara: ";
        for (char shkronje : shkronjatESupozuara) {
            cout << shkronje << " ";
        }
        cout << endl;
    }

    bool eshteSupozuar(char shkronje) {
        return find(shkronjatESupozuara.begin(), shkronjatESupozuara.end(), shkronje) != shkronjatESupozuara.end();
    }

    bool supozoShkronjen(char shkronje) {
        shkronje = tolower(shkronje);
        if (eshteSupozuar(shkronje)) {
            cout << "Ju tashme e keni supozuar ate shkronje!" << endl;
            return false;
        }
        shkronjatESupozuara.push_back(shkronje);
        if (fjalaFshehur.find(shkronje) == string::npos && fjalaFshehur.find(toupper(shkronje)) == string::npos) {
            Gabimet++;
            cout << "Supozim i gabuar!" << endl;
        }
        return true;
    }

    bool fund() {
        return Gabimet >= numriIProvave || gjetja();
    }

    bool gjetja() {
        for (char shkronje : fjalaFshehur) {
            if (find(shkronjatESupozuara.begin(), shkronjatESupozuara.end(), tolower(shkronje)) == shkronjatESupozuara.end() &&
                find(shkronjatESupozuara.begin(), shkronjatESupozuara.end(), toupper(shkronje)) == shkronjatESupozuara.end()) {
                return false;
            }
        }
        return true;
    }

    int kalkulimiiprovave() const {
        return numriIProvave - Gabimet;
    }

    int merrGabimet() const {
        return Gabimet;
    }
};

void shfaqHangman(int Gabimet) {
    static const vector<string> stages = {
        "  +---+\n      |\n      |\n      |\n      |\n      |\n=========",
        "  +---+\n  O   |\n      |\n      |\n      |\n      |\n=========",
        "  +---+\n  O   |\n  |   |\n      |\n      |\n      |\n=========",
        "  +---+\n  O   |\n /|   |\n      |\n      |\n      |\n=========",
        "  +---+\n  O   |\n /|\\  |\n      |\n      |\n      |\n=========",
        "  +---+\n  O   |\n /|\\  |\n /    |\n      |\n      |\n=========",
        "  +---+\n  O   |\n /|\\  |\n / \\  |\n      |\n      |\n========="
    };

    cout << stages[Gabimet] << endl;
}

int main() {
    cout << "Miresevini ne Hangman!\n";
    cout << "Lojtari 1, shkruani 4 fjal per lojtarin 2 qe ai ti supozoj, te ndara me hapsira: ";

    vector<string> fjalet(4);
    for (int i = 0; i < 4; ++i) {
        cin >> fjalet[i];
    }

    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif

    const int numriIProvave = 6;

    srand(time(0));
    int rastesi = rand() % 4;
    Hangman loja(fjalet[rastesi], numriIProvave);

    while (!loja.fund()) {
        cout << "Fjala aktuale: ";
        loja.shfaqFjalen();
        loja.shfaqShkronjatEGjetura();
        cout << "Provat e mbetura: " << loja.kalkulimiiprovave() << endl;
        shfaqHangman(loja.merrGabimet());
        cout << "Lojtari 2, supozoni nje shkronj: ";
        char supozimi;
        cin >> supozimi;

        if (!isalpha(supozimi)) {
            cout << "Karakter i pavlershem! Ju lutem jepni një shkronje te vlershme." << endl;
            continue;
        }

        loja.supozoShkronjen(supozimi);
        cout << endl;
    }

    if (loja.gjetja()) {
        cout << "Urime! Ju gjetet fjalen: " << fjalet[rastesi] << endl;
    } else {
        cout << "Me falni, nuk keni me prova! Fjala ishte: " << fjalet[rastesi] << endl;
        shfaqHangman(numriIProvave);
    }

    return 0;
}
