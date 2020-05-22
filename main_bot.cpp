#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include <cstdlib>
#include "snake.hpp"

int main()
{
  SnakeModel model(40, 40, 10, 1);
  SnakeView view(40, 40, 20, 60);
  sf::RenderWindow& window = view.get_window();
  SnakeBotController bot(window, 50);
  while (model.not_finished())
  {
    bot.update(model.get_state());
    model.read_cmd(bot.get_cmd());
    model.update();
    view.update(model.get_state());
  }

  return 0;
}
