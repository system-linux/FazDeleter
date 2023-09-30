#include<iostream>
#include<fstream>
#include<random>
#include<chrono>
#include<string>
using namespace std;

long long int GetFileSize(const string& filePath) {
    ifstream file(filePath, ios::binary | ios::ate);
    if (file.is_open()) {
        return static_cast<long long int>(file.tellg());
    }
    return -1;
}

string urandom(long long int length) {
    string randBytes;
    random_device rd;  // Rastgele veri üreteci
    mt19937 gen(rd()); // Mersenne Twister 19937 rastgele sayý üreteci
    uniform_int_distribution<int> distribution(0, 255);

    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    gen.seed(static_cast<unsigned>(seed));
    for (long long int i = 0; i < length; ++i) {
        randBytes.push_back(static_cast<char>(distribution(gen)));
    }

    return randBytes;
}

void DestroyFunc(bool delFile) {
    cout << "Enter your file path->";
    string fPath;
    getline(cin, fPath);
    if (fPath.empty()) {
        cerr << "Error: Empty value!\n";
        return;
    }
    cout << "Enter the number of process repeats->";
    int rn = 1;
    cin >> rn;
    long long int fSize = GetFileSize(fPath);
    if (fSize == -1) {
        cerr << "\aCould not open to measure the size of the file. Try launching the application as administrator or check the existence of the file.\n";
        return;
    }
    for (int j = 0; j < rn + 1; j++) {
        ofstream file(fPath, ios::binary);
        if (file.is_open()) {
            cout << j << ". File size-->\t" << fSize << endl;
            file << urandom(fSize);
            file.close();
        }
        else {
            cerr << "\aFile could not be opened. Try launching the application as administrator or check the existence of the file.\n";
            break;
        }
    }
    if (delFile && remove(fPath.c_str()) != 0) {
        cerr << "\aFile could not be deleted. Try starting the application as administrator.\n";
    }
    else {
        cout << "\aThe process has been completed successfully!\n";
    }
}
int main() {
    while (true) {
        cout << "\n<-------------------- Fazbear Entertainment -------------------->\n";
        cout << "1-->\tGet unreadable my file.\n" << "2-->\tDestroy my file.\n" << "3-->\tClear Screen.\n" << "4-->\tExit.\n" << ">";
        string* option = new string;
        getline(cin, *option);

        if (*option == "1") { DestroyFunc(false); }
        else if (*option == "2") { DestroyFunc(true); }
        else if (*option == "3") { system("cls||clear"); }
        else if (*option == "4") { break; }
        else { cout << "Invalid option\n"; }
    }
    return 0;
}