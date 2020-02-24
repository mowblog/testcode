#include <stdio.h>
#include <curses.h>

int fun1(int var1)
{
	if(start_color() != OK)
	{
		addstr("init failed\n");
		return -1;
	}
	else
	{
		init_pair(1,COLOR_RED,COLOR_BLACK);
		attron(COLOR_PAIR(1));
		addstr("=========\n");
		attroff(COLOR_PAIR(1));
		return 0;
	}
}

int fun2(int var2)
{
	if(start_color() != OK)
	{

		addstr("init failed\n");
		return -1;
	}
	else
	{
		init_pair(2,COLOR_GREEN,COLOR_BLACK);
		attron(COLOR_PAIR(2));
		addstr("===   ===\n");
		attroff(COLOR_PAIR(2));
		return 0;
	}

}

int main(int argc, char* argv[])
{
	int (*array[3])(int)={fun1,0,0};
	WINDOW *wnd;

	wnd=initscr();
	addstr("begin test...\n");
	echo();
	refresh();

	array[1]=fun2;
	(*array[0])(8);
	(*array[1])(0);

	refresh();
	endwin();

	return 0;
}
