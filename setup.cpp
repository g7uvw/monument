#include "hooke.h"
// setup menu stuff
const char *setupchoices[] = {				
                        "Lock / Free Motor 1",
                        "Lock / Free Motor 2",
                        "Set Supply Spool Diameter",
                        "Set Take-up Spool Diameter",
			"Set Transfer Speed",
			"Set Transfer Length",
			"Set Accelerations",
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
	mvprintw(LINES - 6, 0, "Navigate with Arrow Keys, ENTER selects");
	if (Source->Locked){mvprintw(LINES - 3, 0, "Motor 1 is: Locked");}
	else
		mvprintw(LINES - 4, 0, "Motor 1 is: Free");
	
	if (Sink->Locked){mvprintw(LINES - 3, 0, "Motor 2 is: Locked");}
	else
		mvprintw(LINES - 3, 0, "Motor 2 is: Free");
	mvprintw(LINES -2,0,"Source Diameter %.3f mm, Takeup Diameter %.3f mm, Speed %.3f mm/s",GetsupplyD(),GettakeupD(),GettakeupSmms());
	if (GetDirection() <0)
		mvprintw(LINES -1,0,"Direction is Supply spool to Takeup spool\n");
	else
		mvprintw(LINES -1,0,"Direction is Takeup spool to Supply spool\n");

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
		printw("%.3f\n",GetsupplyD());
		refresh();
		printw("Supply spool diameter is now: %.3f mm\n",GetsupplyD());
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
		printw("%.3f\n",GettakeupD());
		refresh();
		printw("Take-up spool diameter is now: %.3f mm\n",GettakeupD());
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
		entry = (temp/GetsupplyC()) * (GetPPR()*GetSpeedUnit());
		SetsupplyS(entry);
		printw("%.3f\n",GetsupplySmms());
		refresh();
		SettakeupS(GetsupplyS()*(GetsupplyD()/GettakeupD()));
		Source->SetSpeed(GetsupplyS());
		Sink->SetSpeed(GettakeupS());
		printw("Take-up spool speed is now %.3f \n",GettakeupSmms());
		printw("Supply spool speed is now %.3f \n",GetsupplySmms());
		printw("Press Enter to return to main menu.\n");
		refresh();
		getch();
	    goto setup_menu_entry;
	 
	 case 5:
	    clear();
		refresh();
		printw(". Wire Length\n");
		printw("WARNING : Correct spool diamters must be set first, else this speed WILL BE WRONG!\n");
		printw("Negative length will change transfer direction\n");	
		printw("Enter length of wire to transfer in mm:");
		refresh();
		cin >> entry;
		if (entry < 0)
			SetDirection(1);	//yes, I know this looks wrong, but it isn't
		else
			SetDirection(-1);	//same for this, it really is -ve for a +direction the wave we have the hardware setup
		
		SettransferLength(abs(entry));
		printw("%.3f\n",GettransferLength());
		refresh();
		printw("Press Enter to return to main menu.\n");
		refresh();
		getch();
	    goto setup_menu_entry;
	  
	 case 6:
		clear();
		refresh();
		printw(". Set Accelerations\n");
		printw("WARNING : Correct spool diamters must be set first, else the acceleration ratios WILL BE WRONG!\n");
		printw("Current accelerations are, Supply:%d units and Takeup: %d units\n",GetsupplyA(),GettakeupA());
		printw("Enter new supply acceleration, takeup will be set and scaled automatically\n");
		refresh();
		cin >>entry;
		SetsupplyA(entry);
		SettakeupA(entry * GettakeupD()/GetsupplyD());	//scale to ratio of Ds - bigger one acclerates faster.
		printw("New accelerations are, Supply:%d units and Takeup: %d units\n", GetsupplyA(), GettakeupA());
		refresh();
		printw("Press Enter to return to main menu.\n");
		refresh();
		getch();
	    goto setup_menu_entry;

	
	case 7:
	    break;
	    
	}
  
}
