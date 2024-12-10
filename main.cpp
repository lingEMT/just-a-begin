#include<iostream>
#include<easyx.h>
#include<vector>
#include<ctime>
#include<chrono>
using namespace std;

int Size = 10;
constexpr unsigned int width = 640, height = 480;
int Time = 85.0;

int a = 0, b = 0, c = 0;

/*������*/
class Sprite
{
public:
	Sprite() :Sprite(0, 0) {}
	Sprite(int x, int y) :m_x(x), m_y(y), m_color(RED) {}
	//���ƾ���
	virtual void draw()
	{
		//���û�����ɫ
		setfillcolor(m_color); //ͼ�������ɫ

		setlinecolor(BLUE); //������ɫ
		//���ƾ���
		fillroundrect(m_x, m_y, m_x + Size, m_y + Size, 5, 5);
	}
	//�ƶ�
	void moveBy(int dx, int dy)
	{
		m_x += dx;
		m_y += dy;
	}
	//��ײ���
	bool collision(const Sprite& other)
	{
		return m_x == other.m_x && m_y == other.m_y;

	}
	//Խ����
	void Check()
	{
		if (m_x == width)
		{
			m_x = 0;
		}
		else if (m_x == -Size)
		{
			m_x = width - Size;
		}
		if (m_y == height)
		{
			m_y = 0;
		}
		else if (m_y == -Size)
		{
			m_y = height - Size;
		}
	}
protected:
	int m_x;
	int m_y;
	COLORREF m_color; //��ɫ
};

/*����*/
class Snake :public Sprite
{
public:
	Snake() :Snake(0, 0) {}
	Snake(int x, int y) :Sprite(x, y), dir(VK_RIGHT)
	{
		//��ʼ��������
		nodes.push_back(Sprite(20, height / 2 - 20));
		nodes.push_back(Sprite(10, height / 2 - 20));
		nodes.push_back(Sprite(0, height / 2 - 20));
	}
	void draw()override
	{
		for (Sprite& x : nodes)
		{
			x.draw();
		}
	}
	//�ߵ������ƶ�
	void bodyMove()
	{
		//�������ͷ�ƶ�
		for (size_t i = nodes.size() - 1; i > 0; i--)
		{
			nodes[i] = nodes[i - 1];
		}
		//ͷ���ƶ�
		switch (dir)
		{
		case VK_UP:
			nodes[0].moveBy(0, -Size);
			break;
		case VK_DOWN:
			nodes[0].moveBy(0, Size);
			break;
		case VK_LEFT:
			nodes[0].moveBy(-Size, 0);
			break;
		case VK_RIGHT:
			nodes[0].moveBy(Size, 0);
			break;
		}
		nodes[0].Check();
	}
	bool collision(const Sprite& other) //��ײ���
	{
		return nodes[0].collision(other);
	}
	void incrment() //��������
	{
		nodes.push_back(Sprite(-Size, -Size));
		Time -= 1;
	}
private:
	vector<Sprite> nodes; //�ߵ����нڵ�
public:
	int dir;  //�ߵķ���
};

/*ʳ��*/
class Food :public Sprite
{
public:
	Food()
	{
		changePos();
	}
	void draw()override
	{
		setfillcolor(m_color);
		setlinecolor(BLUE);
		fillellipse(m_x, m_y, m_x + 10, m_y + 10);
	}
	//�ı�ʳ������
	void changePos()
	{
		m_color = GREEN;
		//�����������
		m_x = rand() % (width / 10) * 10;  //��֤ʳ��������10��������
		m_y = rand() % (height / 10) * 10;
	}
};

/*��Ϸ����*/
class GameScene
{
public:
	GameScene(){}
	void run()
	{
		BeginBatchDraw();//˫�����ͼ
		cleardevice();
		//��������
		static int x, y;
		for (int i = 1; i <= 100; i++)
		{
			x = rand() % (width + 1);
			y = rand() % (width + 1);
			putpixel(x, y, WHITE);
		}
		food.draw();
		snake.draw();
		EndBatchDraw();

		//�ƶ��ߣ��ı��ߵ�����
		snake.bodyMove();
		//�ı��ߵ��ƶ����� ��ȡ���̰��� _getch()

		//��ȡ��Ϣ
		ExMessage msg = { 0 };
		while (peekmessage(&msg, EX_KEY))
		{
			onMsg(msg);
		}
		snakeEatFood();
	}
	//��Ӧ��Ϣ�������Ϣ ������Ϣ
	void onMsg(const ExMessage& msg)
	{
		//����м�����Ϣ(��û�а�������)
		if (msg.message == WM_KEYDOWN)
		{
			//�ж��ĸ����� virtual key code �������
			switch (msg.vkcode)
			{
			case VK_UP:
				if(snake.dir!=VK_DOWN)
					snake.dir = msg.vkcode;
				break;
			case VK_DOWN:
				if (snake.dir != VK_UP)
					snake.dir = msg.vkcode;
				break;
			case VK_LEFT:
				if (snake.dir != VK_RIGHT)
					snake.dir = msg.vkcode;
				break;
			case VK_RIGHT:
				if (snake.dir != VK_LEFT)
					snake.dir = msg.vkcode;
				break;
			default:
				break;
			}
		}
	}
	//�ж��ܷ�Ե�ʳ��
	void snakeEatFood()
	{
		if (snake.collision(food))
		{
			//�ߵĽ�������
			snake.incrment();
			//ʳ�����²���
			food.changePos();
		}
	}
private:
	Snake snake;
	Food food;
};

int main()
{
	/*sleep(1000);
	cout << "��ӭ������ling������̰����С��Ϸ,���������Ҽ��ٿؼ��ɡ�" << endl;
	sleep(1000);
	cout << "������ʼ��Ϸ:" << endl;
	sleep(1000);
	cout << "���Ե�,����Ϊ��������..." << endl;
	sleep(1000);
	cout << "*****3*****" << endl;
	sleep(1000);
	cout << "*****2*****" << endl;
	sleep(1000);
	cout << "*****1*****" << endl;
	sleep(1000);
	cout << "���سɹ�,ף����Ϸ���!" << endl;
	sleep(1000);*/

	initgraph(width, height, EX_SHOWCONSOLE);
	setbkcolor(CYAN);

	//�������������
	srand((unsigned int)time(NULL));

	/*std::chrono::steady_clock::time_point start; //��������ʱ��
	std::chrono::steady_clock::time_point end;
	std::chrono::nanoseconds cpu_time_used; 
	long long ns;
	double ms;*/

	GameScene scene;
	while (true)
	{
		//start = std::chrono::high_resolution_clock::now();
		/*��������������������������������������������*/
		scene.run();
		/*��������������������������������������������*/
		//end = std::chrono::high_resolution_clock::now();
		//cpu_time_used = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
		//ns = cpu_time_used.count();
		//ms = static_cast<double>(ns) * 1e-6;
		//cout << "ms:" << ms << endl;

		Sleep(Time);
	}

	(void)getchar();
	return 0;
}