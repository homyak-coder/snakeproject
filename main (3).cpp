#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

class SnakeModel
{
private:
  const int width;
  const int height;
  enum class Direction {left, right, up, down};
  enum class State {snake, fruit, wall, empty};
  struct SnakeNode
  {
    int y;
    int x;
  };
  Direction snake_direction;
  list<SnakeNode> snake;
  vector<vector<State>> field;

public:
  SnakeModel(const int _width, const int _height) :
  width(_width), height(_height)
  {
    for(int i = 0; i < 15; ++i)
      snake.push_back(SnakeNode{0, i});

    snake_direction = Direction::right;
    field.resize(width);
    for(int i = 0; i < width; ++i)
    {
      field[i].resize(height);
      for (int j = 0; j < height; ++j)
        field[i][j] = State::empty;
    }
    for(int i = 0; i < 15; ++i)
      field[0][i] = State::snake;
  }
  void change_dir(int dir)
  {
    switch (dir)
    {
      case 0:
        snake_direction = Direction::right;
      break;

      case 1:
        snake_direction = Direction::left;
      break;

      case 2:
        snake_direction = Direction::up;
      break;

      case 3:
        snake_direction = Direction::down;
      break;
    }
  }
  void update()
  {
    for(auto node : snake)
      field[node.y][node.x] = State::empty;

    auto end = snake.end();
    --end;
    for(auto it = snake.begin(); it != end; ++it)
    {
        auto it_next = it;
        ++it_next;
        it->x = it_next->x;
        it->y = it_next->y;
        field[it->y][it->x] = State::snake;
    }
    switch (snake_direction)
    {
      case Direction::right:
        end->x += 1;
      break;
      case Direction::left:
        end->x -= 1;
      break;
      case Direction::up:
        end->y -= 1;
      break;
      case Direction::down:
        end->y += 1;
      break;
    }
    field[end->y][end->x] = State::snake;
  }

  void show()
  {
    for (int i = 0; i < width; ++i)
    {
      cout << endl;
      for (int j = 0; j < height; ++j)
        cout << (int)field[i][j] << ' ';
    }
    cout << endl;
  }

  int get_state(int y, int x)
  {
    return (int)field[y][x];
  }
};

#define R 0
#define L 1
#define U 2
#define D 3

int main()
{
  SnakeModel model(50, 50);
  sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
          window.close();
    }

    window.clear();
    for(int i = 0; i < 50; ++i)
      for(int j = 0; j < 50; ++j)
      {
        sf::RectangleShape cell(sf::Vector2f(20, 20));
        cell.setPosition(20 * j, 20 * i);
        switch (model.get_state(i, j))
        {
          case 0:
            cell.setFillColor(sf::Color::Green);
          break;
          case 1:
            cell.setFillColor(sf::Color::Red);
          break;
          case 2:
            cell.setFillColor(sf::Color::Black);
          break;
          case 3:
            cell.setFillColor(sf::Color::White);
          break;
        }
        window.draw(cell);
      }
    window.display();
    switch (event.key.code)
    {
      case sf::Keyboard::Key::Up:
        model.change_dir(U);
      break;

      case sf::Keyboard::Key::Down:
        model.change_dir(D);
      break;

      case sf::Keyboard::Key::Left:
        model.change_dir(L);
      break;

      case sf::Keyboard::Key::Right:
        model.change_dir(R);
      break;
    }
    model.update();
    for(int i = 0; i < 25000000; ++i);
  }

  return 0;
}
