#include "Label.h"
#include "Game.h"


Label::Label(std::string text, std::string fontName, int fontSize, SDL_Color colour, glm::vec2 position, int fontStyle, bool isCentered)
{
	// initialize member variables
	m_fontName = fontName;
	m_fontColour = colour;
	m_text = text;
	m_isCentered = isCentered;
	m_fontSize = fontSize;
	m_fontStyle = fontStyle;
	
	m_fontPath = "../Assets/fonts/" + fontName + ".ttf";

	FontManager::Instance()->load(m_fontPath, fontName, fontSize, fontStyle);

	m_fontID = fontName + "-";
	m_fontID += fontSize + "-" + text;

	FontManager::Instance()->textToTexture(text, fontName, m_fontID, colour);
	glm::vec2 size = TheTextureManager::Instance()->getTextureSize(m_fontID);
	setWidth(size.x);
	setHeight(size.y);
	setPosition(position);
}

Label::~Label()
{
}

void Label::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;
	TheTextureManager::Instance()->drawText(m_fontID, xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, m_isCentered);
}

void Label::update()
{
}

void Label::clean()
{
}

void Label::setText(std::string newText)
{
	m_text = newText;
	m_fontID = m_fontName;
	m_fontID += "-";
	m_fontID += m_fontSize + "-";
	m_fontID += m_text;
	
	FontManager::Instance()->textToTexture(newText, m_fontName, m_fontID, m_fontColour);
	glm::vec2 size = TheTextureManager::Instance()->getTextureSize(m_fontID);
	setWidth(size.x);
	setHeight(size.y);
	setPosition(getPosition());
}

void Label::setColour(SDL_Color newColour)
{
	FontManager::Instance()->textToTexture(m_text, m_fontName, m_fontID, newColour);
}

void Label::setSize(int newSize)
{
	m_fontSize = newSize;
	
	FontManager::Instance()->load(m_fontPath, m_fontName, m_fontSize);

	m_fontID = m_fontName + "-";
	m_fontID += m_fontSize + "-" + m_text;

	FontManager::Instance()->textToTexture(m_text, m_fontName, m_fontID, m_fontColour);
	glm::vec2 size = TheTextureManager::Instance()->getTextureSize(m_fontID);
	setWidth(size.x);
	setHeight(size.y);
	setPosition(getPosition());
}

