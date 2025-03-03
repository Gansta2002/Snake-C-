#include <SFML /Graphics.hpp>
#include <time.h>

using namespace sf;

int N = 30, M = 20; //N - �����, M - ������
int ts = 25; //������ ������� ������

int dir = 2, num = 4; //���������� dir �������� �� �������, ���������� num �������� �� ����� ������
/*��� �������������� ������ ��� ������ ���������� dir
dir = 1 -> ����
dir = 2 -> �����
dir = 3 -> �����
dir = 0 -> ����*/

bool game = true; //���������� game �������� �� ������ ����

//��������� ������ �������� �� � �����
struct Snake {
    int x, y;
    //� ��������� ������� ���������� x, y
    //��� �������� �� ���������� ������
} s[600];

//s[] - ��� ������ ������ ������

//��������� ������
struct Fruct
{
    int x, y;
    //����� ���������� ������
} f;

//������� Tick �������� �� ���� ����
void Tick() {
    //����� ��������� ��������� ����������
    //������ �������� ���� ������
    for (int i = num; i > 0; i--) {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }

    //�������� ������
    if (dir == 0)
        s[0].y += 1; //����
    if (dir == 1)
        s[0].x -= 1; //�����
    if (dir == 2)
        s[0].x += 1; //�����
    if (dir == 3)
        s[0].y -= 1; //�����

        //����� ��������, ���� ������ ������ ����� ������ ������
        //�� ��� ����������� �� ����� ������
    if (s[0].x > N)
        s[0].x = 0;
    if (s[0].x < 0)
        s[0].x = N;
    if (s[0].y > M)
        s[0].y = 0;
    if (s[0].y < 0)
        s[0].y = M;

    //���� ������ ������� ������
    if ((s[0].x == f.x) && (s[0].y == f.y)) {
        num++; //������ �����

        f.x = rand() % N; //������ ��������� ���������� ������
        f.y = rand() % M;
    }

    //����� ���������
    for (int i = 1; i < num; i++) //���� for ��� ���� ������ ������
    //���� ������ ������������ �� ����� �����
        if ((s[0].x == s[i].x) && (s[0].y == s[i].y))
            game = false; //������ �������� ���������� game �� false
}

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(ts * N, ts * M), "Snake!");

    //��� ���������� ��������
    /*
    Texture t; <- ������� ���������� ��� ��������
                  t.loadFromFile("������������ ��������"); <- � ���������� ��������
��������� ��������
Sprite tiles(t); <- ����� ��������� ���������� ������� �
��������� ��������
*/

//������ ��������� titels
    Texture t;
    t.loadFromFile("C:/Users/�����/Desktop/Paint/tiles.png");
    Sprite tiles(t);

    //������ �������� ������
    Texture sn;
    sn.loadFromFile("C:/Users/�����/Desktop/Paint/snake.png");
    Sprite snake(sn);

    //������ �������� ������
    Texture ap;
    ap.loadFromFile("C:/Users/�����/Desktop/Paint/apple.png");
    Sprite apple(ap);

    //������ ������� gameover
    Texture go;
    go.loadFromFile("C:/Users/�����/Desktop/Paint/gameover.png");
    Sprite gameover(go);
    gameover.setPosition(0, 175);

    f.x = 10;
    f.y = 10;
    //��������� ���������� ������

    Clock clock; //���������� clock ����� ��� ������� �������
    float timer = 0, delay = 0.1;
    //timer � delay �������� �� �������� ������
    //timer ��������, ����� ����� ����� ������ ���������
    //delay - �� ��������

    while (window.isOpen())
    {
        //������� �����
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        //���������� ������� ����� ����������
        if (Keyboard::isKeyPressed(Keyboard::Left)) //���� ������� ����� ������
            dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) //���� ������� ������ ������
            dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) //���� ������� ����� ������
            dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down))  //���� ������� ���� ������
            dir = 0;

        //����� �������� �� ������ ����
        if (timer > delay && game) {
            timer = 0; //���������� �����
            Tick(); //�������� ������ ����
        }

        window.clear();

        //��� ���������� ����� ������������� ����
        //����� ���� for
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++) {
                tiles.setPosition(i * ts, j * ts); //�������
                window.draw(tiles); //������
            }

        //������ ������
        for (int i = 0; i < num; i++) {
            if (i != 0) //������ ���� ������
                snake.setTextureRect(IntRect(0, 0, ts, ts));
            else //������ ������ ������
                snake.setTextureRect(IntRect(dir * ts, ts, ts, ts));

            // �� ����� ��������� ������ ����������
            if (!game && i == 1)
                snake.setTextureRect(IntRect(dir * ts, ts * 2, ts, ts));

            snake.setPosition(s[i].x * ts, s[i].y * ts); //����� �������
        //��� ������ ������
            window.draw(snake);
        }

        apple.setPosition(f.x * ts, f.y * ts); //������� ������
        window.draw(apple); //������ ������

        //���� �� ���������, �� ������ �������� ������� gameover
        if (!game)
            window.draw(gameover);

        window.display();
    }

    return 0;
}