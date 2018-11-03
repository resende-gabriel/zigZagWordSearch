//Gabriel Resende de Andrade
#include<iostream>
#include<sstream>
#include<vector>
#include"WordSearch.hpp"

using namespace std;


vector<string> WordSearch::splitTextIntoWords(string text) {
    istringstream iss(text); // armazena a sequencia de caracteres completa para separar as palavras por espacos
    string textWord;
    vector<string> words;
    
    while(iss >> textWord) {
        words.push_back(textWord); // armazena a palavra separada em um vector de strings
    }
    return words;
}


void WordSearch::setWord(string inputWord) {
    for(auto & letter: inputWord) { // converte caractere por caractere da palavra para maiusculo
        letter = toupper(letter);
    }
    this->word = inputWord;
}


vector<coordinate> WordSearch::searchInGrid() {
    vector<coordinate> coordinates;
    this->occurrences = 0; // zera as ocorrencias da palavra antes de iniciar a busca
    for(int i = 0; i < GRID_SIZE; ++i) {
        for(int j = 0; j < GRID_SIZE; ++j) {
            if(grid[i][j] == word[0]) { // percorre o grid posicao por posicao comparando as letras com a primeira letra da palavra a ser pesquisada
                if(this->checkIfWordMatch(i, j, coordinates)) { // busca a palavra em zigzag a partir da primeira letra igual encontrada, verificando se os caracteres restantes sao iguais
                    coordinate c; // se a palavra for encontrada a partir dessa posicao, as posicoes das ultimas letras ja foram inseridas na funcao, faltando apenas a posicao da primeira
                    c.lin = i;
                    c.col = j;
                    coordinates.push_back(c);
                }
            }
        }
    }
    return coordinates; // retorna um vector com as coordenadas de todas as letras das palavras encontradas
}


bool WordSearch::checkIfWordMatch(int lin, int col, vector<coordinate> &coordinates) {
    if(word.size() <= 1) { // se a palavra possuir apenas uma letra, a comparacao ja foi terminada ao chamar a funcao
        this->occurrences++; // incrementa o numero de ocorrencias e retorna true
        return true;
    }
    
    int occurrencesBeforeSearch = this->occurrences; // variavel utilizada de parametro para contar as ocorrencias corretamente caso hajam palavras espelhadas
    string wordEnd = word.substr(1); // variavel sem a primeira letra da palavra original, que ja foi comparada
    
    // procura a palavra nas 4 direcoes possiveis
    this->countOccurrAllZigZagDirections(wordEnd, lin, col, coordinates);
    if(occurrencesBeforeSearch < this->occurrences) // se o numero de ocorrencias for diferente do numero antes da busca, significa que foram encontrados resultados
        return true;
    
    return false;
}


/* chama a funcao com as 8 possibilidades possiveis (2 para cada conjunto de direcoes) */
void WordSearch::countOccurrAllZigZagDirections(string wordEnd, int lin, int col, vector<coordinate> &coordinates) {
    int lastCol = 0; // variavel para distinguir a direcao da busca com as 2 possibilidades
    if(col == lastCol) // se a ultima coluna for igual a coluna atual, a busca comecara na horizontal, mudando a coluna atual
        lastCol = 1; // se a ultima coluna for diferente da coluna atual, a busca comecara na vertical, mudando a linha atual
    
    if(this->searchZigZag(wordEnd, lin, col, col, coordinates, "down-right")) // incrementa as ocorrencias se a palavra for encontrada em uma das direcoes
        this->occurrences++;
    if(this->searchZigZag(wordEnd, lin, col, lastCol, coordinates, "down-right"))
        this->occurrences++;
    if(this->searchZigZag(wordEnd, lin, col, col, coordinates, "down-left"))
        this->occurrences++;
    if(this->searchZigZag(wordEnd, lin, col, lastCol, coordinates, "down-left"))
        this->occurrences++;
    if(this->searchZigZag(wordEnd, lin, col, col, coordinates, "up-right"))
        this->occurrences++;
    if(this->searchZigZag(wordEnd, lin, col, lastCol, coordinates, "up-right"))
        this->occurrences++;
    if(this->searchZigZag(wordEnd, lin, col, col, coordinates, "up-left"))
        this->occurrences++;
    if(this->searchZigZag(wordEnd, lin, col, lastCol, coordinates, "up-left"))
        this->occurrences++;
}


