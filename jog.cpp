//jog.cpp
#include "hooke.h"

char *jogchoices[] = {				//char *choices[] = {
                        "Speed Up Motor 1",
                        "Slow Down Motor 1",
                        "Speed Up Motor 2",
                        "Slow Down Motor 2",
			"Emergency Stop",
			"Return to Main Menu",
                  };
		  
		  void dojog(Motor *Source, Motor *Sink)
{
 int menu_selection = -1;

 mainloop:
  menu_selection = jog_menu(Source,Sink);
  switch (menu_selection)
  {
    case 0:
	supplyS=Source->GetSpeed()+30;
	Source->SetSpeed(supplyS);
      break;
    case 1:
	supplyS=Source->GetSpeed()-30;
	Source->SetSpeed(supplyS);
      break;
    case 2:
	takeupS = Sink->GetSpeed()+30;
	Sink->SetSpeed(takeupS);
      break;
    case 3:
      takeupS = Sink->GetSpeed()-30;
	Sink->SetSpeed(takeupS);
      break;
    case 4:
	Source->EmergencyStop();
	Sink->EmergencyStop();
      break;
    case 5:
      //exit to main menu
      goto loopexit;
      
  }
  goto mainloop;

loopexit:
//do something harmless because we can't have a dangling goto jump where nothing happens.
 clear();
}

int jog_menu(Motor *Source, Motor *Sink)
{
  ITEM **jog_items;
  MENU *jog_menu;
  int n_choices, i;
  ITEM *cur_item;
  int c, selection;
  
  /* Initialize items */
        n_choices = ARRAY_SIZE(jogchoices);
        jog_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
                jog_items[i] = new_item(jogchoices[i],jogchoices[i]);
	jog_items[n_choices] = (ITEM *)NULL;
	//item_opts_off(main_items[3], O_SELECTABLE);
	//item_opts_off(main_items[6], O_SELECTABLE);

	/* Create main menu */
	jog_menu = new_menu((ITEM **)jog_items);
	
	/* Set menu option not to show the description */
	menu_opts_off(jog_menu, O_SHOWDESC);

	/* Set fore ground and back ground of the menu */
	set_menu_fore(jog_menu, COLOR_PAIR(1) | A_REVERSE);
	set_menu_back(jog_menu, COLOR_PAIR(2));
	set_menu_grey(jog_menu, COLOR_PAIR(3));

	/* Post the menu */
	mvprintw(LINES - 5, 0, "Navigate with Arrow Keys, ENTER selects");
	if (Source->Locked){mvprintw(LINES - 3, 0, "Motor 1 is: Locked");}
	else
		mvprintw(LINES - 3, 0, "Motor 1 is: Free");
	
	if (Sink->Locked){mvprintw(LINES - 2, 0, "Motor 2 is: Locked");}
	else
		mvprintw(LINES - 2, 0, "Motor 2 is: Free");
	mvprintw(LINES -1,0,"Source speed %d, Takeup speed %d",supplyS,takeupS);
	post_menu(jog_menu);
	refresh();

	while((c = getch()) != KEY_F(4))
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(jog_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(jog_menu, REQ_UP_ITEM);
				break;
			case 10: /* Enter */
			
				selection = item_index(current_item(jog_menu));    
			  
				//move(20, 0);
				//clrtoeol();
				//mvprintw(20, 0, "Item selected is : %s", 
				//		item_name(current_item(main_menu)));
				//pos_menu_cursor(main_menu);
				goto outerbreak;
		}
	}	
outerbreak:

	unpost_menu(jog_menu);
	for(i = 0; i < n_choices; ++i)
		free_item(jog_items[i]);
	free_menu(jog_menu);
	return (selection);
}