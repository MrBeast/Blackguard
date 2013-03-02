/*
 *   Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
 *
 *   This software is provided 'as-is', without any express or implied
 *   warranty.  In no event will the authors be held liable for any damages
 *   arising from the use of this software.
 *
 *   Permission is granted to anyone to use this software for any purpose,
 *   including commercial applications, and to alter it and redistribute it
 *   freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *      claim that you wrote the original software. If you use this software
 *      in a product, an acknowledgment in the product documentation would be
 *      appreciated but is not required.
 *   2. Altered source versions must be plainly marked as such, and must not be
 *      misrepresented as being the original software.
 *   3. This notice may not be removed or altered from any source distribution.
 */

#include "Game.h"
#include "config.h"

#include <iostream>

using namespace GRG;

namespace
{
  #include <sys/stat.h>
  
  bool FileExists(const std::string& path)
  {
    struct stat fileInfo;
    int failed;
    failed = stat(path.c_str(), &fileInfo);
    return !failed && !(fileInfo.st_mode & S_IFDIR);
  }
}

Game* Game::instance=NULL;

Game::Game()
{
  Game::instance = this;
  window = new sf::RenderWindow(sf::VideoMode(800, 600), "Generic Rogue Game");
  window->setVerticalSyncEnabled(true);
#ifdef GRG_PREFER_INSTALLED_VERSION
  mDataPath = GRG_INSTALL_PREFIX"/usr/share/grg";  
#else
  std::vector<std::string> paths{".", GRG_SOURCE_DIR"/Assets", GRG_INSTALL_PREFIX"/usr/share/grg"};
  for(const std::string& path : paths)
  {
    if(FileExists(path+"/AssetInfo.txt"))
    {
      dataPath = path;
      break;
    }
  }
#endif
  std::cout << "Using data from " << dataPath << std::endl;
  assets.initialize();
}

Game::~Game()
{
  delete window;
}

float Game::getDeltaTime() const
{
  return deltaTime;
}

int Game::run()
{
  while(true)
  {
    if(!window->isOpen()) return EXIT_SUCCESS;
    
    this->deltaTime = clock.restart().asSeconds();
    
    draw();
    processEvents();
    update();
  }
}

void Game::draw()
{
  window->clear();
  
  sf::Sprite helloWorld(assets.Textures.TitleTest);
  helloWorld.setOrigin( sf::Vector2f(assets.Textures.TitleTest.getSize()) / 2.f);
  helloWorld.setPosition(window->getView().getCenter());
  window->draw(helloWorld);
  
  window->display();
}

void Game::processEvents()
{
  sf::Event event;
  while(window->pollEvent(event))
  {
    if(event.type == sf::Event::Closed) window->close();
    
    if(event.type == sf::Event::KeyPressed)
    {
      if(event.key.code == sf::Keyboard::Escape)
      {
        window->close();
      }
    }
  }
}

void Game::update()
{
  // TODO
}

std::string Game::getAssetPath(const std::string& path)
{
  return dataPath+"/"+path;
}
