#include "hooke.h"

 int nRetCode = 0;

 char tmp;
 double temp;

const char *mainchoices[] = {				
                        "Lock / Free Motor 1",
                        "Lock / Free Motor 2",
                        "Enter Setup Menu",
                        "Enter Jog Menu",
						"Run Motors",
                        "Exit",
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
	
	//quit if we can't open the serialport
	if (Ret!=1) 
	{                                                           	
	  printf ("Error while opening port. Permission problem ?\n");  
	  exit(Ret);                                                    
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
		Source->Run(GettransferLength(),GetsupplyA(),GetsupplyS());
		Sink->Run(GettransferLength(),GettakeupA(),GettakeupS());
	    dojog(Source, Sink);
	    break;
	  case 5:
	    endwin();
	    exit(0);
	    break;
	    
	}
	goto mainloop;
  
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



