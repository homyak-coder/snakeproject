#ifndef SNAKE_SHARED
#define SNAKE_SHARED
#include "snake_shared.hpp"
#endif
/**
 * @brief Класс, реализующий отрисовку
 * Получает состояние модели, отрисовывает в соответствии
 * с общим "интерфейсом" State
 */
class SnakeView
{
private:
  sf::Clock clock;
  sf::RenderWindow window_;
  const int model_width_;
  const int model_height_;
  const int cell_size_;
  const int freq_;
  bool not_so_fast();
public:
  SnakeView(const int, const int, const int, const int);
  sf::RenderWindow& get_window();
  void update(vector<vector<State>> model_state);
};
