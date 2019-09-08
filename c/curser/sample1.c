// simple curses example; keeps drawing the inputted characters, in columns
2 // downward, shifting rightward when the last row is reached, and
3 // wrapping around when the rightmost column is reached
4
5 #include <curses.h> // required
6
7 int r,c, // current row and column (upper-left is (0,0))
8 nrows, // number of rows in window
9 ncols; // number of columns in window
10
11 void draw(char dc)
12
13 { move(r,c); // curses call to move cursor to row r, column c
14 delch(); insch(dc); // curses calls to replace character under cursor by dc
15 refresh(); // curses call to update screen
16 r++; // go to next row
17 // check for need to shift right or wrap around
18 if (r == nrows) {
19 r = 0;
20 c++;
21 if (c == ncols) c = 0;
22 }
23 }
24
25 main()
26
27 { int i; char d;
28 WINDOW* wnd;
29
30 wnd = initscr(); // curses call to initialize window
31 cbreak(); // curses call to set no waiting for Enter key
32 noecho(); // curses call to set no echoing
33 getmaxyx(wnd,nrows,ncols); // curses call to find size of window
34 clear(); // curses call to clear screen, send cursor to position (0,0)
35 refresh(); // curses call to implement all changes since last refresh
36
37 r = 0; c = 0;
38 while (1) {
39 d = getch(); // curses call to input from keyboard
40 if (d == ¡¯q¡¯) break; // quit?
41 draw(d); // draw the character
42 }
43
44 endwin(); // curses call to restore the original window and leave
45
46 }
47