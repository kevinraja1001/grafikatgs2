#include <stdlib.h>
#include <stdio.h>
#include "line.c"

int planeX;
int planeY;

void floodFill (Point P, Color *target, Color *replacement){
	if((target -> a == replacement -> a) && (target -> r == replacement -> r) && (target -> g == replacement -> g) && (target -> b == replacement -> b)){
		//return
	}
	else{
		location = (P -> x + vinfo.xoffset) * bytePerPixel + (P -> y + vinfo.yoffset) * finfo.line_length;
		if((*(fbp + location) == target -> b) && (*(fbp + location + 1) == replacement -> g) && (*(fbp + location + 2) == replacement -> r) && (*(fbp + location + 3) == replacement -> a)){
			//return
		}
		else{
			changeARGB(location, replacement);
			Point NorthP, SouthP, EastP, WestP;
			setPoint(&NorthP, P -> x, (P -> y - 1));
			setPoint(&SouthP, P -> x, (P -> y + 1));
			setPoint(&EastP, (P -> x + 1), P -> y);
			setPoint(&WestP, (P -> x - 1), P -> y);
			floodFill(NorthP, target, replacement);
			floodFill(SouthP, target, replacement);
			floodFill(EastP, target, replacement);
			floodFill(WestP, target, replacement);
			//return
		}
	}
}

void plot8pixel (Point P, int p, int q, int W, Color C) {
    printSquare(W, P.x+p, P.y+q, C);
    printSquare(W, P.x-p, P.y+q, C);
    printSquare(W, P.x+p, P.y-q, C);
    printSquare(W, P.x-p, P.y-q, C);

    printSquare(W, P.x+q, P.y+p, C);
    printSquare(W, P.x-q, P.y+p, C);
    printSquare(W, P.x+q, P.y-p, C);
    printSquare(W, P.x-q, P.y-p, C);
}

void plot4pixel (Point P, int p, int q, int W, Color C) {
    printSquare(W, P.x+p, P.y-q, C);
    printSquare(W, P.x-p, P.y-q, C);
    printSquare(W, P.x+q, P.y-p, C);
    printSquare(W, P.x-q, P.y-p, C);
}

void drawPolyline (int n, Point *P, Color C) {
	int i;
	for (i = 0;i < n-1;i++) {
		drawLine(P[i], P[i+1], C);
	}
}

void drawPolygon (int n, Point *P, Color C) {
	drawLine(P[n-1], P[0], C);
	drawPolyline(n, P, C);
	// fill unknown generated gap
	drawLine(P[n-1], P[0], C);
}

void drawCircle (int radius, Point P, int W, Color C) {
    int d, p, q;

    p = 0;
    q = radius;
    d = 3 - 2*radius;

    plot8pixel(P, p, q, W, C);

    while (p < q) {
        p++;
        if (d<0) {
            d = d + 4*p + 6;
        }
        else {
            q--;
            d = d + 4*(p-q) + 10;
        }

        plot8pixel(P, p, q, W, C);
    }
}


/*
radius	: jari-jari lingkaran
P	: titik asal lingkaran
*/
void drawCircleHalf (int radius, Point P, int W, color C) {
    int d, p, q;

    p = 0;
    q = radius;
    d = 3 - 2*radius;

    plot4pixel(P, p, q, W, C);

    while (p < q) {
        p++;
        if (d<0) {
            d = d + 4*p + 6;
        }
        else {
            q--;
            d = d + 4*(p-q) + 10;
        }

        plot4pixel(P, p, q, W, C);
    }
}

