//Gabriel Resende de Andrade
#ifndef WORDSEARCH_H
#define WORDSEARCH_H

#include<iostream>
#include<vector>

using namespace std;

struct coordinate { // estrutura para armazenar as posicoes (coluna e linha) das letras da palavra informada na matriz
    int col;
    int lin;
};

class WordSearch {
    private:
        int GRID_SIZE = 15; // variavel para representar o tamanho do grid, que no caso e' de 15x15
        int occurrences = 0; // variavel para armazenar a quantidade de ocorrencias da palavra informada
        
        string grid[15] = { "YCYGWRPKHOABUVH", "SCIRFZBMCPMYCFP", "UAFRXTWLOTASMXC", "EJRAGSAVHGLRXGF", "KXZTAPCVJQMJYMG", "GCXQEWSIALAEOIV", "IFYFXVALPALHETA", "LEKOUUTIGUANAOI", "VHIHZUCIFRACLUB", "ARZHXALCOGEEUVR", "UNBSTMUSICATLAA", "WRAUJABISSNORIS", "CMPLENPALCOAHBE", "TMFOTZMPTRESJRL", "FSIKUFPEQTAMLOJ" };
        string word; // variavel para armazenar a palavra informada em maiusculo
        vector<string> foundWords;
        vector<string> notFoundWords;
        
        bool insertCoordinate(int lin, int col, vector<coordinate> &coordinates); // funcao que recebe uma linha e uma coluna e armazena no vector de coordenadas, se a coordenada nao existir
        bool checkIfWordMatch(int lin, int col, vector<coordinate> &coordinates); // funcao que analisa a busca da palavra em zigzag em todas as direcoes (uma por uma) a partir de uma posicao especifica, contando as ocorrencias
        bool searchZigZag(string wordEnd, int lin, int col, int lastCol, vector<coordinate> &coordinates, string searchType); // funcao que compara as letras do grid com as letras da palavra em zigzag a partir de uma posicao especifica, de acordo com a direcao especificada
        
        void countOccurrAllZigZagDirections(string wordEnd, int lin, int col, vector<coordinate> &coordinates);  // funcao que atualiza a quantidade de ocorrencias de acordo com as buscas em zigzag
        bool updatePositionByDirection(int &lin, int &col, int &lastCol, string searchType); // funcao para atualizar a posicao durante a busca em zigzag, dependendo da direcao a ser analisada
        
        void printWordOccurrences(vector<coordinate> coordinates, int totalOccurrences); // funcao que exibe a quantidade de ocorrencias da palavra e o grid
        void printCoordinatesChar(vector<coordinate> coordinates); // funcao que exibe o grid com asteriscos nas letras que nao pertencem as palavras encontradas
        void setWord(string); // funcao para definir a palavra informada no escopo da classe
        
        vector<string> splitTextIntoWords(string text); // funcao que le um texto e separa em palavras
        vector<coordinate> searchInGrid(); // funcao que percorre o grid
        
    public:
        
        void findWords(string text); // funcao que percorre o grid para buscar uma palavra
        
        void printSquare(); // funcao que exibe o grid do caca-palavras
};

#endif