//引入所有需要使用的头文件
#include "Dino.h"
#include "font.h"
#include "oled.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


//所有动画的字模表示
//恐龙死亡动画
const uint8_t dino_crashedData[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xf1, 0xf5, 0xf1, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7e, 0x7f, 0xfc, 0xf8, 0xe0, 0xe0, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x04, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x81, 0x83, 0x87, 0xff, 0xdf, 0x87, 0x87, 0x87, 0xff, 0xc3, 0xc3, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
};
const Image dino_crashedImg = {21, 23, dino_crashedData};
//恐龙抬前腿动画
const uint8_t dino_front_legData[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xbf, 0xbf, 0xbf, 0x3f, 0x3e, 0x3f, 0xfc, 0xf8, 0xf0, 0xf0, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x04, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x81, 0x83, 0x87, 0xff, 0xdf, 0x8f, 0x87, 0x87, 0x8f, 0x8b, 0x8b, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
};
const Image dino_front_legImg = {21, 23, dino_front_legData};
//恐龙抬后腿动画
const uint8_t dino_back_legData[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xbf, 0xbf, 0xbf, 0x3f, 0x3e, 0x3f, 0xfc, 0xf8, 0xf0, 0xf0, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x04, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x81, 0x83, 0x87, 0x8f, 0x9f, 0x97, 0x87, 0x8f, 0xff, 0xc3, 0xc3, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
};
const Image dino_back_legImg = {21, 23, dino_back_legData};
//恐龙跳跃动画
const uint8_t dino_jumpsData[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xbf, 0xbf, 0xbf, 0x3f, 0x3e, 0x3f, 0xfc, 0xf8, 0xf0, 0xf0, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x04, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x81, 0x83, 0x87, 0xff, 0xdf, 0x8f, 0x87, 0x8f, 0xff, 0xc3, 0xc3, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
};
const Image dino_jumpsImg = {21, 23, dino_jumpsData};
//小型树动画
const uint8_t tree_smallData[] = {
    0xf8, 0x00, 0xff, 0xff, 0xc0, 0x7c, 0xc1, 0xc1, 0xff, 0xff, 0xc0, 0xc0,
};
const Image tree_smallImg = {6, 14, tree_smallData};
//大型树动画
const uint8_t tree_bigData[] = {
    0x80, 0xc0, 0x80, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0xe0, 0xe0, 0xe0, 0x3f, 0x7f, 0x7f, 0x60, 0xff, 0xff, 0xff, 0xff, 0x60, 0x7f, 0x3f, 0x1f, 0x80, 0x80, 0x80, 0x80, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0x80,
};
const Image tree_bigImg = {12, 23, tree_bigData};


//所有初始值
#define DINO_INIT_X 10      //恐龙出生地x坐标
#define DINO_INIT_Y 62 - 23 //恐龙出生地y坐标,其中23为恐龙高度

#define BASE_LINE_X 0		//地面基坐标
#define BASE_LINE_Y 63
#define BASE_LINE_X1 127

#define JUMP_PIXEL 32


//跳跃高度变化使用数组实现，每一帧一个高度
const uint8_t time_distance[38] = {0, 4, 7, 11, 14, 17, 20, 23, 25, 28, 30, 31, 33, 34, 35, 36, 37, 37, 38, 38, 37, 37, 36, 35, 34, 33, 31, 30, 28, 25, 23, 20, 17, 14, 11, 7, 4, 0};


//最高纪录分数，一直存储，重新开机重置
int highest_score = 0;


//主程序进入循环之前调用一次，显示游戏主界面
void introMessage()
{
	OLED_NewFrame();
	OLED_PrintString((128 - 80) / 2, 8, "小恐龙游戏", &font16x16, OLED_COLOR_NORMAL);
	OLED_DrawImage(DINO_INIT_X, DINO_INIT_Y, &dino_jumpsImg, OLED_COLOR_NORMAL);
	OLED_PrintString((128 - 32) / 2, 43, "开始", &font16x16, OLED_COLOR_NORMAL);
	OLED_ShowFrame();
}


