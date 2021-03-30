#ifndef PONG_BALL_HPP
#define PONG_BALL_HPP

#include <random>

enum Direction {
	NONE,
	LEFT,
	RIGHT,
	UPRIGHT,
	DOWNRIGHT,
	UPLEFT,
	DOWNLEFT
};

class Ball {
	public:
		Ball(int, int, int);
		inline int getY() const { return y; }
		inline int getX() const { return x; }
		inline int getSpeed() const { return speed; }
		inline Direction getDirection() const { return direction; }
		inline void setY(const int &x) { this->y = y; }
		inline void setX(const int &x) { this->x = x; }
		inline void setDirection(const Direction &direction) { this->direction = direction; }
		void draw() const;
		void move();;
		void setRandomDirection();
		void setProperties(int, int, Direction);
	private:
		int initialX, initialY;
		int x,y;
		int speed;
		Direction direction;
};

Ball::Ball(int y,int x, int speed) {
	this->y = y;
	this->x = x;
	initialY = y;
	initialX = x;
	this->speed = speed;
	direction = NONE;
}


void Ball::draw() const {
	mvaddch(y,x,'O');
}

void Ball::move() {
	switch (direction) {
		case NONE:
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UPRIGHT:
			x++;
			y--;
			break;
		case UPLEFT:
			x--;
			y--;
			break;
		case DOWNRIGHT:
			x++;
			y++;
			break;
		case DOWNLEFT:
			x--;
			y++;
			break;
		default:
			break;
	}
}

void Ball::setRandomDirection() {
	std::random_device random_device;
	std::mt19937 random_engine(random_device());
	std::uniform_int_distribution<int> distribution_1_100(1, 2);

	auto const randomNumber = distribution_1_100(random_engine);

	setDirection( randomNumber % 2 ? LEFT : RIGHT );
}

void Ball::setProperties(int x, int y, Direction direction) {
	setX(x);
	setY(y);
	setDirection(direction);
}

#endif // PONG_BALL_HPP