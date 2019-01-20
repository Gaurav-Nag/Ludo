#include<winbgim.h>
#include<dos.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

//----------------------------------------lIST OF TURNING POINTS POSITIONS TO SHOW DIRECTIONS FOR THE GOTI------------------------------------------------------ 
int from[24][2] = {
60, 260,
220, 260,
260, 220,
260, 20,
300, 20,
340, 20,
340, 60,
340, 220,
380, 260,
580, 260,
580, 300,
580, 340,
540, 340,
380, 340,
340, 380,
340, 580,
300, 580,
260, 580,
260, 540,
260, 380,
220, 340,
20, 340,
20, 300,
20, 260
};
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//Index for starting points of goti
int starting[] = {0, 6, 12, 18};

//safe points co-ordinates
int safe[] = {100, 340, 260, 100, 500, 260, 340, 500};

//color codes
int color[] = {4, 2, 14, 1};

//class for looks and visuals of ludo
class chopad{
	public:
		void show(){
			rectangle(0,0,600, 600);
			rectangle(240,0,360, 600);
			rectangle(0,240,600,360);
			
			rectangle(280, 0, 320, 240);
			setfillstyle(SOLID_FILL, 2);
			floodfill(300, 50, 0);
			
			rectangle(280, 360, 320, 600);
			setfillstyle(SOLID_FILL, 1);
			floodfill(300, 400, 0);
			
			rectangle(0, 280, 240, 320);
			setfillstyle(SOLID_FILL, 4);
			floodfill(50, 300, 0);
			
			rectangle(360, 280, 600, 320);
			setfillstyle(SOLID_FILL, 14);
			floodfill(400, 300, 0);
			
			for(int i = 0;i <= 560;i = i+80){
				if(i >= 240 && i <= 360)
					continue;
				rectangle(i, 240, i + 40, 360);
			}
			
			for(int i = 0;i <= 560;i = i+80){
				if(i >= 240 && i <= 360)
					continue;
				rectangle(240, i, 360, i + 40);
			}
			
			for(int i = 0;i < 8;i = i+2){
				setfillstyle(1, 13);
				floodfill(safe[i], safe[i+1], 0);
			}
			
			for(int i = 0;i < 4;i++){
				setfillstyle(1, color[i]);
				floodfill(from[starting[i]][0], from[starting[i]][1], 0);
			}
			
			setfillstyle(1, color[0]);
			floodfill(from[starting[0]][0], from[starting[0]][1]-40, 0);
			rectangle(from[starting[0]][0]-20, 40, from[starting[0]][0]+140, 200);
			circle(80, 80, 25);circle(80, 160, 25);circle(160, 80, 25);circle(160, 160, 25);
			setfillstyle(1, 15);
			floodfill(from[starting[0]][0], from[starting[0]][1]-80, 0);
			
			setfillstyle(1, color[1]);			
			floodfill(from[starting[1]][0]+40, from[starting[1]][1]+ 40, 0);
			rectangle(from[starting[1]][0]+60, 40, from[starting[1]][0]+220, 200);
			circle(440, 80, 25);circle(520, 80, 25);circle(440, 160, 25);circle(520, 160, 25);
			setfillstyle(1, 15);
			floodfill(from[starting[1]][0]+80, from[starting[1]][1]+ 80, 0);
			
			setfillstyle(1, color[2]);
			floodfill(from[starting[2]][0], from[starting[2]][1] + 40, 0);
			rectangle(from[starting[1]][0] + 60, 400, from[starting[1]][0]+220, 560);
			circle(440, 440, 25);circle(440, 520, 25);circle(520, 440, 25);circle(520, 520, 25);
			setfillstyle(1, 15);
			floodfill(from[starting[2]][0], from[starting[2]][1] + 80, 0);
			
			setfillstyle(1, color[3]);
			floodfill(from[starting[3]][0] - 40, from[starting[3]][1], 0);
			rectangle(from[starting[0]][0]-20, 400, from[starting[0]][0]+140, 560);
			circle(80, 440, 25);circle(160, 440, 25);circle(80, 520, 25);circle(160, 520, 25);
			setfillstyle(1, 15);
			floodfill(from[starting[3]][0] - 80, from[starting[3]][1], 0);
			
			settextstyle(0, HORIZ_DIR, 2);
			outtextxy(255, 290, "WINNER");
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
		int location[4][2], turning[2], startx, starty, current, color;
		goti(){
			current = -1;
			switch(occur){
				case 0:
					startx = 60;
					starty = 260;
					color = 4;
					turning[0] = 20;
					turning[1] = 300;
				break;
				case 1:
					startx = 340;
					starty = 60;
					color = 2;
					turning[0] = 300;
					turning[1] = 20;
				break;
				case 2:
					startx = 540;
					starty = 340;
					color = 14;
					turning[0] = 580;
					turning[1] = 300;
				break;	
				case 3:
					startx = 260;
					starty = 540;
					color = 1;
					turning[0] = 300;
					turning[1] = 580;
				break;			
			}
			for(int i = 0;i < 4;i++){
				for(int j = 0;j < 2;j++)
					location[i][j] = 0;
			}
			occur++;
		}
		
		int move(int dice){
			int num,  status = 0;
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
					return 0;
				}
			}
			if((location[0][0] != 0) && (ch[0] == '2')){
				do{
					outtextxy(950, 310, "Choose the player\n");
					ch[0] = (char)getch();
					num = atoi(ch);
					current = num - 1;
				}while(location[current][0] == 0);
				status = steps(dice);
				return status;
			}
			return 0;
		}
		
		void goti_pos(){
			settextstyle(0, HORIZ_DIR, 2);
			for(int i = 0;i < 4;i++){
				if(location[i][0] != 0){
					circle(location[i][0], location[i][1], 15);
					setfillstyle(SOLID_FILL, color);
					floodfill(location[i][0], location[i][1], 0);
				}
			}
		}
		
		int steps(int steps){
			int i = 0, scolor, var = 0;
			while(1){
				if(location[current][0] == from[i][0]){
					if(((location[current][1] >= from[i][1]) && (location[current][1] <= from[i+1][1])) || ((location[current][1] <= from[i][1]) && (location[current][1] >= from[i+1][1])))
							break;
				}
				else if(location[current][1] == from[i][1]){
					if(((location[current][0] >= from[i][0]) && (location[current][0] <= from[i+1][0])) || ((location[current][0] <= from[i][0]) && (location[current][0] >= from[i+1][0])))
							break;
				}
				i++;
			}
			
			while(steps-- > 0){
				if((location[current][0] == from[(i+1)%24][0]) && (location[current][1] == from[(i+1)%24][1]))
					i = (++i)%24;
				if(from[(i+1)%24][0] > location[current][0]){
					location[current][0] += 40;
				}
				else if(from[(i+1)%24][0] < location[current][0]){
					location[current][0] -= 40;
				}
				
				if(from[(i+1)%24][1] > location[current][1]){
					location[current][1] += 40;
				}
				else if(from[(i+1)%24][1] < location[current][1]){
					location[current][1] -= 40;
				}
			}
			scolor = getpixel(location[current][0], location[current][1]);
			if((getpixel(location[current][0] - 18, location[current][1]) == 15) && (scolor != 15)){
				while(1){
					if(scolor == ::color[var])
						break;
					var++;
				}
				return var;
			}
			else 
				return 0;
		}
}obj[4];
int goti::occur = 0;

int main(){
	int dice, status = 0, l;
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
		status = obj[k].move(dice);
		if(status!=0){
			for(int j = 0;j < 4;j++){
				if((obj[k].location[obj[k].current][0] == obj[status].location[j][0]) && (obj[k].location[obj[k].current][1] == obj[status].location[j][1])){
					l= j;
					break;
				}
			}
			for(int j = 0;j < 4;j++){
				if(obj[status].location[j][0] == 0){
					obj[status].location[l][0] = obj[status].location[j-1][0];
					obj[status].location[l][1] = obj[status].location[j-1][1];
					obj[status].location[j-1][0] = 0;
					obj[status].location[j-1][1] = 0;
				}
			}
		}
		if(dice == 6 || status != 0)
			k--;
		k++;
	}
	return 0;
}
