#include "GameScenes.h"

Vector2f CameraView::PlanetCenter()
    {
        center.x = (firstPlanet.GetGlobalPosition().x + secondPlanet.GetGlobalPosition().x) / 2;
        center.y = (firstPlanet.GetGlobalPosition().y + secondPlanet.GetGlobalPosition().y) / 2;
        return center;
    }
void CameraView::SetPlanet(Planet fp, Planet sp)
    {
        firstPlanet = fp;
        secondPlanet = sp;
        PlanetCenter();
    }

void GameOver::Init()
    {
        music.openFromFile("GameOver.ogg");
        music.play();
        RegGameObjects(bg);
        bg.SetPosition(Vector2f(400, 300));
        engine->camera.SetTarget(bg.GetGlobalPosition());

        gameOver.SetFont("Pixel.otf");
        gameOver.SetSize(48);
        gameOver.SetText("Game Over!");
        gameOver.CenterText(800, 3);
        RegGameObjects(gameOver);

        esc.SetFont("Pixel.otf");
        esc.SetSize(18);
        esc.SetText("Press Esc to exit the game");
        esc.CenterText(800, 27);
        RegGameObjects(esc);
    }
void GameOver::Update()
    {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            music.stop();
            engine->window.close();
        }
    }

void GameScene::CreatePlanet(Vector2f pos)
    {
        Planet planet;
        planet.CreatePlanet(pos);
        planet.name = c++;
        planets.push_back(planet);
        it = planets.end();
        it--;
        RegGameObjects(planets.back());
        //std::cout << planets.back().name << '\n';
        if (planets.size() > 1)
        {
            view.SetPlanet(planets.back(), *(--it));
            cameraObj.MoveTo(view.center);
        }
        if (planets.size() > 3)
        {
            RemoveGameObject(planets.front());
            planets.pop_front();
        }
        srand(time(NULL));
        float x = rand() % 200 - 100;
        float y = rand() % 150 - 75;
        planets.back().SetPosition(Vector2f(planets.back().GetGlobalPosition().x + x, planets.back().GetGlobalPosition().y + y));
    }
void GameScene::Init()
    {
        music.openFromFile("Theme.ogg");
        music.play();
        RegGameObjects(bg);
        RegGameObjects(cameraObj);

        bg.SetTarget(cameraObj.GetGlobalPosition());
        CreatePlanet(generator.GetNext());
        CreatePlanet(generator.GetNext());
        rocket.SetPlanet(planets.front().GetGlobalPosition());
        rocket.SetPosition(Vector2f(planets.front().GetGlobalPosition().x + 10, planets.front().GetGlobalPosition().y + 100));
        RegGameObjects(ghost);
        RegGameObjects(rocket);

        name.SetFont("Pixel.otf");
        name.SetSize(18);
        name.SetText("Score");
        name.SetPosition(Vector2f(view.PlanetCenter().x - 390, view.PlanetCenter().y + 270));
        RegGameObjects(name);

        score.SetFont("Pixel.otf");
        score.SetSize(18);
        score.SetText(sc);
        score.SetPosition(Vector2f(view.PlanetCenter().x - 300, view.PlanetCenter().y + 270));
        RegGameObjects(score);
    }
void GameScene::Update()
    {
        if (!isSpace && Keyboard::isKeyPressed(Keyboard::Space))
        {
            rocket.Fly();
            isSpace = 1;
        }
        if (music.getStatus() == music.Stopped)
        {
            music.play();
        }
        /*if (!Keyboard::isKeyPressed(Keyboard::Space) && isSpace)
            isSpace = 0;*/
        if (rocket.IsMoving())
        {
            if (cameraObj.IsOutOfBounds(rocket.collider))
            {
                music.stop();
                engine->LoadScene(gameOver);
            }
            else
            {
                targetPlanet = planets.back();
                Vector2f planetPos = targetPlanet.GetPosition();
                FloatRect collPlanet = targetPlanet.collider;
                float d = sqrt(pow(planetPos.x - rocket.GetPosition().x, 2) + pow(planetPos.y - rocket.GetPosition().y, 2));
                if (d < collPlanet.width / 2 + 10)
                {
                    CreatePlanet(generator.GetNext());
                    rocket.SetPlanet(targetPlanet.GetGlobalPosition());
                    rocket.IncSpeed();
                    s += n;
                    sprintf_s(sc, "%d", s);
                    n++;
                    score.SetText(sc);
                    name.SetPosition(Vector2f(view.PlanetCenter().x - 390, view.PlanetCenter().y + 270));
                    score.SetPosition(Vector2f(view.PlanetCenter().x - 300, view.PlanetCenter().y + 270));
                    isSpace = 0;
                }
            }
        }
    }


void Menu::Init()
    {
        RegGameObjects(bg);
        bg.SetPosition(Vector2f(400, 300));
        music.openFromFile("Menu.ogg");
        music.play();
        name.SetFont("Pixel.otf");
        name.SetSize(48);
        name.SetText("Space Trip");
        name.CenterText(800, 3);
        RegGameObjects(name);

        author.SetFont("Pixel.otf");
        author.SetSize(12);
        author.SetText("by Nelson");
        author.CenterText(800, 16);
        RegGameObjects(author);

        start.SetFont("Pixel.otf");
        start.SetSize(18);
        start.SetText("Press Enter to start the game");
        start.CenterText(800, 27);
        RegGameObjects(start);
    }
void Menu::Update()
    {
        if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            music.stop();
            engine->LoadScene(gamescene);
        }
    }

Menu::Menu() { ; }

