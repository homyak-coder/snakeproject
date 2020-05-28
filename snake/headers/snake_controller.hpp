#ifndef SNAKE_SHARED
#define SNAKE_SHARED
#include "snake_shared.hpp"
#endif
/**
 * @brief Класс, реализующий контроллер
 * Обновляется с определённой частотой, получает события от окна,
 * отдаёт команды модели
 */
class SnakeUserController
{
private:
  sf::Clock clock;
  sf::Event event;
  sf::RenderWindow& window_;
  queue<Command> commands_queue;
  const int freq;
  bool not_so_fast();
public:
  SnakeUserController(sf::RenderWindow&, const int);
  void update();
  Command get_cmd();
};
