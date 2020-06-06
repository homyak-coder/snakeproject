#ifndef SNAKE_SHARED
#define SNAKE_SHARED
#include "snake_shared.hpp"
#endif
/**
 * @brief Класс, реализующий контроллер
 * Обновляется с определённой частотой, получает события от окна,
 * отдаёт команды модели
 * @param clock счётчик времени
 * @param event код события в окне (крестик/кнопка)
 * @param window_ сущность окна
 * @param freq частота поиска новой цели ботом
 * @param commands_queue очередь кодов команд, котрые нужно отдать модели
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
