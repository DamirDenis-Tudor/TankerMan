#pragma once
#include "SpriteComponent.h"

#define RED {128 , 0 , 0}

#define BLACK {0 ,0 ,0 }
#define WHITE {255, 255 , 255}

#define GREEN {0, 255 ,0 , 0 }
#define BLUE {0, 0 , 128 }
#define BROWN {101,56,24}
#define YELLOW {255 , 255 , 0}
#define GOLD {255,223,0}

//gaseste o solutie pt pozitii
#define TextScoreBoardHeight 42
#define YellowTeamScorePosition {1600 , 0}
#define GreenTeamScorePosition {1600 , 42}
#define BlueTeamScorePosition {1600 , 84}
#define BrownTeamScorePosition {1600, 126}

/*
	Descriere clasa:
		-> clasa responsabila pentru gestionare entitailor de tip text
*/

class TextComponent : public SpriteComponent
{
private:
	SDL_Color _textColor = {};
	static TTF_Font* _font;
	string _text;
public:

	TextComponent(){}
	TextComponent(SDL_Color color , int heigth , string text = " ", Vector2T<int> position = {0,0});
	~TextComponent();

	static void setFont(const char*);
	
	void setColor(SDL_Color color);
	Vector2T<int> getDimension();
	void setText(string text);
};

