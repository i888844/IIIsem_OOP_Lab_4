#include <iostream>
#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "windows.h"
#include "wingdi.h"

using namespace std;

#define px 1200

HWND hWnd = GetConsoleWindow();
HDC hDC = GetDC(hWnd);
RECT Rect;
HPEN hPen;
HPEN hOldPen;
HBRUSH hBrush;
HBRUSH hOldBrush;

void clear_screen(int r, int g, int b)
{
	hPen = CreatePen(PS_SOLID, 10, RGB(r, g, b));
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hBrush = CreateSolidBrush(RGB(r, g, b));
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, Rect.left, Rect.top, Rect.right, Rect.bottom);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);
}

class figure
{
protected:
	int x;
	int y;
	int l;
	int R;
	int G;
	int B;
	int dx;
	int dy;
	int dl;
public:
	figure()
	{
		l = 40 + rand() % 80;
		x = rand() % (px - l);
		y = rand() % (px - l);
		R = rand() % 256;
		G = rand() % 256;
		B = rand() % 256;
		dx = 1 + rand() % 40;
		if (rand() % 2 == 0)
		{
			dx *= -1;
		}
		dy = 1 + rand() % 40;
		if (rand() % 2 == 0)
		{
			dy *= -1;
		}
		dl = 1 + rand() % 5;
		if (rand() % 2 == 0)
		{
			dl *= -1;
		}
	}
	figure(int _x, int _y, int _l, int _R, int _G, int _B, int _dx, int _dy, int _dl)
	{
		x = _x;
		y = _y;
		l = _l;
		R = _R;
		G = _G;
		B = _B;
		dx = _dx;
		dy = _dy;
		dl = _dl;
	}
	figure(const figure &src_object)
	{
		x = src_object.x;
		y = src_object.y;
		l = src_object.l;
		R = src_object.R;
		G = src_object.G;
		B = src_object.B;
		dx = src_object.dx;
		dy = src_object.dy;
		dl = src_object.dl;
	}
	~figure() { }
	int get_x() const { return x; }
	int get_y() const { return y; }
	int get_l() const { return l; }
	int get_R() const { return R; }
	int get_G() const { return G; }
	int get_B() const { return B; }
	int get_dx() const { return dx; }
	int get_dy() const { return dy; }
	int get_dl() const { return dl; }
	void set_x(int _settable_x) { x = _settable_x; }
	void set_y(int _settable_y) { y = _settable_y; }
	void set_dx(int _settable_dx) { dx = _settable_dx; }
	void set_dy(int _settable_dy) { dy = _settable_dy; }
	void virtual draw() = 0;
	void move()
	{
		if (dx > 0)
		{
			if ((x + l + dx) > px)
			{
				dx *= -1;
			}
		}
		else
		{
			if (dx < 0)
			{
				if ((x + dx) < 0)
				{
					dx *= -1;
				}
			}
		}
		if (dy > 0)
		{
			if ((y + l + dy) > px)
			{
				dy *= -1;
			}
		}
		else
		{
			if (dy < 0)
			{
				if ((y + dy) < 0)
				{
					dy *= -1;
				}
			}
		}
		x += dx;
		y += dy;
	}
	void scale()
	{
		if (l < 10 || l > 100)
		{
			dl *= -1;
		}
		l += dl;
	}
	void recolour()
	{
		R = rand() % 256;
		G = rand() % 256;
		B = rand() % 256;
	}
};

class triangle : public figure
{
public:
	triangle() { }
	triangle(int _x, int _y, int _l, int _R, int _G, int _B, int _dx, int _dy, int _dl)
	{
		x = _x;
		y = _y;
		l = _l;
		R = _R;
		G = _G;
		B = _B;
		dx = _dx;
		dy = _dy;
		dl = _dl;
	}
	triangle(const triangle& src_object)
	{
		x = src_object.x;
		y = src_object.y;
		l = src_object.l;
		R = src_object.R;
		G = src_object.G;
		B = src_object.B;
		dx = src_object.dx;
		dy = src_object.dy;
		dl = src_object.dl;
	}
	~triangle() { }
	void draw()
	{
		POINT points[3];
		points[0].x = x + l / 2;
		points[0].y = y;
		points[1].x = x + l;
		points[1].y = y + l;
		points[2].x = x;
		points[2].y = y + l;
		hPen = CreatePen(PS_SOLID, 5, RGB(R, G, B));
		hOldPen = (HPEN)SelectObject(hDC, hPen);
		hBrush = CreateSolidBrush(RGB(R, G, B));
		hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Polygon(hDC, points, 3);
		DeleteObject(hPen);
		DeleteObject(hBrush);
	}
};

