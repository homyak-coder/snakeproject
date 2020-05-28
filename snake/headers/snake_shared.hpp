#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <cstdlib>
/**
 * @brief Файл с общимим для сущностей игры типами данных
 */
using namespace std;
enum class State {snake, fruit, wall, empty, head};
enum class Command {pass, finish,left, right, up, down};
