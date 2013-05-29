#include "stdafx.h"
#include "MainMenu.h"
#include "iostream"
using namespace std;

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
	//Load menu image from file
	sf::Texture image;
	image.loadFromFile("images/mainmenu.png");
	sf::Sprite sprite(image);

	//Setup clickable regions


	//Play menu item coordinates
	MenuItem playButton;
	playButton.rect.top = 145;
	playButton.rect.width = 235;
	playButton.rect.left = 0;
	playButton.rect.width = 1023;
	playButton.action = Exit;
	playButton.name = "play";

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.left = 0;
	exitButton.rect.width = 1023;
	exitButton.rect.top = 383;
	exitButton.rect.height = 200;
	exitButton.action = Exit;
	exitButton.name = "exit";

	_menuItems.push_back(exitButton);
	_menuItems.push_back(playButton);

	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;
	
	for ( it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if (menuItemRect.top < y
			&& (menuItemRect.height + menuItemRect.top > y)
			&& menuItemRect.left < x
			&& (menuItemRect.left + menuItemRect.width > x))
		{
			cout << _menuItems.size()<<endl << it << endl;
			cout  << (*it).name << " " << x  << " " << y << endl;
			return (*it).action;
		}
	}
	return Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while(true)
	{
		while (window.pollEvent(menuEvent))
		{
			if(menuEvent.type == sf::Event::MouseButtonPressed)
			{
				cout << "click" << menuEvent.mouseButton.x << " " << menuEvent.mouseButton.y;
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}