class rectangle : public figure
{
public:
	rectangle() { }
	rectangle(int _x, int _y, int _l, int _R, int _G, int _B, int _dx, int _dy, int _dl)
	{
		x = _x;
		y = _y;
		l = _l;
		R = _R;
		G = _G;
		B = _B;
		dx = _dx;
		dy = _dy;
		dl = _dl;
	}
	rectangle(const rectangle& src_object)
	{
		x = src_object.x;
		y = src_object.y;
		l = src_object.l;
		R = src_object.R;
		G = src_object.G;
		B = src_object.B;
		dx = src_object.dx;
		dy = src_object.dy;
		dl = src_object.dl;
	}
	~rectangle() { }
	void draw()
	{
		POINT points[4];
		points[0].x = x;
		points[0].y = y;
		points[1].x = x + l;
		points[1].y = y;
		points[2].x = x + l;
		points[2].y = y + l;
		points[3].x = x;
		points[3].y = y + l;
		hPen = CreatePen(PS_SOLID, 5, RGB(R, G, B));
		hOldPen = (HPEN)SelectObject(hDC, hPen);
		hBrush = CreateSolidBrush(RGB(R, G, B));
		hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Polygon(hDC, points, 4);
		DeleteObject(hPen);
		DeleteObject(hBrush);
	}
};

bool colors_are_the_same(figure* first_figure, figure* second_figure)
{
	bool result = false;
	if (first_figure->get_R() == second_figure->get_R() && first_figure->get_G() == second_figure->get_G() && first_figure->get_B() == second_figure->get_B())
	{
		result = true;
	}
	return result;
}

void reverse_dx(figure** figures)
{
	figures[0]->set_dx(figures[0]->get_dx() * -1);
	figures[1]->set_dx(figures[1]->get_dx() * -1);
	figures[2]->set_dx(figures[2]->get_dx() * -1);
	figures[3]->set_dx(figures[3]->get_dx() * -1);
}

void reverse_dy(figure** figures)
{
	figures[0]->set_dy(figures[0]->get_dy() * -1);
	figures[1]->set_dy(figures[1]->get_dy() * -1);
	figures[2]->set_dy(figures[2]->get_dy() * -1);
	figures[3]->set_dy(figures[3]->get_dy() * -1);
}

void change_coordinates(figure** figures)
{
	figures[0]->set_x(figures[0]->get_x() + figures[0]->get_dx());
	figures[0]->set_y(figures[0]->get_y() + figures[0]->get_dy());
	figures[1]->set_x(figures[0]->get_x() + figures[0]->get_dx() + 110);
	figures[1]->set_y(figures[0]->get_y() + figures[0]->get_dy());
	figures[2]->set_x(figures[0]->get_x() + figures[0]->get_dx());
	figures[2]->set_y(figures[0]->get_y() + figures[0]->get_dy() + 110);
	figures[3]->set_x(figures[0]->get_x() + figures[0]->get_dx() + 110);
	figures[3]->set_y(figures[0]->get_y() + figures[0]->get_dy() + 110);
}

void check_sector_has_reached_the_border(figure** figures)
{
	for (int i = 0; i < 4; i++)
	{
		if (figures[i]->get_dx() > 0)
		{
			if ((figures[i]->get_x() + figures[i]->get_l() + figures[i]->get_dx()) > px)
			{
				reverse_dx(figures);
			}
		}
		else
		{
			if (figures[i]->get_dx() < 0)
			{
				if ((figures[i]->get_x() + figures[i]->get_dx()) < 0)
				{
					reverse_dx(figures);
				}
			}
		}
		if (figures[i]->get_dy() > 0)
		{
			if ((figures[i]->get_y() + figures[i]->get_l() + figures[i]->get_dy()) > px)
			{
				reverse_dy(figures);
			}
		}
		else
		{
			if (figures[i]->get_dy() < 0)
			{
				if ((figures[i]->get_y() + figures[i]->get_dy()) < 0)
				{
					reverse_dy(figures);
				}
			}
		}
	}
	change_coordinates(figures);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	MoveWindow(hWnd, 100, 100, px, px, TRUE);
	GetClientRect(hWnd, &Rect);
	Rect.right = px;
	Rect.bottom = px;
	int dx = 1 + rand() % 40;
	if (rand() % 2 == 0)
	{
		dx *= -1;
	}
	int dy = 1 + rand() % 40;
	if (rand() % 2 == 0)
	{
		dy *= -1;
	}
	int dl = 1 + rand() % 5;
	if (rand() % 2 == 0)
	{
		dl *= -1;
	}
	figure** figures = new figure * [4];
	figures[0] = new rectangle(0, 0, 100, 255, 0, 0, dx, dy, dl);
	figures[1] = new rectangle(110, 0, 100, 255, 0, 0, dx, dy, dl);
	figures[2] = new triangle(0, 110, 100, 255, 0, 0, dx, dy, 0);
	figures[3] = new triangle(110, 110, 100, 255, 0, 0, dx, dy, 0);
	int i = 0;
	int j = 0;
	while (!_kbhit())
	{
		clear_screen(255, 255, 255);
		figures[0]->draw();
		figures[1]->draw();
		figures[2]->draw();
		figures[3]->draw();
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (colors_are_the_same(figures[i], figures[j]) && i != j)
				{
					figures[i]->recolour();
					figures[j]->recolour();
				}
			}
		}
		check_sector_has_reached_the_border(figures);
		figures[0]->scale();
		figures[1]->scale();
		Sleep(50);
	}
    return 0;
}