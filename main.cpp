#include "hooke.h"


const char *mainchoices[] = {				//char *choices[] = {
                        "Lock / Free Motor 1",
                        "Lock / Free Motor 2",
                        "Enter Setup Menu",
                        "Enter Jog Menu",
						"Run Motors",
                        "Exit",
                  };
		  
		  
const char *setupchoices[] = {				//char *choices[] = {
                        "Lock / Free Motor 1",
                        "Lock / Free Motor 2",
                        "Set Supply Spool Diameter",
                        "Set Take-up Spool Diameter",
						"Set Transfer Speed",
						"Set Transfer Length",
						"Return to Main Menu",
                  };


int main()
{	
	/* Initialize curses */	
	initscr();
	start_color();
    cbreak();
    noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	
	serialib port;
	
	cout<<"\nInitializing communications - turn on motors now...\n"<<endl;
	
	int Ret=port.Open(DEVICE_PORT,38400);                      
	if (Ret!=1) 
	{                                                           	// If an error occured...
	  printf ("Error while opening port. Permission problem ?\n");  // ... display a message ...
	  exit(Ret);                                                    // ... quit the application
	}
    
	printf ("Serial port opened successfully !\n");
		
	Motor Source(&port, 1,(char)1);
	Motor Sink(&port,1,(char)2);
	Source.Lock();
	Sink.Lock();
	Sink.SetSpeed(takeupS);
	Source.SetSpeed(supplyS);
	main_menu(&Source, &Sink);
	
	
	endwin();
}

void main_menu(Motor* Source, Motor* Sink)
{
mainloop:
int menu_selection = -1;

	menu_selection = realmain(Source,Sink);
	switch (menu_selection)
	{
	  case 0:
	  if (Source->Locked)		  
		Source->Free();
	  else
		Source->Lock();
	    break;
	  case 1:
	if (Sink->Locked)
		Sink->Free();
	else
		Sink->Lock();
	    break;
	  case 2:
	    dosetup(Source, Sink);
	    break;
	  case 3:
	    dojog(Source, Sink);
	    break;
	  case 4:
	    break;
	  case 5:
	    break;
	  case 6:
		Source->Run(transferLength,supplyA,supplyS);
		Sink->Run(transferLength,takeupA,takeupS);
	    dojog(Source, Sink);
	    break;
	  case 7:
	    endwin();
	    exit(0);
	    break;
	    
	}
	goto mainloop;
  
}



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
	mvprintw(LINES -1,0,"Source Diameter %f mm, Takeup Diameter %f mm, Speed %d mm/s",supplyD,takeupD,takeupS/1000);



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

  menu_selection = setup_menu(Source, Sink);
  
  switch (menu_selection)
	{
	  case 0:
	  if (Source->Locked)		  
		Source->Free();
	  else
		Source->Lock();
	    break;
	  case 1:
	if (Sink->Locked)
		Sink->Free();
	else
		Sink->Lock();
	    break;
	  case 2:
	    clear();
		refresh();
		printw(". Supply spool diameter\n");
		printw("Enter Supply spool diameter in mm:");
		refresh();
		cin >> supplyD;
		printw("%f\n",supplyD);
		refresh();
		printw("Supply spool diameter is now: %f mm\n",supplyD);
		printw("Press Enter to return to main menu.\n");
		refresh();
		getch();
		break;
	    break;
	  case 3:
	    clear();
		refresh();
		printw(". Take-up spool diamter\n");
		printw("Enter Take-up spool diameter in mm:");
		refresh();
		cin >> takeupD;
		printw("%f\n",takeupD);
		refresh();
		printw("Take-up spool diameter is now: %f mm\n",takeupD);
		printw("Press Enter to return to main menu.\n");
		refresh(); 
		getch();
	    break;
	  case 4:
	    clear();
		refresh();
		printw(". Transfer speed\n");
		printw("WARNING : Correct spool diamters must be set first, else this speed WILL BE WRONG!\n");
		printw("Enter transfer speed in mm/s:");
		refresh();
		cin >> takeupS;
		printw("%d\n",takeupS);
		refresh();
		takeupC = 3.1415926535 * takeupD;
		temp = (500/takeupC)*takeupS;
		takeupS = temp;
		supplyS = takeupS*(takeupD/supplyD);
		Source->SetSpeed(supplyS);
		Sink->SetSpeed(takeupS);
		printw("Take-up spool speed is now %d \n",takeupS);
		printw("Supply spool speed is now %d \n",supplyS);
		printw("Press Enter to return to main menu.\n");
		refresh();
		getch();
	    break;
	  case 5:
	    clear();
		refresh();
		printw(". Wire Length\n");
		printw("WARNING : Correct spool diamters must be set first, else this speed WILL BE WRONG!\n");
		printw("Enter length of wire to transfer in mm:");
		refresh();
		cin >> transferLength;
		printw("%d\n",transferLength);
		refresh();
		transferLength *=5000;
		printw("Press Enter to return to main menu.\n");
		refresh();
		getch();
	    break;
	  case 6:
	    break;
	    
	}
  
}






void dorun(Motor *Source, Motor *Sink)
{
  cout<<"in run"<<endl;
}


int realmain(Motor *Source, Motor *Sink)
{
  
  ITEM **main_items;
  MENU *main_menu;
  int n_choices, i;
  ITEM *cur_item;
  int c, selection;
	
  
/* Initialize items */
        n_choices = ARRAY_SIZE(mainchoices);
        main_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
                main_items[i] = new_item(mainchoices[i],mainchoices[i]);
	main_items[n_choices] = (ITEM *)NULL;

	/* Create main menu */
	main_menu = new_menu((ITEM **)main_items);
	
	/* Set menu option not to show the description */
	menu_opts_off(main_menu, O_SHOWDESC);

	/* Set fore ground and back ground of the menu */
	set_menu_fore(main_menu, COLOR_PAIR(1) | A_REVERSE);
	set_menu_back(main_menu, COLOR_PAIR(2));
	set_menu_grey(main_menu, COLOR_PAIR(3));

	/* Post the menu */
	mvprintw(LINES - 5, 0, "Navigate with Arrow Keys, ENTER selects");
	if (Source->Locked){mvprintw(LINES - 3, 0, "Motor 1 is: Locked");}
	else
		mvprintw(LINES - 3, 0, "Motor 1 is: Free");
	
	if (Sink->Locked){mvprintw(LINES - 2, 0, "Motor 2 is: Locked");}
	else
		mvprintw(LINES - 2, 0, "Motor 2 is: Free");
	
	
	post_menu(main_menu);
	refresh();

	while((c = getch()) != KEY_F(4))
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(main_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(main_menu, REQ_UP_ITEM);
				break;
			case 10: /* Enter */
			
				selection = item_index(current_item(main_menu));    
			  
				goto outerbreak;
		}
	}	
outerbreak:

	unpost_menu(main_menu);
	for(i = 0; i < n_choices; ++i)
		free_item(main_items[i]);
	free_menu(main_menu);
	return (selection);
}


void dojog(Motor *Source, Motor *Sink)
{
 int menu_selection = -1;

 mainloop:
 clear();
 
  menu_selection = jog_menu(Source,Sink);
  switch (menu_selection)
  {
    case KEY_UP:
	supplyS=Source->GetSpeed()+30;
	Source->SetSpeed(supplyS);
      break;
    case KEY_DOWN:
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
	mvprintw(LINES -1,0,"Source speed %d, Takeup speed %d",supplyS,takeupS);
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