/* compara recursivamente as letras a partir de uma posicao especifica do grid */
bool WordSearch::searchZigZag(string wordEnd, int lin, int col, int lastCol, vector<coordinate> &coordinates, string searchType) {
    if(!this->updatePositionByDirection(lin, col, lastCol, searchType)) // segue para a proxima posicao a ser comparada de acordo com a posicao atual e a direcao da busca
        return false;
    if(grid[lin][col] != wordEnd[0]) // se a letra da posicao atual for diferente da letra a ser comparada da palavra, interrompe a comparacao
        return false;
    
    if(wordEnd.size() > 1) // enquanto a palavra tiver mais que 1 caractere, continua comparando letra por letra recursivamente, removendo a primeira letra da palavra atual para a proxima comparacao
        if(!this->searchZigZag(wordEnd.substr(1), lin, col, lastCol, coordinates, searchType)) // se uma letra diferente for encontrada, retorna falso para as chamadas recursivas
            return false;
    
    this->insertCoordinate(lin, col, coordinates); // se a funcao nao foi interrompida, todas as letras foram comparadas e sao iguais, entao suas posicoes serao armazenadas
    // armazena as coordenadas de cada letra a medida que as funcoes recursivas sao desempilhadas e retorna true (pois a palavra foi encontrada em zigzag a partir da posicao inicial passada de parametro)
    return true;
}


/* atualiza os valores da linha e da coluna de acordo com a direcao e o ultimo movimento */
bool WordSearch::updatePositionByDirection(int &lin, int &col, int &lastCol, string searchType) {
    if(searchType == "down-right") { // se a busca consiste em movimentos para baixo e para direita, as linhas e colunas so' podem ser incrementadas
        if(col == lastCol && col < (this->GRID_SIZE - 1)) { // se a coluna e' igual a coluna da ultima posicao analisada, significa que o ultimo movimento foi na vertical (no caso, para baixo)
            col++; // move para a direita incrementando a coluna
        } else if(lin < (this->GRID_SIZE - 1)) {
            lastCol = col; // move para baixo incrementando a linha e define a ultima coluna analisada na variavel
            lin++;
        } else {
            return false;
        }
    } else if(searchType == "down-left") { // se a busca consiste em movimentos para baixo e para esquerda, as linhas so' podem ser incrementadas e as colunas so' podem ser decrementadas
        if(col == lastCol && col > 0) {
            col--; // move para a esquerda decrementando a coluna
        } else if(lin < (this->GRID_SIZE - 1)) {
            lastCol = col; // move para baixo incrementando a linha e define a ultima coluna analisada na variavel
            lin++;
        } else {
            return false;
        }
    } else if(searchType == "up-right") { // se a busca consiste em movimentos para cima e para direita, as linhas so' podem ser decrementadas e as colunas so' podem ser incrementadas
        if(col == lastCol && col < (this->GRID_SIZE - 1)) {
            col++; // move para a direita incrementando a coluna
        } else if(lin > 0) {
            lastCol = col; // move para cima decrementando a linha e define a ultima coluna analisada na variavel
            lin--;
        } else {
            return false;
        }
    } else if(searchType == "up-left") { // se a busca consiste em movimentos para cima e para esquerda, as linhas e colunas so' podem ser decrementadas
        if(col == lastCol && col > 0) {
            col--; // move para a esquerda decrementando a coluna
        } else if(lin > 0) {
            lastCol = col; // move para cima decrementando a linha e define a ultima coluna analisada na variavel
            lin--;
        } else {
            return false;
        }
    }
    return true;
}


