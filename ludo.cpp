#include<winbgim.h>
#include<dos.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

int from[24][2] = {
52, 252,
212, 252,
252, 212,
252, 12,
292, 12,
332, 12,
332, 52,
332, 212,
372, 252,
572, 252,
572, 292,
572, 332,
532, 332,
372, 332,
332, 372,
332, 572,
292, 572,
252, 572,
252, 532,
252, 372,
212, 332,
12, 332,
12, 292,
12, 252
}, 

to[24][2] = {
212, 252,
252, 212,
252, 12,
292, 12,
332, 12,
332, 52,
332, 212,
372, 252,
572, 252,
572, 292,
572, 332,
532, 332,
372, 332,
332, 372,
332, 572,
292, 572,
252, 572,
252, 532,
252, 372,
212, 332,
12, 332,
12, 292,
12, 252,
52, 252
};

class chopad{
	public:
		void show(){
			rectangle(0,0,600, 600);
			for(int i = 0,j = 40;j <= 240; i = i + 40, j = j + 40){
				for(int k = 240, a = 1; a <= 3;a++, k = k+40){
					rectangle(k, i, k + 40, j);
				}
			}
		
			for(int i = 360,j = 400;j <= 600; i = i + 40, j = j + 40){
				for(int k = 240, a = 1; a <= 3;a++, k = k+40){
					rectangle(k, i, k + 40, j);
				}
			}
			for(int i = 240,j = 280;j <= 360; i = i + 40, j = j + 40){
				for(int k = 0, a = 1; a <= 6;a++, k = k+40){
					rectangle(k, i, k + 40, j);
				}
			}
			for(int i = 240,j = 280;j <= 360; i = i + 40, j = j + 40){
				for(int k = 360, a = 1; a <= 6;a++, k = k+40){
					rectangle(k, i, k + 40, j);
				}
			}
			settextstyle(0, HORIZ_DIR, 2);
			outtextxy(250, 300, "WINNER");
		}
		int roll_dice(){
			char dice[2], ch;
			int num;
			dice[1] = '\0';
			settextstyle(0, HORIZ_DIR, 2);
			outtextxy(950, 100, "Enter R to roll the dice\n");
			do{
				ch = (char)getch();
				itoa((rand()%6)+1, dice, 10);
				settextstyle(0, HORIZ_DIR, 10);
				outtextxy(1100,150,dice);
			}while((ch != 'r') && (ch != 'R'));
			num = atoi(dice);
			return num;
		}
};

class goti{
	public:
		static int occur;
		int location[4][2], startx, starty, current, viewx, viewy, color;
		char name;
		goti(){
			current = -1;
			switch(occur){
				case 0:
					startx = 52;
					starty = 252;
					viewx = startx;
					viewy = starty - 40;
					color = 4;
				break;
				case 1:
					startx = 332;
					starty = 52;
					viewx = startx + 40;
					viewy = starty;
					color = 2;
				break;
				case 2:
					startx = 532;
					starty = 332;
					viewx = startx;
					viewy = starty + 40;
					color = 14;
				break;	
				case 3:
					startx = 252;
					starty = 532;
					viewx = startx - 40;
					viewy = starty;
					color = 1;
				break;			
			}
			for(int i = 0;i < 4;i++){
				for(int j = 0;j < 2;j++)
					location[i][j] = 0;
			}
			occur++;
		}
		
		void move(int dice){
			int num;
			char ch[2];
			ch[0] = '2';
			ch[1] = '\0';
			settextstyle(0, HORIZ_DIR, 2);
			if(dice == 6){
				if(location[3][0] == 0)
					outtextxy(950, 250, "Enter 1:Want To Open Goti\n");
				if(location[0][0] != 0)
					outtextxy(950, 270, "Enter 2:Move the player\n");	
				do{
					outtextxy(950, 290, "Enter one of above options\n");	
					ch[0] = (char)getch();	
				}while(!(((ch[0] == '1') && (location[3][0] == 0)) || ((ch[0] == '2') && (location[0][0] != 0))));
					
				if((location[3][0] == 0) && (ch[0] == '1')){
					current++;
					location[current][0] = startx;
					location[current][1] = starty;
				}	
			}
			if((location[0][0] != 0) && (ch[0] == '2')){
				do{
					outtextxy(950, 310, "Choose the player\n");
					ch[0] = (char)getch();
					num = atoi(ch);
					current = num - 1;
				}while(location[current][0] == 0);
				steps(dice);
			}
		}
		
		void goti_pos(){
			settextstyle(0, HORIZ_DIR, 2);
			for(int i = 0;i < 4;i++){
				if(location[i][0] != 0){
					circle(location[i][0] + 7, location[i][1] + 10 , 15);
					setfillstyle(SOLID_FILL, color);
					floodfill(location[i][0], location[i][1], 0);
				}
				setfillstyle(SOLID_FILL, color);
				floodfill(viewx, viewy, 0);
			}
		}
		
		void steps(int steps){
			char remp[2];
			remp[1] = '\0';
			int i = 0;
			while(1){
				if(location[current][0] == from[i][0]){
					if(((location[current][1] >= from[i][1]) && (location[current][1] <= to[i][1])) || ((location[current][1] <= from[i][1]) && (location[current][1] >= to[i][1])))
							break;
				}
				else if(location[current][1] == from[i][1]){
					if(((location[current][0] >= from[i][0]) && (location[current][0] <= to[i][0])) || ((location[current][0] <= from[i][0]) && (location[current][0] >= to[i][0])))
							break;
				}
				i++;
			}
			while(steps-- > 0){
				if((location[current][0] == to[i][0]) && (location[current][1] == to[i][1]))
					i = (++i)%24;
				if(to[i][0] > location[current][0]){
					location[current][0] += 40;
				}
				else if(to[i][0] < location[current][0]){
					location[current][0] -= 40;
				}
				
				if(to[i][1] > location[current][1]){
					location[current][1] += 40;
				}
				else if(to[i][1] < location[current][1]){
					location[current][1] -= 40;
				}
			}
		}
}obj[4];
int goti::occur = 0;

int main(){
	int dice;
	char temp[2];
	chopad table;
	temp[1] = '\0';
	initwindow(getmaxx(), getmaxy());
	setbkcolor(15);
	setcolor(0);
	settextstyle(0, HORIZ_DIR, 2);
	for(int k = 0;;k = k%4){
		cleardevice();
		itoa(k+1, temp, 10);
		outtextxy(950, 10,"player");
		outtextxy(1050, 10, temp);
		table.show();
		for(int j = 0;j < 4;j++){
			obj[j].goti_pos();
		}
		dice = table.roll_dice();
		obj[k].move(dice);
		if(dice == 6)
			k--;
		k++;
	}
	return 0;
}
