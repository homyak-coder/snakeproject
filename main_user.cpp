#include <SFML/Graphics.hpp>
#include "snake/headers/snake.hpp"

/**
 * @brief Main для управления клавиатурой
 * @param args Аргументы в следующем порядке: ширина поля, высота поля, размер клетки, частота модели, частота отрисовка, частота контроллера, сложность
 *
 * @return Program exit status
 */

int main(int k, char* args[])
{
  const int width = stoi(args[1]);
  const int height = stoi(args[2]);
  const int cell_size = stoi(args[3]);
  const int model_freq = stoi(args[4]);
  const int view_freq = stoi(args[5]);
  const int controller_freq = stoi(args[6]);
  const int difficulty = stoi(args[7]);

  SnakeModel model(width, height, model_freq, difficulty);
  SnakeView view(width, height, cell_size, view_freq);
  sf::RenderWindow& window = view.get_window();
  SnakeUserController controller(window, controller_freq);
  while (model.not_finished())
  {
    controller.update();
    model.read_cmd(controller.get_cmd());
    model.update();
    view.update(model.get_state());
  }

  return 0;
}