/* verifica se a coordenada existe no vetor e insere caso contrario */
bool WordSearch::insertCoordinate(int lin, int col, vector<coordinate> &coordinates) {
    for(vector<coordinate>::iterator it = coordinates.begin(); it != coordinates.end(); ++it) { // verifica se a posicao ja esta armazenada
        if(it->col == col && it->lin == lin)
            return false;
    }
    coordinate coord; // armazena a posicao se a mesma nao existir no vector de coordenadas
    coord.lin = lin;
    coord.col = col;
    
    coordinates.push_back(coord);
    return true;
}


/* exibe a quantidade de ocorrencias da(s) palavra(s) e, se for maior que 0, chama a funcao para exibir as posicoes no grid */
void WordSearch::printWordOccurrences(vector<coordinate> coordinates, int totalOccurrences) {
    if(totalOccurrences > 0) {
        cout << endl << totalOccurrences << " ocorrencia(s) para a(s) palavra(s)"; // exibe a(s) palavra(s) encontradas
        for(vector<string>::iterator word = this->foundWords.begin(); word != this->foundWords.end(); ++word) {
            cout << " '" << (*word) << "'";
        }
        cout << endl;
        this->printCoordinatesChar(coordinates);
    }
    if(this->notFoundWords.size() > 0) {
        cout << "Nenhuma ocorrencia para a(s) palavra(s)"; // exibe a(s) palavra(s) nao encontradas
        for(vector<string>::iterator word = this->notFoundWords.begin(); word != this->notFoundWords.end(); ++word) {
            cout << " '" << (*word) << "'";
        }
        cout << endl << endl;
    }
}


/* monta um grid apenas com * e substitui as posicoes das coordenadas que formam a palavra pelas letras originais */
void WordSearch::printCoordinatesChar(vector<coordinate> coordinates) {
    string wordSquare[GRID_SIZE] = { "***************", "***************", "***************", "***************", "***************", "***************", "***************", "***************", "***************", "***************", "***************", "***************", "***************", "***************", "***************" };
    for(vector<coordinate>::iterator it = coordinates.begin(); it != coordinates.end(); ++it) { // percorre o vetor de coordenadas substituindo os asteriscos pelas letras originais da(s) palavra(s) encontrada(s)
        wordSquare[it->lin][it->col] = grid[it->lin][it->col];
    }
    cout << endl;
    for(int i = 0; i < GRID_SIZE; ++i) { // percorre o array de strings exibindo os caracteres separados por espaco e quebrando a linha no fim de cada sequencia
        for(int j = 0; j < GRID_SIZE; ++j) {
            cout << wordSquare[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


/* percorre o array de strings (que e' tratado como uma matriz de caracteres),
exibindo as letras separadas por espaco e quebrando a linha no fim de cada sequencia */
void WordSearch::printSquare() { 
    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


/* recebe um texto e separa as palavras por espaco, buscando cada uma no grid */
void WordSearch::findWords(string text) {
    vector<coordinate> allWordsCoordinates; // variavel para armazenar as coordenadas de todas as palavras informadas
    vector<coordinate> currentCoordinates; // variavel para armazenar as coordenadas da palavra atual a ser buscada
    vector<string> inputWords = this->splitTextIntoWords(text);
    this->foundWords.clear();
    this->notFoundWords.clear();
    int totalOccurrences = 0;
    
    for(vector<string>::iterator word = inputWords.begin(); word != inputWords.end(); ++word) { // procura cada palavra no grid, armazenando as ocorrencias e posicoes
        this->setWord(*word);
        currentCoordinates = this->searchInGrid(); // insere as coordenadas encontradas no vector com todas as coordenadas
        allWordsCoordinates.insert(allWordsCoordinates.end(), currentCoordinates.begin(), currentCoordinates.end());
        totalOccurrences += occurrences;
        if(currentCoordinates.size() > 0) { // determina se a palavra foi encontrada ou nao a partir das coordenadas retornadas, e armazena em um vector para exibicao posterior
            this->foundWords.push_back(*word);
        } else {
            this->notFoundWords.push_back(*word);
        }
    }
    this->printWordOccurrences(allWordsCoordinates, totalOccurrences);
}