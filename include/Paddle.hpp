#ifndef PONG_PALETTE_HPP
#define PONG_PALETTE_HPP


#define PADDLE_LENGTH 5
#define PADDLE_MARGIN 4


class Paddle {
	public:
		Paddle(int y, int x);
		inline int getX() const { return x; }
		inline int getY() const { return y; }
		inline int getInitialX() const { return initialX; }
		inline int getInitialY() const { return initialY; }
		inline bool getTurn() const { return turn; }
		inline int getScore() const { return score; }
		inline void setX(const int x) { this->x = x; }
		inline void setY(const int y) { this->y = y; }
		inline void setTurn(const bool &turn) { this->turn = turn; }
		inline void setScore(const int &score) { this->score = score; }
		void draw() const;
		inline void moveUp() { y--; }
		inline void moveDown() { y++; }
		void reset();
	private:
		int y, x;
		int initialY, initialX;
		bool turn;
		int score;
};


/*
	The reason why we subtract PADDLE_LENGTH/2 is to adjust	the paddles right at the middle
*/
Paddle::Paddle(int y, int x) : 
		y(y - PADDLE_LENGTH / 2),
		x(x - PADDLE_LENGTH / 2),
		initialY(y - PADDLE_LENGTH / 2),
		initialX(x - PADDLE_LENGTH / 2),
		turn(false),
		score(0) {
}

void Paddle::draw() const {
	for ( int i=0; i<PADDLE_LENGTH; i++ )
		mvaddch(y+i, x, '|');
}

void Paddle::reset() {
	x = initialX;
	y = initialY;
}

#endif // PONG_PALETTE_HPP