/**
 *@file snake_view.cpp
*/
#include "../headers/snake.hpp"
/**
 * @brief Конструктор класса отрисовки
 * @param model_width ширина поля в клетках
 * @param model_height высота поля в клетках
 * @param cell_size размер клетки в пикселях
 */
SnakeView::SnakeView(const int model_width, const int model_height, const int cell_size, const int freq) :
window_(sf::VideoMode(model_width * cell_size, model_height * cell_size), "Snake"),
model_width_(model_width),
model_height_(model_height),
cell_size_(cell_size),
freq_(freq)
{}
  /**
   * @brief Выдержка частоты обновления
   * @return true, если рано обновляться, true, если пора
   */
bool SnakeView::not_so_fast()
{
  if (clock.getElapsedTime().asMilliseconds() >= 1000 / freq_)
  {
    clock.restart();
    return false;
  }
  return true;
}
/**
 * @brief Возвращает окно, на котором рисует
 */
sf::RenderWindow& SnakeView::get_window()
{
  return window_;
}
/**
 * @brief Перерисовка
 * @param model_state двумерный вектор состояний клеток поля
 * @return ссылка на окно
 */
void SnakeView::update(vector<vector<State>> model_state)
{
  if (not_so_fast())
    return;
  if (window_.isOpen())
  {
    window_.clear();
    for(int i = 0; i < model_height_; ++i)
      for(int j = 0; j < model_width_; ++j)
      {
        sf::RectangleShape cell(sf::Vector2f(cell_size_, cell_size_));
        cell.setPosition(cell_size_ * j, cell_size_ * i);
        switch (model_state[i][j])
        {
          case State::snake:
            cell.setFillColor(sf::Color::Green);
          break;
          case State::fruit:
            cell.setFillColor(sf::Color::Red);
          break;
          case State::wall:
            cell.setFillColor(sf::Color::Blue);
          break;
          case State::empty:
            cell.setFillColor(sf::Color::White);
          break;
          case State::head:
            cell.setFillColor(sf::Color::Yellow);
          break;
        }
        window_.draw(cell);
      }
    window_.display();
  }
}
