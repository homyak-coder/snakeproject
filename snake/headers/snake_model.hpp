#ifndef SNAKE_SHARED
#define SNAKE_SHARED
#include "snake_shared.hpp"
#endif

/**
 * @brief Класс, содержащий модель игры
 * Обновляется с заданной частотой, реализует хранение змеи на двусвязном списке,
 * хранит поле, как двумерный вектор состояний
 * выполняет команды от контроллера, умеет возвращать своё состояние
 * @param clock счётчик времени
 * @param width ширина поля в клетках
 * @param height высота поля в клетках
 * @param freq частота обновления модели (раз в секунду)
 * @param difficulty_ сложность игры (скорсть увеличения частоты)
 * @param finished флаг, сигнализирующий об окончании игры
 * @param snake_direction направление змеи
 * @param snake сущность змеи (список координат каждого её узла)
 * @param field двумерный вектор состояний поля
 */

class SnakeModel
{
private:
  sf::Clock clock;
  const int width;
  const int height;
  int freq;
  const int difficulty_;
  bool finished;
  int fruits_value;
  struct SnakeNode
  {
    int y;
    int x;
  };
  enum class Direction {left, right, up, down};
  Direction snake_direction;
  list<SnakeNode> snake;
  vector<vector<State>> field;

  bool not_so_fast();
  void generate_fruits();

public:
  bool not_finished();
  SnakeModel(const int, const int, const int, const int);

  void read_cmd(Command);
  void update();
  vector<vector<State>> get_state();
};
