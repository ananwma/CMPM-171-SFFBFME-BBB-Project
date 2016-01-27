#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <vector>
#include <map>
#include <list>

#include "input.h"
#define NOTE_ON 144


using namespace std;

list<int> notes;
vector<HMIDIIN> activeDevices;

[event_receiver(native)]
class EventRecieverTest 
{
public:
	void doMove(std::list<int> &notes) {
		// For now this just prints the list of notes pressed down
		for (auto i = notes.begin(); i != notes.end(); ++i)
			cout << *i << ' ';
		cout << endl;
	}
	void onKeysUp() {}
	void hookEvent(InputHandler* inputHandler) {
		__hook(&InputHandler::onNoteDown, inputHandler, &EventRecieverTest::doMove);
	}
	void unhookEvent(InputHandler* inputHandler) {
		__unhook(&InputHandler::onNoteDown, inputHandler, &EventRecieverTest::doMove);
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	// Get a console for debugging with cout
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	MIDIINCAPS device_capabilities;
	//cout << midiInGetNumDevs() << endl;
	//for (int dev_num = 0; dev_num < midiInGetNumDevs(); dev_num++) {
	//	midiInGetDevCaps(dev_num, &device_capabilities, sizeof device_capabilities);
	//	cout << device_capabilities.wMid;
	//}

	int numDevs = midiInGetNumDevs();
	cout << endl << "Num Devs: " << numDevs << endl;
	HMIDIIN midi_device_handle;
	HMIDIIN midi_device_handle2;

	//Testing functor
	//midiFunctor mf = midiFunctor();
	//int address = &mf;

	// Open devices and push handles on to vector
	vector<HMIDIIN> devices;
	/*for (int i = 0; i < midiInGetNumDevs(); i++) {
		HMIDIIN device;
		cout<<midiInOpen(&device, i, (DWORD_PTR)mf, 0, CALLBACK_FUNCTION);
		cout<<midiInStart(device);
		devices.push_back(device);
	}*/


	InputHandler  inputHandler = InputHandler();
	InputHandler  inputHandler2 = InputHandler();
	inputHandler.prepareDevice();
	inputHandler2.prepareDevice();
	MIDIINCAPS caps;
	//midiInGetDevCaps(i, &caps, sizeof(MIDIINCAPS));

	EventRecieverTest test;
	test.hookEvent(&inputHandler);

	// SFML Stuff
	sf::Texture texture;
	if (!texture.loadFromFile("sprites/bach_default.png"))
	{
		cerr << "Error loading texture" << endl;
		system("PAUSE");
		return EXIT_FAILURE;
	}
	texture.setSmooth(true);
	sf::Sprite sprite;
	sprite.setTexture(texture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		sprite.move(sf::Vector2f(0.1, 0));
		window.draw(sprite);
		window.display();
	}

	return 0;
}