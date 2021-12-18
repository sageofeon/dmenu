/*****************************************************
*	Serge Bash
*
**********************DYNAMIC MENU OF ITEMS***********
*  Use menu( char *item[],  unsigned int count_item )
*  Where "item" is array of items for menu
*	And "count_item" is count of items of menu
*	For exit press ESC key
******************************************************/

#ifdef __linux__ 
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#elif _WIN32
#include "curses.h"
#include "wchar.h"
#include "locale.h"
#else
#endif
#include "string.h"
#define	PRINT( val ) printf("\n %s\n", val);

/*** DRAWS A BORDER AROUND THE ITEM ***/
void frame(char *item)
{
    int i, len;
    len = strlen(item);
    printf("%c", 0xC9);
    for( i=0; i<len; i++ ) printf("%c", 0xCD);
    printf("%c", 0xBB);
    printf("\n%c", 0xBA); printf( item ); printf("%c\n", 0xBA);
    printf("%c", 0xC8);
    for( i=0; i<len; i++ ) printf("%c", 0xCD);
    printf("%c", 0xBC);
}

/*** SHOWS THE CURRENT ITEM IN THE FRAME AND ALL OTHER ITEMS***/
unsigned int  menu_items(  char *item[],
                        unsigned int cur_item,
                        unsigned int count_item,
                        unsigned int ch ) 		  /* 80  DOWN key */
                                                    /*	 72  UP key  	*/
{
    int i;

    if ( (ch == 80 ) && ( cur_item != (count_item - 1) ) )
          cur_item++;
    else if ( (ch == 72) &&  ( cur_item != 0 ) )
          cur_item--;
    else if ( ( ch == 80 ) && ( cur_item == (count_item - 1) ) )
            cur_item = 0;
    else if ( ( ch == 72 ) && ( cur_item == 0 ) )
            cur_item = count_item - 1;

    for ( i = 0; i < count_item; i ++ )
    {
        if ( i == cur_item )
        {
            frame( item[ cur_item ] );
        }
        else
        {
            PRINT( item[i] );
         }
    }

    return cur_item;
}


void menu( char *item[],  unsigned int count_item )
{
    unsigned int crtl, ch = 0,
                 cur_item = 0;
#ifdef __linux__
   menu_items( item, cur_item, count_item, 0);
   while ( 1 )
    {
        crtl = getch();
        if ( crtl == 27 )
        {
            crtl = getch();
            if ( crtl == 91 )
            {
                ch = getch();
                clear(); 
                refresh();
                cur_item = menu_items( item, cur_item, count_item, ch );
                PRINT("");
            }
        }	
    } 
#elif _WIN32
    system("cls");
    menu_items( item, cur_item, count_item, 0);

    while ( 1 )
     {
        crtl = getch();
        if ( crtl == 27 )  // ESC key
            break;
        ch = getch();

        system( "cls" );
        cur_item = menu_items( item, cur_item, count_item, ch );
    }
#else
#endif
}


int main()
{
#ifdef __linux__
    setlocale(LC_ALL, "ru_RU.UTF-8");

    WINDOW *wnd;

    wnd = initscr(); // curses call to initialize window
    cbreak(); // curses call to set no waiting for Enter key
    noecho(); // curses call to set no echoing
    clear(); // curses call to clear screen, send cursor to position (0,0)
    refresh(); // curses call to implement all changes since last refresh
#endif
    
    char 	*item[] = { "item1", "item2",  "item3", "item4", "item5", "item6", "item7" };
    unsigned int count = sizeof(item) / sizeof(item[0]);

    menu( item,  count );
#ifdef __linux__
    endwin(); // curses call to restore the original window and leave
#endif
    return 0;
}