void buildPlaneToRight(int x, int y, int scale, Color c) {
	//making list of points
	Point PointList[7];

	//assign global variables with the assigned parameters
	planeX = x;
	planeY = y;
	
	Point p1, p2, p3, p4;
	Color white;
	setColor (&white, (char) 255, (char) 255, (char) 255);
	Color black;
	setColor (&white, (char) 0, (char) 0, (char) 0);

	PointList[0].x = planeX;
	PointList[0].y = planeY;
	
	PointList[1].x = planeX - (70 * scale);
	planeX -= (70 * scale);
	PointList[1].y = planeY - (45 * scale);
	planeY -= (45 * scale);
	
	PointList[2].x = planeX - (190 * scale);
	planeX -= (190 * scale);
	PointList[2].y = planeY;
	
	PointList[3].x = planeX - (60 * scale);
	planeX -= (60 * scale);
	PointList[3].y = planeY - (35 * scale);
	planeY -= (35 * scale);
	
	PointList[4].x = planeX - (20 * scale);
	planeX -= (20 * scale);
	PointList[4].y = planeY;
	
	PointList[5].x = planeX + (50 * scale);
	PointList[5].y = planeY + (80 * scale);
	planeY += (80 * scale);
	
	drawPolygon(6, &PointList, c);

	Point circle;
	circle.x = planeX + (260 * scale);
	circle.y = planeY + (3 * scale);
	drawCircle(12, circle, 2, c);

	planeX = x - (100 * scale);
	planeY = y - (25 * scale);

	PointList[0].x = planeX;
	PointList[0].y = planeY;

	PointList[1].x = planeX - (100 * scale);
	planeX -= (100 * scale);
	PointList[1].y = planeY;

	PointList[2].x = planeX - (100 * scale);
	planeX -= (100 * scale);
	PointList[2].y = planeY + (45 * scale);
	planeY += (45 * scale);

	PointList[3].x = planeX + (50 * scale);
	planeX += (50 * scale);
	PointList[3].y = planeY;

	drawPolygon(4, &PointList, c);

	planeX = x - (100 * scale);
	planeY = y - (45 * scale);

	PointList[0].x = planeX;
	PointList[0].y = planeY;

	PointList[1].x = planeX - (100 * scale);
	planeX -= (100 * scale);
	PointList[1].y = planeY;

	PointList[2].x = planeX - (100 * scale);
	planeX -= (100 * scale);
	PointList[2].y = planeY - (45 * scale);
	planeY -= (45 * scale);

	PointList[3].x = planeX + (50 * scale);
	planeX += (50 * scale);
	PointList[3].y = planeY;

	drawPolygon(4, &PointList, c);	
	
	//flood fill
	setPoint(&p1, x - 175, y - 55);
	setPoint(&p2, x - 175, y - 40);
	setPoint(&p3, x - 175, y - 10);
	setPoint(&p4, x - 225, y - 5);
	
	floodFill(p1, &black, &white);
	floodFill(p2, &black, c);
	floodFill(p3, &black, &white);
	floodFill(p4, &black, &white);
}

void buildPlaneToLeft(int x, int y, int scale, Color c){
	//making list of points
	Point PointList[7];

	//assign global variables with the assigned parameters
	planeX = x;
	planeY = y;
	
	Point p1, p2, p3, p4;
	Color white;
	setColor (&white, (char) 255, (char) 255, (char) 255);
	Color black;
	setColor (&white, (char) 0, (char) 0, (char) 0);

	PointList[0].x = planeX;
	PointList[0].y = planeY;
	
	PointList[1].x = planeX + (70 * scale);
	planeX += (70 * scale);
	PointList[1].y = planeY - (45 * scale);
	planeY -= (45 * scale);
	
	PointList[2].x = planeX + (190 * scale);
	planeX += (190 * scale);
	PointList[2].y = planeY;
	
	PointList[3].x = planeX + (60 * scale);
	planeX += (60 * scale);
	PointList[3].y = planeY - (35 * scale);
	planeY -= (35 * scale);
	
	PointList[4].x = planeX + (20 * scale);
	planeX += (20 * scale);
	PointList[4].y = planeY;
	
	PointList[5].x = planeX - (50 * scale);
	PointList[5].y = planeY + (80 * scale);
	planeY += (80 * scale);
	
	drawPolygon(6, &PointList, c);

	Point circle;
	circle.x = planeX - (260 * scale);
	circle.y = planeY + (3 * scale);
	drawCircle(12, circle, 2, c);

	planeX = x + (100 * scale);
	planeY = y - (25 * scale);

	PointList[0].x = planeX;
	PointList[0].y = planeY;

	PointList[1].x = planeX + (100 * scale);
	planeX += (100 * scale);
	PointList[1].y = planeY;

	PointList[2].x = planeX + (100 * scale);
	planeX += (100 * scale);
	PointList[2].y = planeY + (45 * scale);
	planeY += (45 * scale);

	PointList[3].x = planeX - (50 * scale);
	planeX -= (50 * scale);
	PointList[3].y = planeY;

	drawPolygon(4, &PointList, c);

	planeX = x + (100 * scale);
	planeY = y - (45 * scale);

	PointList[0].x = planeX;
	PointList[0].y = planeY;

	PointList[1].x = planeX + (100 *scale);
	planeX += (100 * scale);
	PointList[1].y = planeY;

	PointList[2].x = planeX + (100 * scale);
	planeX += (100 * scale);
	PointList[2].y = planeY - (45 * scale);
	planeY -= (45 * scale);

	PointList[3].x = planeX - (50 * scale);
	planeX -= (50 * scale);
	PointList[3].y = planeY;

	drawPolygon(4, &PointList, c);	
	
	//flood fill
	setPoint(&p1, x + 175, y - 55);
	setPoint(&p2, x + 175, y - 40);
	setPoint(&p3, x + 175, y - 10);
	setPoint(&p4, x + 225, y - 5);
	
	floodFill(p1, &black, &white);
	floodFill(p2, &black, c);
	floodFill(p3, &black, &white);
	floodFill(p4, &black, &white);
}
