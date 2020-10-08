#include <iostream>
#include <string>
#include <cmath>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "External/stb_image.h"
#include "External/logl_shader.hpp"

#include "2Dlib/RenderWindow/RenderWindow.hpp"

#include <vector>
#include "2Dlib/InstancingFeatures/DrawableEntitysStorage/DEStorage.hpp"
#include "2Dlib/InstancingFeatures/TempDrawableEntitysStorage/TDEStorage.hpp"
#include "additionalFunctions/2DMMath/mat3glm.hpp"
#include "2Dlib/InstancingFeatures/ITextureStorage/ITexStorage.hpp"
#include <glm/gtx/string_cast.hpp>

#include <chrono>

class Timer
{
private:

	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

int main()
{
	SimpleTimer timer;
	IRWindow myWindow(1024, 1024, "MyWindow");
	TDEStorage myTDE(360, myWindow, timer);

	for (int i = 0; i < 2; ++i)
	{
		if (i%2 == 0) myTDE.loadTexture("redRec2.png", 1);
		else myTDE.loadTexture("blueRec.png", 2);
	}
	
	myTDE.loadTexture("testImg.png", 3);

	for (int i = 0; i < 360; ++i)
	{
		myTDE.CreateSpriteEntity();
		myTDE.getSpriteEntityByStorageID(i).setTextureByStorageID(i%2);
	}
		

	ISEntity* sprite;
	ISEntity* sprite2;
	for (int i = 1; i < 360; ++i)
	{
		sprite = &myTDE.getSpriteEntityByStorageID(i);
		sprite->setPosition(64, 64);
		sprite->setOrigin(0, 0);
		//sprite->setRotation(30 * i);
		sprite->attachTo(myTDE.getSpriteEntityByStorageID(0));
	}


	for (int i = 6; i < 360; i += 5)
	{
		sprite = &myTDE.getSpriteEntityByStorageID(i);
		myTDE.getSpriteEntityByStorageID(i - 1).attachTo(*sprite);
		myTDE.getSpriteEntityByStorageID(i - 2).attachTo(*sprite);
		myTDE.getSpriteEntityByStorageID(i - 3).attachTo(*sprite);
		myTDE.getSpriteEntityByStorageID(i - 4).attachTo(*sprite);
	}

	for (int i = 357; i < 360; i += 5)
	{
		myTDE.getSpriteEntityByStorageID(i).attachTo(myTDE.getSpriteEntityByStorageID(355));
	}

	sprite = &myTDE.getSpriteEntityByStorageID(0);
	sprite->setPosition(0, 0);
	sprite->setOrigin(64, 64);
	
    std::shared_ptr<logl_shader> myShader = std::make_shared<logl_shader>("temp_shader.vs", "temp_shader.frag", true);

    myTDE.setShader(myShader);
	myTDE.bindStorageTextures("m_samplers");


	Timer t;

	//bool center_1 = false;
	//float scale = 1.0f;

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	float angle = 0;
	bool retach = false;
	int conn = 1;
	bool decreas = true;

	myTDE.getSpriteEntityByStorageID(0).setTextureByStorageID(2);
	myTDE.getSpriteEntityByStorageID(0).setFrameNumber(5);
	myTDE.getSpriteEntityByStorageID(0).setColumnNumber(3);
	myTDE.getSpriteEntityByStorageID(0).setRowNumber(2);
	myTDE.getSpriteEntityByStorageID(0).setFPS(1);
	myTDE.getSpriteEntityByStorageID(0).play();

    while (!glfwWindowShouldClose(myWindow.get()))
    {
        glfwPollEvents();		
		glClear(GL_COLOR_BUFFER_BIT);
		
		angle = fmod(t.elapsed() * 60, 360);
		sprite = &myTDE.getSpriteEntityByStorageID(0);
		sprite->setRotation(angle);

		//sprite = &myTDE.getSpriteEntityByStorageID(1);
		//sprite->setRotation(-angle);



		if (!retach && t.elapsed() >= 1)
		{
			myTDE.getSpriteEntityByStorageID(3).attachTo(myTDE.getSpriteEntityByStorageID(0));
			retach = true;
		}
		else if (retach && t.elapsed() >= 2)
		{
			myTDE.getSpriteEntityByStorageID(1).attachTo(myTDE.getSpriteEntityByStorageID(3));
			myTDE.getSpriteEntityByStorageID(1).setOrder(3);
		}

		//if (t.elapsed() >= 2.5)
			for (int i = 1; i < 360; ++i)
			{
				sprite2 = &myTDE.getSpriteEntityByStorageID(i);
				sprite2->setOrder(rand()%100);
			}


			//myTDE.getSpriteEntityByStorageID(0).setColor(0.0, 1.0, 1.0, 1.0);


			//if (conn == 1 && t.elapsed() >= 2.5)
			//{
			//	conn = 0;
			//	t.reset();
			//}				
			//else conn = 1;
			//if (t.elapsed() >= 2.5)
			/*myTDE.getSpriteEntityByStorageID(0).setTextureByStorageID(1);*/

		/*for (int i = 1; i < 6; ++i)
		{
			sprite = &myTDE.getSpriteEntityByStorageID(i);
			sprite->setRotation(-angle);
		}*/

		////scale = t.elapsed() * 0.3;
		////if (scale > 3.0)
		////{
		////	scale = 1.0f;
		////	t.reset();
		////}
		//sprite->setScale(scale, scale);
        myTDE.drawStorageData();

        glfwSwapBuffers(myWindow.get());

    }
}