#include <SDL2/SDL_rect.h>

#include <random>
#include <stack>
#include <vector>

#include "Generators/generators.h"
#include "maze.h"

void Generators::randomDFS(Mazes::Maze& maze) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<> rand(0, 1);

	maze.clear(true);

	std::stack<SDL_Point> stack;
	maze.at(0, 0) |= Mazes::VISITED;
	stack.push({0, 0});

	std::vector<SDL_Point> neighbors;
	neighbors.reserve(4);

	while (!stack.empty()) {
		neighbors.clear();

		auto [x, y] = stack.top();
		stack.pop();

		if (x > 0 && (maze.at(x - 1, y) & Mazes::VISITED) == 0) {
			neighbors.push_back({x - 1, y});
		}
		if (x < maze.getWidth() - 1
		    && ((maze.at(x + 1, y) & Mazes::VISITED) == 0)) {
			neighbors.push_back({x + 1, y});
		}
		if (y > 0 && ((maze.at(x, y - 1) & Mazes::VISITED) == 0)) {
			neighbors.push_back({x, y - 1});
		}
		if (y < maze.getHeight() - 1
		    && ((maze.at(x, y + 1) & Mazes::VISITED) == 0)) {
			neighbors.push_back({x, y + 1});
		}

		if (!neighbors.empty()) {
			stack.push({x, y});
			auto [nx, ny] =
				neighbors.at((unsigned)(rand(gen) * (float)neighbors.size()));
			// NOLINTBEGIN(*signed-bitwise)
			if (nx > x) {
				maze.at(x, y) &= ~Mazes::RIGHT_WALL;
			} else if (nx < x) {
				maze.at(nx, ny) &= ~Mazes::RIGHT_WALL;
			} else if (ny > y) {
				maze.at(x, y) &= ~Mazes::BOTTOM_WALL;
			} else {
				maze.at(nx, ny) &= ~Mazes::BOTTOM_WALL;
			}
			// NOLINTEND(*signed-bitwise)
			maze.at(nx, ny) |= Mazes::VISITED;
			stack.push({nx, ny});
		}
	}
}
