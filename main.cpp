//Gabriel Resende de Andrade
#include<iostream>
#include"WordSearch.hpp"

using namespace std;

int main() {
    string word;
    WordSearch ws;
    
    ws.printSquare();
    while(true) {
        cout << "Digite a palavra a ser buscada: " << endl;
        getline(cin, word);
        ws.findWords(word);
    }
	return 0;
}
