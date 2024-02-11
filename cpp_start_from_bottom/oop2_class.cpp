#include <iostream>

/* ������ animal�� Ŭ������ �����ϰ� �ٲ㺸�� */
class Animal
{
public:
	void set_animal(int food, int health)
	{
		_food = food;
		_health = health;
	}
	void play()
	{
		_health += 10;
		_food += 20;
	}
	void show_stat()
	{
		std::cout << "health : " << _health << std::endl
			<< "food : " << _food << std::endl
			<< std::endl;
	}
	

private:
	int _health;
	int _food;
};

int main()
{
	Animal animal;

	// animal._health = 100;	// C2248 'Animal::_health': private���('Animal' Ŭ�������� ����)�� �׼��� �� �� �����ϴ�.
	animal.set_animal(100, 50);
	animal.show_stat();

	animal.play();
	animal.show_stat();

}