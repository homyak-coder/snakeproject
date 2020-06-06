all:
	g++ main_bot.cpp -o snake_bot snake/lib/snake_model.cpp snake/lib/snake_bot.cpp snake/lib/snake_view.cpp -lsfml-graphics -lsfml-system -lsfml-window
	g++ main_user.cpp -o snake_user snake/lib/snake_model.cpp snake/lib/snake_controller.cpp snake/lib/snake_view.cpp -lsfml-graphics -lsfml-system -lsfml-window
	g++ main_test.cpp snake/lib/snake_model.cpp -o test -lsfml-graphics -lsfml-window -lsfml-system
	g++ -o test snake_test.cpp snake/lib/snake_model.cpp -lsfml-system
