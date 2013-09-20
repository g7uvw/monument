#include "hooke.h"
//jog menu stuff
void dojog(Motor *Source, Motor *Sink)
{
 int menu_selection = -1;
 int keycounter = 0;
double speedfraction = (1/1000);
 mainloop:
 clear();
 
  menu_selection = jog_menu(Source,Sink);
  switch (menu_selection)
  {
    case KEY_UP:
	keycounter++;
	SetsupplyS(Source->GetSpeed()+Source->GetSpeed()*speedfraction);
	Source->SetSpeed(GetsupplyS());
      break;
    case KEY_DOWN:
	keycounter--;
	SetsupplyS(Source->GetSpeed()-Source->GetSpeed()*speedfraction);
	Source->SetSpeed(GetsupplyS());
      break;
    case 2:
	SettakeupS(Sink->GetSpeed()+30);
	Sink->SetSpeed(GettakeupS());
      break;
    case 3:
      SettakeupS(Sink->GetSpeed()-30);
	Sink->SetSpeed(GettakeupS());
      break;
    case 32:
	Source->EmergencyStop();
	Sink->EmergencyStop();
      break;
    case KEY_F(4):
      //exit to main menu
      goto loopexit;
      
  }
  goto mainloop;

loopexit:
//do something harmless because we can't have a dangling goto jump where nothing happens.
 clear();
main_menu(Source, Sink);
}

int jog_menu(Motor *Source, Motor *Sink)
{
  //ITEM **jog_items;
 // MENU *jog_menu;
  //int n_choices, i;
  //ITEM *cur_item;
  int c, selection;
  
  /* Initialize items */
  //      n_choices = ARRAY_SIZE(jogchoices);
  //      jog_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
  //      for(i = 0; i < n_choices; ++i)
  //              jog_items[i] = new_item(jogchoices[i],jogchoices[i]);
	//jog_items[n_choices] = (ITEM *)NULL;
	//item_opts_off(main_items[3], O_SELECTABLE);
	//item_opts_off(main_items[6], O_SELECTABLE);

	/* Create main menu */
	//jog_menu = new_menu((ITEM **)jog_items);
	
	/* Set menu option not to show the description */
	//menu_opts_off(jog_menu, O_SHOWDESC);

	/* Set fore ground and back ground of the menu */
	//set_menu_fore(jog_menu, COLOR_PAIR(1) | A_REVERSE);
	//set_menu_back(jog_menu, COLOR_PAIR(2));
	//set_menu_grey(jog_menu, COLOR_PAIR(3));

	/* Post the menu */
	//mvprintw(LINES - 5, 0, "Navigate with Arrow Keys, ENTER selects");
	mvprintw(LINES - 20, 0, "Cursor Up = Speed Up Wire Transfer");
	mvprintw(LINES - 19, 0, "Cursor Down = Slow Down Wire Transfer");
	mvprintw(LINES - 18, 0, "SPACE = Emergency Stop");
	mvprintw(LINES - 17, 0, "F4 = exit back to main menu");
	
	
	
	if (Source->Locked){mvprintw(LINES - 3, 0, "Motor 1 is: Locked");}
	else
		mvprintw(LINES - 3, 0, "Motor 1 is: Free");
	
	if (Sink->Locked){mvprintw(LINES - 2, 0, "Motor 2 is: Locked");}
	else
		mvprintw(LINES - 2, 0, "Motor 2 is: Free");
	mvprintw(LINES -1,0,"Source speed %d, Takeup speed %d",GetsupplyS(),GettakeupS());
	//post_menu(jog_menu);
	refresh();

	while((c = getch()) != KEY_F(4))
	{       switch(c)
	        {	case KEY_DOWN:
				selection = 0;
				goto outerbreak;
			case KEY_UP:
				selection = 1;
				goto outerbreak;
			case 32: /* space */
				selection = 4;    
			  
				goto outerbreak;
		}
	}	
outerbreak:

	//unpost_menu(jog_menu);
	//for(i = 0; i < n_choices; ++i)
	//	free_item(jog_items[i]);
	//free_menu(jog_menu);
	return (c);
}