//按下按键开启游戏之后显示进场动画
void showLine()
{
	//
	int line_end = 1;
	OLED_NewFrame();
	OLED_DrawImage(DINO_INIT_X, DINO_INIT_Y, &dino_jumpsImg, OLED_COLOR_NORMAL);
	//进入循环，不断增加地面线的end坐标，直到超出oled屏幕
	//在绘画过程中，地面线会互相覆盖，所以不需要多次使用OLED_NewFrame()来清除显存
	for(;;)
	{
		OLED_DrawLine(BASE_LINE_X, BASE_LINE_Y, line_end, BASE_LINE_Y, OLED_COLOR_NORMAL);
		OLED_ShowFrame();
		line_end = line_end+4;
		if (line_end > BASE_LINE_X1) break;
	}
}


//显示不同状态的小恐龙，不同状态的小恐龙y轴不相同，因此需要使用y参数和type来确定参数
void moveDino(int16_t y,int type)
{
	if(type == 0)
	{
		OLED_DrawImage(DINO_INIT_X, y, &dino_front_legImg, OLED_COLOR_NORMAL);
	}
	else if(type == 1)
	{
		OLED_DrawImage(DINO_INIT_X, y, &dino_back_legImg, OLED_COLOR_NORMAL);
	}
	else if (type == -1)
	{
		OLED_DrawImage(DINO_INIT_X, y, &dino_jumpsImg, OLED_COLOR_NORMAL);
	}
	else if (type == -2)
	{
		OLED_DrawImage(DINO_INIT_X, y, &dino_crashedImg, OLED_COLOR_NORMAL);
	}
}


//提供参数x和树木字模显示障碍物
void moveTree(int16_t x,Image *type)
{
	if(x > 127 -type->w)
		return;
	OLED_DrawImage(x, BASE_LINE_Y - type->h, type, OLED_COLOR_NORMAL);
}


//显示分数，根据type来确定是否要显示出“最高分”
void displayScore(int score,int8_t type)
{
	static char tmp[15];//确保tmp不会因为跳出函数消失

	if(type == 0)
	{
		//当传入type为0时表示没有超过历史记录,在固定位置显示分数
		sprintf(tmp, "%d", score);
		OLED_PrintString(72, 3, "得分：", &font12x12, OLED_COLOR_NORMAL);
		OLED_PrintString(72 + 30, 3, tmp, &font12x12, OLED_COLOR_NORMAL);
	}
	else
	{
		sprintf(tmp, "%d", highest_score);
		OLED_PrintString(72 - 12, 22, "最高分：", &font12x12, OLED_COLOR_NORMAL);
		OLED_PrintString(72 + 30, 22, tmp, &font12x12, OLED_COLOR_NORMAL);
	}
}


