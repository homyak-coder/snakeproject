/**
 *@file snake_bot.cpp
*/

#include "../headers/snake_bot.hpp"
/**
 * @brief Функция для выдержки частоты обновления
 * @return true, если рано обновляться, true, если пора
 */
bool SnakeBotController::not_so_fast()
{
  if (clock.getElapsedTime().asMilliseconds() >= 1000 / freq)
  {
    clock.restart();
    return false;
  }
  return true;
}
/**
 * @brief Конструктор класса бота
 * @param window ссылка на окно
 * @param f Частота обновления
 *
 */
SnakeBotController::SnakeBotController(sf::RenderWindow& window, const int f) :
window_(window), freq(f), cmd(Command::pass)
{}
  /**
   * @brief Функция обновления бота.
   * Получает модель, отслеживает нажатие на крестик
   * видит цель, не видит препятствий
   * @param model двумерный вектор состояний клеток
   */
void SnakeBotController::update(vector<vector<State>> model)
{
  if (window_.pollEvent(event))
    if (event.type == sf::Event::Closed)
        cmd = Command::finish;
  if (not_so_fast())
    return;
  int snake_x = 0, snake_y = 0;
  int target_x = 0, target_y = 0;
  bool flag = true;
  for (int i = 0; i < model.size(); ++i)
    for (int j = 0; (j < model[0].size()) && (flag); ++j)
      if (model[i][j] == State::head)
      {
        snake_x = j;
        snake_y = i;
        flag = false;
        break;
      }
  flag = true;
  for (int i = 0; i < model.size(); ++i)
    for (int j = 0; (j < model[0].size()) && (flag); ++j)
      if (model[i][j] == State::fruit)
      {
        target_x = j;
        target_y = i;
        flag = false;
        break;
      }
  if (snake_x < target_x)
    cmd = Command::right;
  if (snake_x > target_x)
    cmd = Command::left;
  if (snake_y < target_y)
    cmd = Command::down;
  if (snake_y > target_y)
    cmd = Command::up;
}
/**
 * @brief Возвращает команду от бота модели
 * @return команда от бота модели
 */
Command SnakeBotController::get_cmd()
{
  return cmd;
}
