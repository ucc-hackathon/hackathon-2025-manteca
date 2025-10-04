#include <iostream>
#include <ctime>
#include <cstdlib>

typedef struct {
    int x;
    int y;
    char value;
} position;

class Board
{
private:
    char *pieces;
    int size;
    position **matrix;

public:
   Board(int s) : size(s) {
        if (size < 2) size = 2;         
        matrix = new position*[size];
        for(int i = 0; i < size; i++)
            matrix[i] = new position[size];

        pieces = new char[size*size/2];

        std::srand(static_cast<unsigned>(std::time(nullptr)));
        init_empty_matrix();
    }
    ~Board() {
        for(int i = 0; i < size; i++)
            delete[] matrix[i];
        delete[] matrix;
        delete[] pieces;
    }

    void init_empty_matrix() {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++) {
                matrix[i][j].x = i;
                matrix[i][j].y = j;
                matrix[i][j].value = '-';
            }
    }

    char get_piece(int x) 
    {
        switch (x)
        {
        case 1: return 185;
        case 2: return 186;
        case 3: return 187;
        case 4: return 188;
        case 5: return 200;
        case 6: return 201;
        case 7: return 202;
        case 8: return 203;
        case 9: return 204;
        case 10: return 205;
        case 11: return 206;
        default: return '?';
        }
    }

    void add_random_piece(int x, int y) {
        if(x >= size || y >= size) return;
        matrix[x][y].value = get_piece(rand() % 11 + 1);
    }

    void add_piece(int x, int y, char val) {
        if(x >= size || y >= size) return;
        matrix[x][y].value = val;
    }

    void piece_set_generator() {
        for(int i = 0; i < size*size/2; i++)
            pieces[i] = get_piece(rand() % 11 + 1);
    }

    void start_game() {
        int val;
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j += 2) {
                std::cout << "Ingrese un simbolo para (" << i << "," << j << "): ";
                std::cin >> val;
                add_piece(i, j, get_piece(val));

                if(j + 1 < size)
                    add_random_piece(i, j + 1);

                show_board();
                system("pause");
                system("cls");
            }
        }
    }

    void show_board() {
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++)
                std::cout << matrix[i][j].value << " ";
            std::cout << std::endl;
        }
    }
};

int main()
{
    Board board(8);
    board.show_board();
    board.piece_set_generator();
    board.start_game();
    return 0;
}
