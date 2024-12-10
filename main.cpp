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

/*精灵类*/
class Sprite
{
public:
	Sprite() :Sprite(0, 0) {}
	Sprite(int x, int y) :m_x(x), m_y(y), m_color(RED) {}
	//绘制精灵
	virtual void draw()
	{
		//设置基础颜色
		setfillcolor(m_color); //图的填充颜色

		setlinecolor(BLUE); //画线颜色
		//绘制矩形
		fillroundrect(m_x, m_y, m_x + Size, m_y + Size, 5, 5);
	}
	//移动
	void moveBy(int dx, int dy)
	{
		m_x += dx;
		m_y += dy;
	}
	//碰撞检测
	bool collision(const Sprite& other)
	{
		return m_x == other.m_x && m_y == other.m_y;

	}
	//越界检查
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
	COLORREF m_color; //颜色
};

/*蛇类*/
class Snake :public Sprite
{
public:
	Snake() :Snake(0, 0) {}
	Snake(int x, int y) :Sprite(x, y), dir(VK_RIGHT)
	{
		//初始化三节蛇
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
	//蛇的身体移动
	void bodyMove()
	{
		//身体跟着头移动
		for (size_t i = nodes.size() - 1; i > 0; i--)
		{
			nodes[i] = nodes[i - 1];
		}
		//头的移动
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
	bool collision(const Sprite& other) //碰撞检测
	{
		return nodes[0].collision(other);
	}
	void incrment() //长度增加
	{
		nodes.push_back(Sprite(-Size, -Size));
		Time -= 1;
	}
private:
	vector<Sprite> nodes; //蛇的所有节点
public:
	int dir;  //蛇的方向
};

/*食物*/
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
	//改变食物坐标
	void changePos()
	{
		m_color = GREEN;
		//随机生成坐标
		m_x = rand() % (width / 10) * 10;  //保证食物坐标是10的整数倍
		m_y = rand() % (height / 10) * 10;
	}
};

/*游戏场景*/
class GameScene
{
public:
	GameScene(){}
	void run()
	{
		BeginBatchDraw();//双缓冲绘图
		cleardevice();
		//美化背景
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

		//移动蛇，改变蛇的坐标
		snake.bodyMove();
		//改变蛇的移动方向 获取键盘按键 _getch()

		//获取消息
		ExMessage msg = { 0 };
		while (peekmessage(&msg, EX_KEY))
		{
			onMsg(msg);
		}
		snakeEatFood();
	}
	//响应消息：鼠标消息 键盘消息
	void onMsg(const ExMessage& msg)
	{
		//如果有键盘消息(有没有按键按下)
		if (msg.message == WM_KEYDOWN)
		{
			//判断哪个按键 virtual key code 虚拟键码
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
	//判断能否吃到食物
	void snakeEatFood()
	{
		if (snake.collision(food))
		{
			//蛇的节数增加
			snake.incrment();
			//食物重新产生
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
	cout << "欢迎来到由ling开发的贪吃蛇小游戏,用上下左右键操控即可。" << endl;
	sleep(1000);
	cout << "即将开始游戏:" << endl;
	sleep(1000);
	cout << "请稍等,正在为您加载中..." << endl;
	sleep(1000);
	cout << "*****3*****" << endl;
	sleep(1000);
	cout << "*****2*****" << endl;
	sleep(1000);
	cout << "*****1*****" << endl;
	sleep(1000);
	cout << "加载成功,祝您游戏愉快!" << endl;
	sleep(1000);*/

	initgraph(width, height, EX_SHOWCONSOLE);
	setbkcolor(CYAN);

	//设置随机数种子
	srand((unsigned int)time(NULL));

	/*std::chrono::steady_clock::time_point start; //测量运行时间
	std::chrono::steady_clock::time_point end;
	std::chrono::nanoseconds cpu_time_used; 
	long long ns;
	double ms;*/

	GameScene scene;
	while (true)
	{
		//start = std::chrono::high_resolution_clock::now();
		/*——————————————————————*/
		scene.run();
		/*——————————————————————*/
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