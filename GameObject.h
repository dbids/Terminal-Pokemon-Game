using namespace std;
#include "Point2D.h"
#include "Vector2D.h"

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

//Forward declaration:
class Model;

//Define all of the private and public members of the GameObject class
class GameObject
{
public:
	//Constructors/Destructors
	GameObject(char);
	GameObject(Point2D, int, char);
	virtual ~GameObject();

	//Public Member Functions
	Point2D GetLocation();
	int GetId();
	char GetState();
	char GetDisplayCode();
	virtual void ShowStatus();
	virtual bool Update() = 0;
	virtual bool ShouldBeVisible() = 0;
	void DrawSelf(char* ptr);
	virtual bool IsAlive();

	//Extra Credit Read/Write functions
	virtual void save(ofstream& file);
	virtual void restore(ifstream& file, Model& model);

protected:
	//Protected Member Variables
	Point2D location;
	int id_num;
	char display_code;
	char state;
};

#endif