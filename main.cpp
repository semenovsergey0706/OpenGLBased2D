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
	IRWindow myWindow(1024, 1024, "MyWindow");
	TDEStorage myTDE(360, myWindow);
	ITexStorage myTS;

	for (int i = 0; i < 360; ++i)
	{
		if (i%2 == 0) myTS.loadTexture("redRec.png", 1);
		else myTS.loadTexture("blueRec.png", 2);
	}


	for(int i = 0; i < 360; ++i) myTDE.CreateSpriteEntity();

	ISEntity* sprite;
	for (int i = 1; i < 360; ++i)
	{
		sprite = &myTDE.getSpriteEntityByStorageID(i);
		sprite->setPosition(64, 64);
		sprite->setOrigin(0, 0);
		//sprite->setRotation(i);
		sprite->attachTo(myTDE.getSpriteEntityByStorageID(i-1));
	}

	sprite = &myTDE.getSpriteEntityByStorageID(0);
	sprite->setPosition(0, 0);
	sprite->setOrigin(64, 64);

		
    std::shared_ptr<logl_shader> myShader = std::make_shared<logl_shader>("temp_shader.vs", "temp_shader.frag", true);

    myTDE.setShader(myShader);
	myTS.bindStorageTextures(myShader, "m_samplers");

	Timer t;

	//bool center_1 = false;
	//float scale = 1.0f;

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	float angle = 0;
	bool retach = false;
    while (!glfwWindowShouldClose(myWindow.get()))
    {
        glfwPollEvents();		
		glClear(GL_COLOR_BUFFER_BIT);
		
		angle = fmod(t.elapsed() * 60, 360);
		sprite = &myTDE.getSpriteEntityByStorageID(0);
		sprite->setRotation(angle);

		sprite = &myTDE.getSpriteEntityByStorageID(1);
		sprite->setRotation(-angle);


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