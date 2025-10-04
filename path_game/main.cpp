
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>

using std::cout;
#define N 7

int length_str(std::string str) {
    int length = 0;
    for (char c : str) {
        length++;
    }
    return length;
}

enum Direction {NORTH, EAST, SOUTH, WEST};
enum Room_name {H1, H2, H3, H4, H5, H6, H7};

typedef struct {
    bool directions[4];
    int edges[4];
    int num_edges;
} RoomConnections;

typedef struct {
    bool exists;
    bool type;
} Object;

typedef struct 
{
    std::string name;
    RoomConnections connections;
    Object object;
} Room;

class Map {
public:
    Map();
    void add_random_objects();
    Room* return_map();
    int min_size_path();
private:    
    Room rooms[N];
    Object objects[N];
};

Map::Map() {
    rooms[H1].name = "Habitacion 1";
    rooms[H1].connections.directions[SOUTH] = true; 
    rooms[H1].connections.edges[SOUTH] = 2; 
    rooms[H1].connections.directions[NORTH] = false;
    rooms[H1].connections.directions[EAST] = false; 
    rooms[H1].connections.directions[WEST] = false;
    rooms[H1].connections.num_edges = 1;

    rooms[H2].name = "Habitacion 2";
    rooms[H2].connections.directions[SOUTH] = true;
    rooms[H2].connections.edges[SOUTH] = 3; 
    rooms[H2].connections.directions[WEST] = false;
    rooms[H2].connections.directions[NORTH] = false;
    rooms[H2].connections.directions[EAST] = false;
    rooms[H2].connections.num_edges = 1;

    rooms[H3].name = "Habitacion 3";
    rooms[H3].connections.directions[NORTH] = true;
    rooms[H3].connections.edges[NORTH] = 0; 
    rooms[H3].connections.directions[EAST] = true;
    rooms[H3].connections.edges[EAST] = 3; 
    rooms[H3].connections.directions[WEST] = false;
    rooms[H3].connections.directions[SOUTH] = false;
    rooms[H3].connections.num_edges = 2;

    rooms[H4].name = "Habitacion 4";
    rooms[H4].connections.directions[NORTH] = true;
    rooms[H4].connections.edges[NORTH] = 1; 
    rooms[H4].connections.directions[WEST] = true;
    rooms[H4].connections.edges[WEST] = 2; 
    rooms[H4].connections.directions[EAST] = true;
    rooms[H4].connections.edges[EAST] = 2; 
    rooms[H4].connections.directions[SOUTH] = true;
    rooms[H4].connections.edges[SOUTH] = 5; 
    rooms[H4].connections.num_edges = 4;

    rooms[H5].name = "Habitacion 5";
    rooms[H5].connections.directions[WEST] = true;
    rooms[H5].connections.edges[WEST] = 3; 
    rooms[H5].connections.directions[SOUTH] = true; 
    rooms[H5].connections.edges[SOUTH] = 6; 
    rooms[H5].connections.directions[NORTH] = false;
    rooms[H5].connections.directions[EAST] = false;
    rooms[H5].connections.num_edges = 2;

    rooms[H6].name = "Habitacion 6";
    rooms[H6].connections.directions[NORTH] = true;
    rooms[H6].connections.edges[NORTH] = 3;  
    rooms[H6].connections.directions[EAST] = true;
    rooms[H6].connections.edges[EAST] = 6;
    rooms[H6].connections.directions[SOUTH] = false;
    rooms[H6].connections.directions[WEST] = false;
    rooms[H6].connections.num_edges = 2;

    rooms[H7].name = "Habitacion 7";
    rooms[H7].connections.directions[NORTH] = true;
    rooms[H7].connections.edges[NORTH] = 5; 
    rooms[H7].connections.directions[WEST] = true;
    rooms[H7].connections.edges[WEST] = 4; 
    rooms[H7].connections.directions[EAST] = false;
    rooms[H7].connections.directions[SOUTH] = false;
    rooms[H7].connections.num_edges = 2;
}

Room* Map::return_map() {
    return rooms;
}

int Map::min_size_path() {
    int s = 0;
    
    for (int i = 0; i < N; i++) {
        s += rooms[i].connections.num_edges; 
    }

    return s / 2;
}

void Map::add_random_objects() {
    srand(time(0));
    for (int i = 0; i < N; i++) {
        int r_obj = rand() % 2;
        rooms[i].object.exists = r_obj;
        if (r_obj) {
            rooms[i].object.type = rand() % 2;
        }   
    }    
}

class Player {
    public: 
    Player(std::string p, Map m) : path(p), map(m) {
        points = 0;
    }

    void check_path();
    void show_map();

    int get_direction(char c) {
        switch(c) {
            case 'N': return NORTH;
            case 'E': return EAST;
            case 'S': return SOUTH;
            case 'W': return WEST;
            default: return -1;
        }
    }

    private:
    std::string path;
    int points;
    Map map;
};

void Player::check_path()
{
    int start = 0;

    Room* rooms = map.return_map();
    cout << "Iniciando en " << rooms[start].name << "\n";

    for (int i=0; i < length_str(path); i++) {
        int current = get_direction(path[i]);
        
        if (current == -1) {
            std::cout << "Direccion invalida: " << path[i] << "\n";
            continue;
        }
        
        if (rooms[start].connections.directions[current]) {
            start = rooms[start].connections.edges[current];
            std::cout << "A " << rooms[start].name << "\n";
            if (rooms[start].object.exists) {
                if (rooms[start].object.type) {
                    points += 10;
                    std::cout << "Has encontrado un arma! Puntos: " << points << "\n";
                } else {
                    points += 5;
                    std::cout << "Has encontrado comida! Puntos: " << points << "\n";
                }
                rooms[start].object.exists = false;
            }
        } else {
            std::cout << "No puedes avanzar " << rooms[start].name << "\n";
        }

        
    }

    cout << "Puntos totales: " << points << "\n";
}

void Player::show_map()
{
    std::cout << "Mapa del juego:\n";
    Room* rooms = map.return_map();
    for (int i = 0; i < N; i++) {
        std::cout << rooms[i].name << "\n";
        std::cout << "Conexiones: ";
        if (rooms[i].connections.directions[NORTH]) {
            std::cout << "N ";
        }
        if (rooms[i].connections.directions[EAST]) {
            std::cout << "E ";
        }
        if (rooms[i].connections.directions[SOUTH]) {
            std::cout << "S ";
        }
        if (rooms[i].connections.directions[WEST]) {
            std::cout << "W ";
        }
        std::cout << "\n";
        if (rooms[i].object.exists) {
            if (rooms[i].object.type) {
                std::cout << "Objeto: Arma\n";
            } else {
                std::cout << "Objeto: Comida\n";
            }
        } else {
            std::cout << "Objeto: Ninguno\n";
        }
        std::cout << "---------------------\n";
    }
}

int main()
{
    Map map;
    map.add_random_objects();
    Player player("NSEW", map);
    player.show_map();
    player.check_path();
    cout << "Camino minimo para recorrer todas las habitaciones: " << map.min_size_path() << "\n";
  return 0;
}