//游戏主程序
void play()
{
	int16_t tree_interval = 252;
	int16_t tree1_interval = 381;
	int16_t tree_x = tree_interval + 100;
	int16_t tree1_x = tree1_interval + 200;

	Image *tree = (HAL_GetTick() % 8) ? (Image *)&tree_smallImg : (Image *)&tree_bigImg;
	Image *tree1 = (HAL_GetTick() % 5) ? (Image *)&tree_smallImg : (Image *)&tree_bigImg;
	//随机tree是大树还是小树

	int16_t dino_right = DINO_INIT_X + dino_front_legImg.w;
	int16_t dino_y = DINO_INIT_Y;
	//用于碰撞检测

	int jump = 0;

	//分数计算过程,每次循环score_raw原始分数++，score根据score_raw得到
	int score_raw = 0;
	int score = 0;

	int8_t leg = 0;

	//开始
	for(;;)
	{
		OLED_NewFrame();
		//jump状态机的状态在按下按键之后进行检测，如果是jump=0时则说明在平地，那么允许起跳
		//jump状态说明，jump=0说明在平地，jump非0说明在空中，并且jump的不同取值决定了此时处于跳跃的帧(time_distance[38])
		if (HAL_GPIO_ReadPin(JUMP_GPIO_Port, JUMP_Pin) == GPIO_PIN_RESET || HAL_GPIO_ReadPin(START_GPIO_Port, START_Pin) == GPIO_PIN_RESET)
		{
			if (jump == 0) jump = 1;
		}

		//碰撞检测01，检测条件需要同时满足三个:①恐龙的右边大于障碍物;②障碍物还在屏幕之内;③恐龙的底部y轴大于障碍物顶部
		if(tree_x <= (dino_right-((jump<5) ? jump : 5)) && tree_x > (DINO_INIT_X+1) && (dino_y + dino_back_legImg.h) >= (BASE_LINE_Y - tree->h))
		{
			moveDino(dino_y, -2);//显示死亡的恐龙

			//显示碰撞时坐标的障碍物
			moveTree(tree_x, tree);
			moveTree(tree1_x, tree1);

			//显示地面和成绩结算
			OLED_DrawLine(BASE_LINE_X, BASE_LINE_Y, BASE_LINE_X1, BASE_LINE_Y, OLED_COLOR_NORMAL);
			displayScore(score, 0);
			if(score > highest_score)
			{
				highest_score = score;//update latest highest score
				OLED_PrintString(75, 22, "新纪录！", &font12x12, OLED_COLOR_NORMAL);
			}
			else
			{
				displayScore(score, 1);
			}
			OLED_ShowFrame();
			break;//跳出主程序,准备下一把
		}

		//碰撞检测02
		if (tree1_x <= (dino_right-((jump<5) ? jump : 5)) && tree1_x > (DINO_INIT_X+1) && (dino_y + dino_back_legImg.h) >= (BASE_LINE_Y - tree1->h))
		{
			moveDino(dino_y, -2);

			moveTree(tree_x, tree);
			moveTree(tree1_x, tree1);

			OLED_DrawLine(BASE_LINE_X, BASE_LINE_Y, BASE_LINE_X1, BASE_LINE_Y, OLED_COLOR_NORMAL);
			displayScore(score, 0);
			if(score > highest_score)
			{
				highest_score = score;
				OLED_PrintString(75, 22, "新纪录！", &font12x12, OLED_COLOR_NORMAL);
			}
			else
			{
				displayScore(score, 1);
			}
			OLED_ShowFrame();
			break;//跳出主程序,准备下一把
		}

		//跳跃状态机
		if(jump > 0)
		{
			dino_y = DINO_INIT_Y - time_distance[jump - 1];

			//防止jump-1越界检索
			if(++jump > 38) jump = 0;
		}

		//分数计算并显示
	    score_raw++;
	    score = score_raw / 5;
	    displayScore(score, 0);

	    //检测jump状态机改变恐龙显示
	    if(jump != 0)
	    {
	    	moveDino(dino_y,-1);
	    }
	    else
	    {
	    	moveDino(dino_y, leg > 4 ? 1 : 0);
	    	if(++leg > 9) leg = 0;//leg取值在0-9，每次循环加1，根据leg的值决定显示恐龙奔跑的不同动画
	    }


	    //显示移动的障碍物，每次循环都会执行，因为无论什么状态都需要显示障碍物
	    moveTree(tree_x,tree);
	    moveTree(tree1_x, tree1);
	    OLED_DrawLine(BASE_LINE_X, BASE_LINE_Y, BASE_LINE_X1, BASE_LINE_Y, OLED_COLOR_NORMAL);

	    //循环累减坐标，表现障碍物的移动
	    tree_x -= 2;
	    tree1_x -= 2;

	    //当一开始的两个障碍物超出屏幕之外，重新进行一轮显示
	    if(tree_x <= 0)
	    {
	    	tree_x = tree_interval + HAL_GetTick()/10%20;
	    	tree = (HAL_GetTick() % 4) ? (Image *)&tree_smallImg : (Image *)&tree_bigImg;
	    }
	    if(tree1_x <= 0)
	    {
	    	tree1_x = tree1_interval + HAL_GetTick()/10%20;
	    	tree1 = (HAL_GetTick() % 2) ? (Image *)&tree_smallImg : (Image *)&tree_bigImg;
	    }

	    //间隔修复，避免障碍物生成太紧
	    static int16_t interval;
	    interval = tree_x - tree1_x;
	    if (interval > 0 && interval <= 46)
	      tree_x += interval;
	    else if (interval < 0 && interval >= -46)
	      tree1_x += interval;

	    OLED_ShowFrame();
	}
}




























