#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>




class Rectangle : public sf::RectangleShape
{
   
public:
	Rectangle() : sf::RectangleShape(sf::Vector2f(100,100)), movement_speed(10,10){}

	sf::Vector2f& getSpeed(){return this->movement_speed;}
	sf::Vector2f& setSpeed(float x, float y){this->movement_speed.x = x; this->movement_speed.y = y;}

private:
	sf::Vector2f movement_speed;
};

bool boundsCheck(Rectangle&, sf::RenderWindow&, int);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600),"Window");
	Rectangle rectangle;
	sf::Vector2f rect_position;
	


	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	window.setMouseCursorVisible(true);

	rectangle.setPosition(400,300);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)

				window.close();

			//key press events
			if (event.type == sf::Event::KeyPressed)
			{
				
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					//check to make sure boundaries won't be exceeded
					if(boundsCheck(rectangle, window, sf::Keyboard::Key::Up))
					{

					//store the coodinates of the rectangle in a temporary place
					rect_position = rectangle.getPosition();
					//alter the coordinates in the temporary place
					rect_position.y -= rectangle.getSpeed().y;
					//set the rectangle's new position
					rectangle.setPosition(rect_position);

					}
					
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					
					if(boundsCheck(rectangle,window, sf::Keyboard::Down))
					{
					rect_position = rectangle.getPosition();
					rect_position.y += rectangle.getSpeed().y;
					rectangle.setPosition(rect_position);
					}
					
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					if(boundsCheck(rectangle,window, sf::Keyboard::Left))
					{
					rect_position = rectangle.getPosition();
					rect_position.x -= rectangle.getSpeed().x;
					rectangle.setPosition(rect_position);
					}
					
					
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					if(boundsCheck(rectangle,window, sf::Keyboard::Right))
					{
					rect_position = rectangle.getPosition();
					rect_position.x += rectangle.getSpeed().x;
					rectangle.setPosition(rect_position);
					}
					
				}
			}
		}

		window.clear();
		window.draw(rectangle);
		window.display();
	}
}

bool boundsCheck(Rectangle& rectangle, sf::RenderWindow& window, int key)
{   
	//if the square will move past the right screen bound
	if(((rectangle.getPosition().x + (rectangle.getSize().x + rectangle.getSpeed().x)) > window.getSize().x) && (key == sf::Keyboard::Right)   ) 
		return false;
	
	//if the square will move past the left screen bound
	else if(((rectangle.getPosition().x - rectangle.getSpeed().x) < 0) && (key == sf::Keyboard::Left))
		return false;
	
	//if the square will move past the top screen bound
	else if(((rectangle.getPosition().y - rectangle.getSpeed().y) < 0) && (key == sf::Keyboard::Up))
		return false;
	//if the square will move past the bottom screen bound
	else if(((rectangle.getPosition().y + (rectangle.getSize().y + rectangle.getSpeed().y)) > window.getSize().y) && (key == sf::Keyboard::Down)) 
		return false;
	//if it won't transcend the boundaries, it passes the check
	else return true;
	
	return true;
}

/*
*  11/22/13
* -made square
* -implemented escape, up, down, left, right
* -implemented boundaries
* remarks: getPosition() is relative to the shape's (0,0) coordinate
*/
