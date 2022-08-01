#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>

using namespace sf;

class setSound {
public:
    SoundBuffer s1, s2, s3, s4;
    Sound shooting, destroy, score, damage;

    setSound() {
        s1.loadFromFile("C:/Users/��/Desktop/Programming_Project/Lesson/Play/Play_Antiasteroid/Anti Asteroid/shooting.ogg");
        s2.loadFromFile("C:/Users/��/Desktop/Programming_Project/Lesson/Play/Play_Antiasteroid/Anti Asteroid/destroy.ogg");
        s3.loadFromFile("C:/Users/��/Desktop/Programming_Project/Lesson/Play/Play_Antiasteroid/Anti Asteroid/score.ogg");
        s4.loadFromFile("C:/Users/��/Desktop/Programming_Project/Lesson/Play/Play_Antiasteroid/Anti Asteroid/damage.ogg");

        shooting.setBuffer(s1);
        destroy.setBuffer(s2);
        score.setBuffer(s3);
        damage.setBuffer(s4);
    }
};

setSound sound;

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(1200, 790), "Game!");

    Texture f;
    f.loadFromFile("C:/Users/��/Desktop/Programming_Project/Lesson/Play/Play_Antiasteroid/Anti Asteroid/Painting/fon.png");
    Sprite fon[2];
    for (int i = 0; i < 2; i++) {
        fon[i].setTexture(f);
        fon[i].setPosition(0, 790 * i - 790);
    }
    fon[1].setTextureRect(IntRect(0, 790, 1200, -790));

    Texture p;
    p.loadFromFile("C:/Users/��/Desktop/Programming_Project/Lesson/Play/Play_Antiasteroid/Anti Asteroid/Painting/player.png");
    Sprite player(p);
    player.setTextureRect(IntRect(0, 0, 208, 145));
    player.setPosition(450, 600);
    float frame = 0;

    Texture pr;
    pr.loadFromFile("C:/Users/��/Desktop/Programming_Project/Lesson/Play/Play_Antiasteroid/Anti Asteroid/Painting/prod.png");
    Sprite prod(pr);
    prod.setPosition(200, 300);
    float pd = 0;
    bool play = false;

    Texture pu;
    pu.loadFromFile("C:/Users/��/Desktop/Programming_Project/Lesson/Play/Play_Antiasteroid/Anti Asteroid/Painting/pula.png");
    Sprite pula(pu);
    pula.setPosition(-50, 0);
    bool mp = false;

    Texture as;
    as.loadFromFile("C:/Users/��/Desktop/Programming_Project/Lesson/Play/Play_Antiasteroid/Anti Asteroid/Painting/asteroid.png");
    Sprite asteroid[7];
    int ay[7] = { 0 };
    for (int i = 0; i < 7; i++) {
        asteroid[i].setTexture(as);
        ay[i] = rand() % 5;
        asteroid[i].setPosition(175 * i, -150 - 100 * ay[i]);
    }

    Texture ns;
    ns.loadFromFile("C:/Users/��/Desktop/Programming_Project/Lesson/Play/Play_Antiasteroid/Anti Asteroid/Painting/nadscore.png");
    Sprite nadscore(ns);
    nadscore.setPosition(10, 5);

    Texture sc;
    sc.loadFromFile("C:/Users/��/Desktop/Programming_Project/Lesson/Play/Play_Antiasteroid/Anti Asteroid/Painting/score.png");
    Sprite score[3];
    int re[3] = { 0 };
    for (int i = 0; i < 3; i++) {
        score[i].setTexture(sc);
        score[i].setPosition(300 + 50 * i, 10);
        score[i].setTextureRect(IntRect(0, 0, 50, 79));
    }

    Texture nl;
    nl.loadFromFile("C:/Users/��/Desktop/Programming_Project/Lesson/Play/Play_Antiasteroid/Anti Asteroid/Painting/nadlife.png");
    Sprite nadlife(nl);
    nadlife.setPosition(770, 5);

    Sprite life(sc);
    life.setTextureRect(IntRect(150, 0, 50, 79));
    life.setPosition(1120, 5);
    int l = 3;
    bool die = false;

    Texture go;
    go.loadFromFile("C:/Users/��/Desktop/Programming_Project/Lesson/Play/Play_Antiasteroid/Anti Asteroid/Painting/gameover.png");
    Sprite gameover(go);
    gameover.setPosition(300, 200);

    Texture pa;
    pa.loadFromFile("C:/Users/��/Desktop/Programming_Project/Lesson/Play/Play_Antiasteroid/Anti Asteroid/Painting/pause.png");
    Sprite pause(pa);
    pause.setPosition(400, 200);
    bool pe = false;

    while (window.isOpen())
    {
        Vector2f pl = player.getPosition();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Space) {
                    if (!play && !die)
                        play = true;
                    else if (!play && die) {
                        play = true;
                        die = false;

                        player.setPosition(450, 600);
                        for (int i = 0; i < 7; i++) {
                            ay[i] = rand() % 5;
                            asteroid[i].setPosition(175 * i, -150 - 100 * ay[i]);
                        }

                        pula.setPosition(-50, 0);

                        for (int i = 0; i < 3; i++) {
                            re[i] = 0;
                            score[i].setTextureRect(IntRect(0, 0, 50, 79));
                        }
                        l = 3;
                    }
                    else if (play && !mp && !die && !pe) {
                        sound.shooting.play();

                        pula.setPosition(pl.x + 95, pl.y - 60);

                        mp = true;
                    }
                }
                else if (event.key.code == Keyboard::Escape && play && !die) {
                    if (!pe)
                        pe = true;
                    else
                        pe = false;
                }
        }

        if (play) {
            if (!pe) {
                if (Keyboard::isKeyPressed(Keyboard::Right))
                    if (pl.x < 990)
                        player.move(1.5, 0);
                if (Keyboard::isKeyPressed(Keyboard::Left))
                    if (pl.x > 0)
                        player.move(-1.5, 0);
                if (Keyboard::isKeyPressed(Keyboard::Up))
                    if (pl.y > 5)
                        player.move(0, -1.5);
                if (Keyboard::isKeyPressed(Keyboard::Down))
                    if (pl.y < 650)
                        player.move(0, 1.5);
            }

            Vector2f fn[2];
            for (int i = 0; i < 2; i++) {
                if (!pe)
                    fon[i].move(0, 0.1);

                fn[i] = fon[i].getPosition();
                if (fn[i].y > 780)
                    fon[i].setPosition(0, -780);
            }

            Vector2f pa = pula.getPosition();
            if (mp && !pe) {
                pula.move(0, -2);

                if (pa.y < -100)
                    mp = false;
            }

            Vector2f ad[7];
            for (int i = 0; i < 7; i++) {
                if (!pe)
                    asteroid[i].move(0, 0.5);

                ad[i] = asteroid[i].getPosition();
                if (ad[i].y > 850) {
                    ay[i] = rand() % 5;
                    asteroid[i].setPosition(175 * i, -150 - 100 * ay[i]);

                    re[2]++;
                }

                if (pula.getGlobalBounds().intersects(asteroid[i].getGlobalBounds())) {
                    sound.destroy.play();

                    ay[i] = rand() % 5;
                    asteroid[i].setPosition(175 * i, -150 - 100 * ay[i]);

                    pula.setPosition(-50, 0);

                    re[2] += 5;
                }

                if (player.getGlobalBounds().intersects(asteroid[i].getGlobalBounds())) {
                    sound.damage.play();

                    l--;

                    ay[i] = rand() % 5;
                    asteroid[i].setPosition(175 * i, -150 - 100 * ay[i]);
                }
            }

            life.setTextureRect(IntRect(50 * l, 0, 50, 79));

            if (l == 0) {
                play = false;
                die = true;
            }
        }

        if (re[2] > 9) {
            sound.score.play();

            re[2] -= 10;

            re[1]++;
            if (re[1] > 9) {
                re[1] -= 10;

                re[0]++;
                if (re[0] > 9)
                    re[0] -= 10;
                score[0].setTextureRect(IntRect(re[0] * 50, 0, 50, 79));
            }
            score[1].setTextureRect(IntRect(re[1] * 50, 0, 50, 79));
        }
        score[2].setTextureRect(IntRect(re[2] * 50, 0, 50, 79));

        frame += 0.01;
        if (frame < 1)
            player.setTextureRect(IntRect(0, 0, 208, 145));
        else if (frame > 1 && frame < 2)
            player.setTextureRect(IntRect(214, 0, 208, 145));
        else
            frame = 0;

        window.clear(Color::White);

        for (int i = 0; i < 2; i++)
            window.draw(fon[i]);

        window.draw(player);

        window.draw(pula);

        for (int i = 0; i < 7; i++)
            window.draw(asteroid[i]);

        if (!play) {
            pd += 0.005;
            if (pd > 0 && pd < 1)
                window.draw(prod);
            else if (pd > 2)
                pd = 0;
        }

        if (play || die) {
            window.draw(nadscore);
            window.draw(nadlife);
            window.draw(life);

            for (int i = 0; i < 3; i++)
                window.draw(score[i]);

            if (die)
                window.draw(gameover);

            if (pe)
                window.draw(pause);
        }

        window.display();
    }

    return 0;
}