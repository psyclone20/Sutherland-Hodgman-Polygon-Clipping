#include <stdio.h>
#include <graphics.h>

int points[80][2] = { { 0 } }, new[80][2] = { { 0 } };

int leftClip(int, int);
int topClip(int, int);
int rightClip(int, int);
int bottomClip(int, int);

int main() {
	int gd = DETECT, gm, xmin, ymin, xmax, ymax, n, i;
	printf(
			"Enter the co-ordinates of top left corner of the clipping window: ");
	scanf("%d %d", &xmin, &ymin);
	printf(
			"Enter the co-ordinates of bottom right corner of the clipping window: ");
	scanf("%d %d", &xmax, &ymax);

	printf("Enter the number of co-ordinates of the polygon: ");
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		printf("Enter the co-ordinates of vertex %d: ", (i + 1));
		scanf("%d %d", &points[i][0], &points[i][1]);
	}

	initgraph(&gd, &gm, NULL);
	rectangle(xmin, ymin, xmax, ymax);
	for (i = 0; i < n; i++)
		line(points[i][0], points[i][1], points[(i + 1) % n][0],
				points[(i + 1) % n][1]);

	int result = leftClip(n, xmin);
	result = topClip(result, ymin);
	result = rightClip(result, xmax);
	result = bottomClip(result, ymax);

	delay(3000);
	cleardevice();
	rectangle(xmin, ymin, xmax, ymax);
	for (i = 0; i < result; i++)
		line(points[i][0], points[i][1], points[(i + 1) % result][0],
				points[(i + 1) % result][1]);

	return 0;
}

int leftClip(int limit, int xmin) {
	int i, j = 0, x1, y1, x2, y2;
	float m;
	for (i = 0; i < limit; i++) {
		x1 = points[i][0];
		y1 = points[i][1];
		x2 = points[(i + 1) % limit][0];
		y2 = points[(i + 1) % limit][1];
		if (x2 - x1)
			m = (y2 - y1) * 1.0 / (x2 - x1);

		if (x1 < xmin && x2 < xmin)
			continue;
		if (x1 > xmin && x2 > xmin) {
			new[j][0] = x2;
			new[j++][1] = y2;
			continue;
		}
		if (x1 > xmin && x2 < xmin) {
			new[j][0] = xmin;
			new[j++][1] = y1 + m * (xmin - x1);
			continue;
		}
		if (x1 < xmin && x2 > xmin) {
			new[j][0] = xmin;
			new[j++][1] = y1 + m * (xmin - x1);
			new[j][0] = x2;
			new[j++][1] = y2;
		}
	}

	for (i = 0; i < j; i++) {
		points[i][0] = new[i][0];
		points[i][1] = new[i][1];
		new[i][0] = new[i][1] = 0;
	}

	if (j < limit)
		for (; i < limit; i++)
			points[i][0] = points[i][1] = 0;

	return j;
}

int topClip(int limit, int ymin) {
	int i, j = 0, x1, y1, x2, y2;
	float m;
	for (i = 0; i < limit; i++) {
		x1 = points[i][0];
		y1 = points[i][1];
		x2 = points[(i + 1) % limit][0];
		y2 = points[(i + 1) % limit][1];
		if (x2 - x1)
			m = (y2 - y1) * 1.0 / (x2 - x1);

		if (y1 < ymin && y2 < ymin)
			continue;
		if (y1 > ymin && y2 > ymin) {
			new[j][0] = x2;
			new[j++][1] = y2;
			continue;
		}
		if (y1 > ymin && y2 < ymin) {
			new[j][0] = x1 + (ymin - y1) / m;
			new[j++][1] = ymin;
			continue;
		}
		if (y1 < ymin && y2 > ymin) {
			new[j][0] = x1 + (ymin - y1) / m;
			new[j++][1] = ymin;
			new[j][0] = x2;
			new[j++][1] = y2;
		}
	}

	for (i = 0; i < j; i++) {
		points[i][0] = new[i][0];
		points[i][1] = new[i][1];
		new[i][0] = new[i][1] = 0;
	}

	if (j < limit)
		for (; i < limit; i++)
			points[i][0] = points[i][1] = 0;

	return j;
}

int rightClip(int limit, int xmax) {
	int i, j = 0, x1, y1, x2, y2;
	float m;
	for (i = 0; i < limit; i++) {
		x1 = points[i][0];
		y1 = points[i][1];
		x2 = points[(i + 1) % limit][0];
		y2 = points[(i + 1) % limit][1];
		if (x2 - x1)
			m = (y2 - y1) * 1.0 / (x2 - x1);

		if (x1 > xmax && x2 > xmax)
			continue;
		if (x1 < xmax && x2 < xmax) {
			new[j][0] = x2;
			new[j++][1] = y2;
			continue;
		}
		if (x1 < xmax && x2 > xmax) {
			new[j][0] = xmax;
			new[j++][1] = y1 + m * (xmax - x1);
			continue;
		}
		if (x1 > xmax && x2 < xmax) {
			new[j][0] = xmax;
			new[j++][1] = y1 + m * (xmax - x1);
			new[j][0] = x2;
			new[j++][1] = y2;
		}
	}

	for (i = 0; i < j; i++) {
		points[i][0] = new[i][0];
		points[i][1] = new[i][1];
		new[i][0] = new[i][1] = 0;
	}

	if (j < limit)
		for (; i < limit; i++)
			points[i][0] = points[i][1] = 0;

	return j;
}

int bottomClip(int limit, int ymax) {
	int i, j = 0, x1, y1, x2, y2;
	float m;
	for (i = 0; i < limit; i++) {
		x1 = points[i][0];
		y1 = points[i][1];
		x2 = points[(i + 1) % limit][0];
		y2 = points[(i + 1) % limit][1];
		if (x2 - x1)
			m = (y2 - y1) * 1.0 / (x2 - x1);

		if (y1 > ymax && y2 > ymax)
			continue;
		if (y1 < ymax && y2 < ymax) {
			new[j][0] = x2;
			new[j++][1] = y2;
			continue;
		}
		if (y1 < ymax && y2 > ymax) {
			new[j][0] = x1 + (ymax - y1) / m;
			new[j++][1] = ymax;
			continue;
		}
		if (y1 > ymax && y2 < ymax) {
			new[j][0] = x1 + (ymax - y1) / m;
			new[j++][1] = ymax;
			new[j][0] = x2;
			new[j++][1] = y2;
		}
	}

	for (i = 0; i < j; i++) {
		points[i][0] = new[i][0];
		points[i][1] = new[i][1];
		new[i][0] = new[i][1] = 0;
	}

	if (j < limit)
		for (; i < limit; i++)
			points[i][0] = points[i][1] = 0;

	return j;
}
