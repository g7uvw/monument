#include "hooke.h"
// setup menu stuff
const char *setupchoices[] = {				
                        "Lock / Free Motor 1",
                        "Lock / Free Motor 2",
                        "Set Supply Spool Diameter",
                        "Set Take-up Spool Diameter",
						"Set Transfer Speed",
						"Set Transfer Length",
						"Return to Main Menu",
                  };
		  
		  int setup_menu(Motor* Source, Motor* Sink)
{
  ITEM **setup_items;
  MENU *setup_menu;
  int n_choices, i;
  ITEM *cur_item;
  int c, selection;
  
  /* Initialize items */
        n_choices = ARRAY_SIZE(setupchoices);
        setup_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
                setup_items[i] = new_item(setupchoices[i],setupchoices[i]);
	setup_items[n_choices] = (ITEM *)NULL;


	/* Create main menu */
	setup_menu = new_menu((ITEM **)setup_items);
	
	/* Set menu option not to show the description */
	menu_opts_off(setup_menu, O_SHOWDESC);

	/* Set fore ground and back ground of the menu */
	set_menu_fore(setup_menu, COLOR_PAIR(1) | A_REVERSE);
	set_menu_back(setup_menu, COLOR_PAIR(2));
	set_menu_grey(setup_menu, COLOR_PAIR(3));

	/* Post the menu */
	mvprintw(LINES - 5, 0, "Navigate with Arrow Keys, ENTER selects");
	if (Source->Locked){mvprintw(LINES - 3, 0, "Motor 1 is: Locked");}
	else
		mvprintw(LINES - 3, 0, "Motor 1 is: Free");
	
	if (Sink->Locked){mvprintw(LINES - 2, 0, "Motor 2 is: Locked");}
	else
		mvprintw(LINES - 2, 0, "Motor 2 is: Free");
	mvprintw(LINES -1,0,"Source Diameter %f mm, Takeup Diameter %f mm, Speed %f mm/s",GetsupplyD(),GettakeupD(),GettakeupS()/10.0);



	post_menu(setup_menu);
	refresh();

	while((c = getch()) != KEY_F(4))
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(setup_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(setup_menu, REQ_UP_ITEM);
				break;
			case 10: /* Enter */
			
				selection = item_index(current_item(setup_menu));    
				goto outerbreak;
		}
	}	
outerbreak:

	unpost_menu(setup_menu);
	for(i = 0; i < n_choices; ++i)
		free_item(setup_items[i]);
	free_menu(setup_menu);
	return (selection);
}

void dosetup(Motor *Source, Motor *Sink)
{
int menu_selection = -1;
double entry,temp;
setup_menu_entry:
clear();
refresh();
  menu_selection = setup_menu(Source, Sink);
  
  switch (menu_selection)
	{
	  case 0:
	  if (Source->Locked)		  
		Source->Free();
	  else
		Source->Lock();
	    goto setup_menu_entry;
	  case 1:
	if (Sink->Locked)
		Sink->Free();
	else
		Sink->Lock();
	    goto setup_menu_entry;
	  case 2:
	    clear();
		refresh();
		printw(". Supply spool diameter\n");
		printw("Enter Supply spool diameter in mm:");
		refresh();
		cin >>  entry;
		SetsupplyD(entry);
		printw("%f\n",GetsupplyD());
		refresh();
		printw("Supply spool diameter is now: %f mm\n",GetsupplyD());
		printw("Press Enter to return to main menu.\n");
		refresh();
		getch();
		goto setup_menu_entry;
	    
	  case 3:
	    clear();
		refresh();
		printw(". Take-up spool diamter\n");
		printw("Enter Take-up spool diameter in mm:");
		refresh();
		cin >> entry;
		SettakeupD(entry);
		printw("%f\n",GettakeupD());
		refresh();
		printw("Take-up spool diameter is now: %f mm\n",GettakeupD());
		printw("Press Enter to return to main menu.\n");
		refresh(); 
		getch();
	    goto setup_menu_entry;
	  case 4:
	    clear();
		refresh();
		printw(". Transfer speed\n");
		printw("WARNING : Correct spool diamters must be set first, else this speed WILL BE WRONG!\n");
		printw("Enter transfer speed in mm/s:");
		refresh();
		cin >> temp;
		entry = ((((temp/GettakeupD())*60.0)/60.0)*50000)/10;
		SettakeupS(entry);
		printw("%f\n",GettakeupS());
		refresh();
		//takeupC = 3.1415926535 * takeupD;
		//temp = (500/GettakeupC())*GettakeupS();
		//SettakeupS(temp);
		SetsupplyS(GettakeupS()*(GettakeupD()/GetsupplyD()));
		Source->SetSpeed(GetsupplyS());
		Sink->SetSpeed(GettakeupS());
		printw("Take-up spool speed is now %f \n",GettakeupS());
		printw("Supply spool speed is now %f \n",GetsupplyS());
		printw("Press Enter to return to main menu.\n");
		refresh();
		getch();
	    goto setup_menu_entry;
	 
	 case 5:
	    clear();
		refresh();
		printw(". Wire Length\n");
		printw("WARNING : Correct spool diamters must be set first, else this speed WILL BE WRONG!\n");
		printw("Enter length of wire to transfer in mm:");
		refresh();
		cin >> entry;
		SettransferLength(entry*500);
		printw("%f\n",GettransferLength()/500);
		refresh();
		printw("Press Enter to return to main menu.\n");
		refresh();
		getch();
	    goto setup_menu_entry;
	  
	 case 6:
	    break;
	    
	}
  
}
