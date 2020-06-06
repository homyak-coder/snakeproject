/**
 *@file snake_controller.cpp
*/
#include "../headers/snake.hpp"
/**
 * @brief Функция для выдержки частоты обновления
 * @return true, если рано обновляться, true, если пора
 */
bool SnakeUserController::not_so_fast()
{
  if (clock.getElapsedTime().asMilliseconds() >= 1000 / freq)
  {
    clock.restart();
    return false;
  }
  return true;
}
/**
 * @brief Конструктор контроллера
 * @param window Ссылка на окно
 * @param f Частота считывания событий
 */
SnakeUserController::SnakeUserController(sf::RenderWindow& window, const int f) :
window_(window),
freq(f)
{}
  /**
   * @brief Обновление контроллера
   * Читает события с окна (крестик или кнопки), добавляет в очередь команд
   * соответствующую команду
   */
void SnakeUserController::update()
{
  if (not_so_fast())
    return;
  if (window_.pollEvent(event))
    if (event.type == sf::Event::Closed)
        commands_queue.push(Command::finish);

  switch (event.key.code)
  {
    case sf::Keyboard::Key::Up:
      commands_queue.push(Command::up);
    break;
    case sf::Keyboard::Key::Down:
      commands_queue.push(Command::down);
    break;
    case sf::Keyboard::Key::Left:
      commands_queue.push(Command::left);
    break;
    case sf::Keyboard::Key::Right:
      commands_queue.push(Command::right);
    break;
  }
}
/**
 * @brief Извлекает из очереди первую команду и возвращает её
 * @return возвращает последнюю команду, сохранённую в контроллере
 */
Command SnakeUserController::get_cmd()
{
  if (commands_queue.empty())
    return Command::pass;
  Command cmd = commands_queue.front();
  commands_queue.pop();
  return cmd;
}
