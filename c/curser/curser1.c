#include <curses.h>                  /* 引进 curses.h , 并自动引进
stdio.h */


  #define StartX  1                    /* 决定游标初始位置 */
  #define StartY  1

  void initial();

int  main()
  {
     int x=StartX;                     /* 宣告 x,y 并设定其初值
     */

     int y=StartY;
     int ch;                           /* 宣告 ch 为整数,配合 getch()
使用   */


     initial();                        /* 呼叫 initial(), 启动 curses
模式,  */

                                       /* 并完成其它设定
     */


     box(stdscr,'|','-');              /* 画方框
     */


     attron(A_REVERSE);                /* 开启反白模式
     */

     mvaddstr(0,20,"Curses Program");  /* 在 (20,0) 处输出反白字元
     */

     attroff(A_REVERSE);               /* 关闭反白模式
     */


     move(x,y);                        /* 将游标移至初始位置
     */


     do {                              /* 以无限回圈不断等待输入
     */

      ch=getch();                      /* 等待自键盘输入字元*/
      switch(ch) {                     /* 判断输入字元为何
     */


         case KEY_UP: --y;             /* 判断是否"↑"键被按下
     */

                      break;
         case KEY_DOWN: ++y;           /* 判断是否"↓"键被按下
     */

                      break;
         case KEY_RIGHT: ++x;          /* 判断是否"→"键被按下
     */

                      break;
         case KEY_LEFT: --x;           /* 判断是否"←"键被按下
     */

                      break;
         case '\r':                    /* 判断是否 ENTER 键被按下
     */

                   ++y;
                   x=1;
                   break;
         case '\t':                    /* 判断是否 TAB 键被按下
     */

                   x+=7;
                   break;
         case 127:                     /* 判断是否 BACKSPACE 键被按下
     */

                    mvaddch(y,--x,' ');/* delete 一个字元
     */

                    break;

         case 27: endwin();            /* 判断是否[ESC]键被按下
     */

                  exit(1);             /* 结束 curses 模式
     */

                                       /* 结束此程式
     */


         default:
                  addch(ch);           /* 如果不是特殊字元, 将此字元印
出     */

                  x++;
                  break;
       }
       move(y,x);                      /* 移动游标至现在位置
     */

     } while (1);
return 0;
   }

  void initial()                       /* 自定开启 curses 函式
     */

  {
      initscr();
      cbreak();
      nonl();
      noecho();
      intrflush(stdscr,FALSE);
      keypad(stdscr,TRUE);
      refresh();
   }

