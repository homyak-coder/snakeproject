#include "snake/headers/snake.hpp"
#include <SFML/Graphics.hpp>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Test moving and model sizes")
{
  const int width = 40;
  const int height = 40;
  const int model_freq = 100000;
  const int difficulty = 2;

  SnakeModel model(width, height, model_freq, difficulty);
  vector<vector<State>> state = model.get_state();
  REQUIRE(state.size() == height);
  REQUIRE(state[0].size() ==  width);
  int snake_x, snake_y;
  bool flag = true;
  Command cmd = Command::right;
  for (int i = 0; i < width; ++i)
    for (int j = 0; (j < height) && (flag); ++j)
      if (state[i][j] == State::head)
      {
        snake_x = j;
        snake_y = i;
        flag = false;
        break;
      }

  for (int test = 0; test < 10; ++test)
  {
    int targ_x = snake_x, targ_y = snake_y;
    if (snake_x > width / 2)
    {
      cmd = Command::left;
      --targ_x;
    } else
    if (snake_x < width / 2)
    {
      cmd = Command::right;
      ++targ_x;
    } else
    if (snake_y > height / 2)
    {
      cmd = Command::up;
      --targ_y;
    } else
    if (snake_y < height / 2)
    {
      cmd = Command::down;
      ++targ_y;
    }
    model.read_cmd(cmd);
    model.update();

    state = model.get_state();

    flag = true;
    for (int i = 0; i < width; ++i)
      for (int j = 0; (j < height) && (flag); ++j)
        if (state[i][j] == State::head)
        {
          snake_x = j;
          snake_y = i;
          flag = false;
          break;
        }
    REQUIRE(targ_x == snake_x);
    REQUIRE(targ_y == snake_y);
  }
}

TEST_CASE("Test fruit collision")
{
  const int width = 40;
  const int height = 40;
  const int model_freq = 100000;
  const int difficulty = 2;

  SnakeModel model(width, height, model_freq, difficulty);
  auto state = model.get_state();
  int fruit_x;
  int fruit_y;

  int snake_x;
  int snake_y;

  bool flag = true;
  for(int i = 0; (i < height) && flag; ++i)
    for(int j = 0; (j < width) && flag; ++j)
      if (state[i][j] == State::fruit)
      {
        flag = false;
        fruit_x = j;
        fruit_y = i;
      }
  flag = true;
  for(int i = 0; (i < height) && flag; ++i)
    for(int j = 0; (j < width) && flag; ++j)
      if (state[i][j] == State::head)
      {
        flag = false;
        snake_x = j;
        snake_y = i;
      }

  if (snake_x > fruit_x)
  for(int i = 0; i < snake_x - fruit_x; ++i)
  {
    model.read_cmd(Command::left);
    model.update();
  }
  if (snake_x < fruit_x)
  for(int i = 0; i < -snake_x + fruit_x; ++i)
  {
    model.read_cmd(Command::right);
    model.update();
  }
  if (snake_y > fruit_y)
  for(int i = 0; i < snake_y - fruit_y; ++i)
  {
    model.read_cmd(Command::up);
    model.update();
  }

  if (snake_y < fruit_y)
  for(int i = 0; i < -snake_y + fruit_y; ++i)
  {
    model.read_cmd(Command::down);
    model.update();
  }
  state = model.get_state();
  int snake_counter = 0;
  for(int i = 0; i < height; ++i)
    for(int j = 0; j < width; ++j)
      if ((state[i][j] == State::head) || (state[i][j] == State::snake))
        ++snake_counter;
  REQUIRE(snake_counter == 2);
}

TEST_CASE("Test wall collision")
{
  const int width = 40;
  const int height = 40;
  const int model_freq = 100000;
  const int difficulty = 2;

  SnakeModel model(width, height, model_freq, difficulty);
  auto state = model.get_state();

  int snake_x;
  int snake_y;

  bool flag = true;
  for(int i = 0; (i < height) && flag; ++i)
    for(int j = 0; (j < width) && flag; ++j)
      if (state[i][j] == State::head)
      {
        flag = false;
        snake_x = j;
        snake_y = i;
      }

  for(int i = 0; i < snake_y; ++i)
  {
    model.read_cmd(Command::up);
    model.update();
  }
  REQUIRE(!model.not_finished());
}
