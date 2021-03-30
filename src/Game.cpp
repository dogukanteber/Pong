#include <iostream>
#include <ncurses.h>
#include "../include/Paddle.hpp"
#include "../include/Ball.hpp"

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 24;

bool quit = false;

Paddle paddle1(SCREEN_HEIGHT/2, PADDLE_MARGIN);
Paddle paddle2(SCREEN_HEIGHT/2, SCREEN_WIDTH-PADDLE_MARGIN);
Ball ball(SCREEN_HEIGHT/2, SCREEN_WIDTH/2,2);

void init() {
	initscr();
	cbreak();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	timeout(50);

	ball.setRandomDirection();
}

void drawBoard() {
	for ( int i=0; i<SCREEN_HEIGHT; i++ ) {
		mvaddch(i,SCREEN_WIDTH/2, '|');
	}
	for ( int i=0; i<SCREEN_WIDTH; i++ ) {
		mvaddch(0,i,'-');
		mvaddch(SCREEN_HEIGHT, i,'-');
	}
	for ( int i=1; i<SCREEN_HEIGHT; i++ ) {
		mvaddch(i,0,'*');
		mvaddch(i,SCREEN_WIDTH,'*');
	}

}

void printScores() {
	mvprintw(SCREEN_HEIGHT/2 -10, SCREEN_WIDTH/2-10, "%d" ,paddle1.getScore());
	mvprintw(SCREEN_HEIGHT/2 -10, SCREEN_WIDTH/2+10, "%d" ,paddle2.getScore());
}


bool checkLowerBound(const Paddle &paddle) {
	return SCREEN_HEIGHT > paddle.getY() + PADDLE_LENGTH;
}

bool checkUpperBound(const Paddle &paddle) {
	return paddle.getY() > 1;
}

void keyEvents() {
	int ch;
	ch = getch();
	switch ( ch ) {
		case 'q':
			quit = true;
			break;
		case 'w':
			if ( checkUpperBound(paddle1) )
				paddle1.moveUp();
			break;
		case 's':
			if ( checkLowerBound(paddle1) )
				paddle1.moveDown();
			break;
		case KEY_UP:
			if ( checkUpperBound(paddle2) )
				paddle2.moveUp();
			break;
		case KEY_DOWN:
			if ( checkLowerBound(paddle2) )
				paddle2.moveDown();
			break;
		case ' ':
			if ( paddle1.getTurn() ) {
				paddle1.setTurn(false);
				ball.setDirection(RIGHT);			
			}
			else if ( paddle2.getTurn() ) {
				paddle2.setTurn(false);
				ball.setDirection(LEFT);
			}
			break;
		default:
			break;
	}
}

// keeps the ball in the vertical bounds
void boardCollision(Ball &ball) {
	if ( ball.getY() <= 0 && ball.getDirection() == Direction(UPRIGHT) )
		ball.setDirection(DOWNRIGHT);
	else if ( ball.getY() >= SCREEN_HEIGHT && ball.getDirection() == Direction(DOWNRIGHT) )
		ball.setDirection(UPRIGHT);
	else if ( ball.getY() <= 0 && ball.getDirection() == Direction(UPLEFT) )
		ball.setDirection(DOWNLEFT);
	else if ( ball.getY() >= SCREEN_HEIGHT && ball.getDirection() == Direction(DOWNLEFT) )
		ball.setDirection(UPLEFT);
}

// collision detection for paddles
void paddleCollision(Paddle &p1, Paddle &p2, Ball &ball) {
	// if the ball touches the paddle
	if ( ball.getX() == p1.getX() && ( ball.getY() >= p1.getY() && ball.getY() <= p1.getY() + 4) ) {
		// if the ball is hit from at the end of the paddle, go appropriate direction
		if ( ball.getY() == p1.getY() + 3 || ball.getY() == p1.getY() + 4 )
			ball.setDirection(DOWNRIGHT);
		// if the ball is hit from at the middle of the paddle, go directly the opposite direction
		else if ( ball.getY() == p1.getY() + 2 )
			ball.setDirection(RIGHT);
		// if the ball is hit from at the beginning of the paddle, go appropriate direction
		else if ( ball.getY() == p1.getY() || ball.getY() == p1.getY() + 1 )
			ball.setDirection(UPRIGHT);
	}
	// if the ball touches the paddle
	else if ( ball.getX() == p2.getX() && ( ball.getY() >= p2.getY() && ball.getY() <= p2.getY() + 4 ) ) {
		// if the ball is hit from at the end of the paddle, go appropriate direction
		if ( ball.getY() == p2.getY() + 3 || ball.getY() == p2.getY() + 4 )
			ball.setDirection(UPLEFT);
		// if the ball is hit from at the middle of the paddle, go directly the opposite direction
		else if ( ball.getY() == p2.getY() + 2 )
			ball.setDirection(LEFT);
		// if the ball is hit from at the beginning of the paddle, go appropriate direction
		else if ( ball.getY() == p2.getY() || ball.getY() == p2.getY() + 1 );
			ball.setDirection(DOWNLEFT);
	}
}

// if someone scored reset paddles and put the ball in appropriate position
void checkScore(Paddle &p1, Paddle &p2, Ball &ball) {
	if ( ball.getX() == 0 ) {
		p2.setScore(p2.getScore() + 1);
		p1.setTurn(true);
		p1.reset();
		p2.reset();
		ball.setProperties(p1.getX() + ( PADDLE_MARGIN / 2), p1.getInitialY() - 2, NONE);
	}
	else if ( ball.getX() == SCREEN_WIDTH ) {
		p1.setScore(p1.getScore() + 1);
		p2.setTurn(true);
		p1.reset();
		p2.reset();
		ball.setProperties(p2.getX() - ( PADDLE_MARGIN / 2), p2.getInitialY() - 2, NONE);
	}
}


void collisionDetection() {
	boardCollision(ball);
	paddleCollision(paddle1, paddle2, ball);
}

void render() {
	clear();
	refresh();
	drawBoard();
	printScores();
	ball.draw();
	paddle1.draw();
	paddle2.draw();
	printScores();
}

void play() {
	render();
	collisionDetection();
	checkScore(paddle1, paddle2, ball);
	keyEvents();
	ball.move();
}

void end() {
	endwin();
}

void game() {
	init();
	while ( !quit ) {
		play();
	}
	end();
}

int main(int argc, char const *argv[])
{
	game();
	return 0;
}