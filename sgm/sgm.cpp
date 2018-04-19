/*王博老师给的程序，还需要研究一下*/

/*
参数说明：
lImg: 左影像（RGB彩色）
lWidth: 左影像宽
lHeight: 左影像高
rImg, rWidth, rHeight: 右影像，宽和高
dP1, baseP2: 惩罚系数
m_minDisparity: 最小视差
m_Disprange: 视差搜索范围
C: 代价矩阵
S: 累积矩阵
dx, dy: 扫描线方向
ifLeft: 基准影像是否为左影像 TRUE为左影像  FALSE为右影像

调用案例：
//8方向约束
	SearchFromDirections1_8ReNew(lImg3, lWidth, lHeight, rImg3, rWidth, rHeight, P1, P2, m_minDisparity, m_Disprange, Cost, S, 1, 0, ifLeft);
	SearchFromDirections1_8ReNew(lImg3, lWidth, lHeight, rImg3, rWidth, rHeight, P1, P2, m_minDisparity, m_Disprange, Cost, S, -1, 0, ifLeft);
	SearchFromDirections1_8ReNew(lImg3, lWidth, lHeight, rImg3, rWidth, rHeight, P1, P2, m_minDisparity, m_Disprange, Cost, S, 0, 1, ifLeft);
	SearchFromDirections1_8ReNew(lImg3, lWidth, lHeight, rImg3, rWidth, rHeight, P1, P2, m_minDisparity, m_Disprange, Cost, S, 0, -1, ifLeft);
	SearchFromDirections1_8ReNew(lImg3, lWidth, lHeight, rImg3, rWidth, rHeight, P1, P2, m_minDisparity, m_Disprange, Cost, S, 1, 1, ifLeft);
	SearchFromDirections1_8ReNew(lImg3, lWidth, lHeight, rImg3, rWidth, rHeight, P1, P2, m_minDisparity, m_Disprange, Cost, S, -1, -1, ifLeft);
	SearchFromDirections1_8ReNew(lImg3, lWidth, lHeight, rImg3, rWidth, rHeight, P1, P2, m_minDisparity, m_Disprange, Cost, S, 1, -1, ifLeft);
	SearchFromDirections1_8ReNew(lImg3, lWidth, lHeight, rImg3, rWidth, rHeight, P1, P2, m_minDisparity, m_Disprange, Cost, S, -1, 1, ifLeft);
*/
BOOL SearchFromDirections1_8ReNew(BYTE *lImg,int lWidth,int lHeight,BYTE *rImg,int rWidth,int rHeight,
											 float dP1,float baseP2,int m_minDisparity,int m_Disprange,
											 float *C, float *S, int dx, int dy, BOOL ifLeft)
{
	//路径搜索范围 <= <=
	int startx,endx;
	int starty,endy;

	//搜索起点范围 <= <
	int sPx,ePx;
	int sPy,ePy;
	int px,py; //起点遍历步距

	int x,y,d;
	int maxD=m_minDisparity+m_Disprange;
	int LineRange;

	unsigned char *Img;
	int ImgWidth;

	double direction;
	if (ifLeft==TRUE) //表明为左影像
	{
		LineRange=lWidth*m_Disprange;
		Img=lImg;
		ImgWidth=lWidth;

		if (dx==1 && dy==0) 
		{ startx=0; endx=lWidth-1; starty=-1; endy=-1; sPx=-1; ePx=-1; sPy=0; ePy=lHeight; px=0; py=1; direction=0;} //从左向右搜索
		else if (dx==-1 && dy==0) 
		{ startx=lWidth-1; endx=0; starty=-1; endy=-1; sPx=-1; ePx=-1; sPy=0; ePy=lHeight; px=0; py=1; direction=PI;} //从右向左搜索
		else if (dx==0 && dy==1) 
		{ startx=-1; endx=-1; starty=0; endy=lHeight-1; sPx=0; ePx=lWidth; sPy=-1; ePy=-1; px=1; py=0; direction=PI/2;} //从下向上搜索
		else if (dx==0 && dy==-1) 
		{ startx=-1; endx=-1; starty=lHeight-1; endy=0; sPx=0; ePx=lWidth; sPy=-1; ePy=-1; px=1; py=0; direction=-PI/2;} //从上向下搜索
		else if (dx==1 && dy==1) 
		{ startx=0; endx=lWidth-1; starty=0; endy=lHeight-1; sPx=0; ePx=lWidth; sPy=1; ePy=lHeight; px=1; py=1; direction=PI/4;} //从左下开始搜索
		else if (dx==1 && dy==-1) 
		{ startx=0; endx=lWidth-1; starty=lHeight-1; endy=0; sPx=0; ePx=lWidth; sPy=lHeight-2; ePy=-1; px=1; py=-1; direction=-PI/4;} //从左上开始搜索
		else if (dx==-1 && dy==1) 
		{ startx=lWidth-1; endx=0; starty=0; endy=lHeight-1; sPx=lWidth-1; ePx=-1; sPy=1; ePy=lHeight; px=-1; py=1; direction=3*PI/4;} //从右下开始搜索
		else if (dx==-1 && dy==-1) 
		{ startx=lWidth-1; endx=0; starty=lHeight-1; endy=0; sPx=lWidth-1; ePx=-1; sPy=lHeight-2; ePy=-1; px=-1; py=-1; direction=5*PI/4;} //从右上开始搜索
		else return FALSE;
	}
	else              //表明为右影像
	{
		int RDispWith=rWidth;
		LineRange=RDispWith*m_Disprange;
		Img=rImg;
		ImgWidth=rWidth;
		
		if (dx==1 && dy==0)
		{ startx=0; endx=RDispWith-1; starty=-1; endy=-1; sPx=-1; ePx=-1; sPy=0; ePy=rHeight; px=0; py=1; direction=0;} //从左向右搜索
		else if (dx==-1 && dy==0) 
		{ startx=RDispWith-1; endx=0; starty=-1; endy=-1; sPx=-1; ePx=-1; sPy=0; ePy=rHeight; px=0; py=1; direction=PI;} //从右向左搜索
		else if (dx==0 && dy==1) 
		{ startx=-1; endx=-1; starty=0; endy=rHeight-1; sPx=0; ePx=RDispWith; sPy=-1; ePy=-1; px=1; py=0; direction=PI/2;} //从下向上搜索
		else if (dx==0 && dy==-1) 
		{ startx=-1; endx=-1; starty=rHeight-1; endy=0; sPx=0; ePx=RDispWith; sPy=-1; ePy=-1; px=1; py=0; direction=-PI/2;} //从上向下搜索
		else if (dx==1 && dy==1) 
		{ startx=0; endx=RDispWith-1; starty=0; endy=rHeight-1; sPx=0; ePx=RDispWith; sPy=1; ePy=rHeight; px=1; py=1; direction=PI/4;} //从左下开始搜索
		else if (dx==1 && dy==-1) 
		{ startx=0; endx=RDispWith-1; starty=rHeight-1; endy=0; sPx=0; ePx=RDispWith; sPy=rHeight-2; ePy=-1; px=1; py=-1; direction=-PI/4;} //从左上开始搜索
		else if (dx==-1 && dy==1)
		{ startx=RDispWith-1; endx=0; starty=0; endy=rHeight-1; sPx=RDispWith-1; ePx=-1; sPy=1; ePy=rHeight; px=-1; py=1; direction=3*PI/4;} //从右下开始搜索
		else if (dx==-1 && dy==-1) 
		{ startx=RDispWith-1; endx=0; starty=rHeight-1; endy=0; sPx=RDispWith-1; ePx=-1; sPy=rHeight-2; ePy=-1; px=-1; py=-1; direction=5*PI/4;} //从右上开始搜索
		else return FALSE;
	}

	float *preLr;//存储前一次搜索的代价
	preLr = new float [m_Disprange];
	memset(preLr,0,sizeof(float)*m_Disprange);
	float *Lr;
	Lr = new float [m_Disprange];
	memset(Lr,0,sizeof(float)*m_Disprange);

	float m_P2 = baseP2;
	int Pos;
	float min1, min2;
	int imgpos, imgpos2;
	int tmpR, tmpG, tmpB;
	int tmpR2, tmpG2, tmpB2;

	if (dy!=0)
	{
		int sx=startx-dx, ex=endx+dx;
		int sy=starty-dy, ey=endy+dy;

		for (x=sPx;x!=ePx;x=x+px)
		{
			y=starty;
			
			Pos = y*LineRange + x*m_Disprange;
			for (d = 0; d < m_Disprange; d++)//第一个起点初始化
			{
				preLr[d] = C[Pos + d];
			}

			int tx = x + dx, ty = y + dy;
			while (tx != ex && ty != ey)
			{
				//计算惩罚系数P2
				double deltaColor;
				imgpos = ty*ImgWidth * 3 + tx * 3;
				imgpos2 = (ty - dy)*ImgWidth * 3 + (tx - dx) * 3;
				tmpR2 = Img[imgpos + 0] - Img[imgpos2 + 0];
				tmpG2 = Img[imgpos + 1] - Img[imgpos2 + 1];
				tmpB2 = Img[imgpos + 2] - Img[imgpos2 + 2];
				tmpR = tmpR2; tmpR2 = tmpR2 >> 31; tmpR = tmpR + tmpR2 ^ tmpR2;
				tmpG = tmpG2; tmpG2 = tmpG2 >> 31; tmpG = tmpG + tmpG2 ^ tmpG2;
				tmpB = tmpB2; tmpB2 = tmpB2 >> 31; tmpB = tmpB + tmpB2 ^ tmpB2;
				deltaColor = (double)(tmpR + tmpG + tmpB) / 3.0;

				float dP2 = m_P2 / ((float)deltaColor + 0.1f);
				if (dP2 < dP1 + 0.01f) dP2 = dP1 + 0.01f;
				if (dP2 > m_P2) dP2 = m_P2;

				float minpreCost, minpreL;
				minpreL = preLr[0];
				int td;
				for (td = 1; td < m_Disprange; td++)
				{
					minpreL = (minpreL < preLr[td]) ? minpreL : preLr[td];
				}
				for (td = 0; td < m_Disprange; td++)
				{
					Lr[td] = -minpreL;
				}
				minpreL += dP2;

				Pos = ty*LineRange + tx*m_Disprange;
				//d=0
				min1 = (((preLr[1] + dP1) < minpreL) ? (preLr[1] + dP1) : minpreL);
				minpreCost = ((preLr[0] < min1) ? preLr[0] : min1);
				Lr[0] += (C[Pos] + minpreCost);
				S[Pos] += (Lr[0] - C[Pos]);
				Pos++;
				//0<d<m_Disprange-1
				for (d = 1; d < m_Disprange - 1; d++)
				{
					min1 = ((preLr[d - 1] < preLr[d + 1]) ? preLr[d - 1] : preLr[d + 1]) + dP1;
					min2 = ((min1 < minpreL) ? min1 : minpreL);
					minpreCost = ((preLr[d] < min2) ? preLr[d] : min2);
					Lr[d] += (C[Pos] + minpreCost);
					S[Pos] += (Lr[d] - C[Pos]);
					Pos++;
				}
				//d=m_Disprange-1
				d = m_Disprange - 1;
				min1 = (((preLr[d - 1] + dP1) < minpreL) ? (preLr[d - 1] + dP1) : minpreL);
				minpreCost = ((preLr[d] < min1) ? preLr[d] : min1);
				Lr[d] += (C[Pos] + minpreCost);
				S[Pos] += (Lr[d] - C[Pos]);

				tx = tx + dx;
				ty = ty + dy;
				memcpy(preLr, Lr, sizeof(float)*m_Disprange);
			}
		}
	}

	if (dx!=0)
	{
		int sx=startx-dx, ex=endx+dx;
		int sy=starty-dy, ey=endy+dy;

		for (y=sPy;y!=ePy;y=y+py)
		{
			x=startx;

			Pos = y*LineRange + x*m_Disprange;
			for (d = 0; d < m_Disprange; d++)//第一个起点初始化
			{
				preLr[d] = C[Pos + d];
			}

			int tx = x + dx, ty = y + dy;
			while (tx != ex && ty != ey)
			{
				//计算惩罚系数P2
				double deltaColor;
				imgpos = ty*ImgWidth * 3 + tx * 3;
				imgpos2 = (ty - dy)*ImgWidth * 3 + (tx - dx) * 3;
				tmpR2 = Img[imgpos + 0] - Img[imgpos2 + 0];
				tmpG2 = Img[imgpos + 1] - Img[imgpos2 + 1];
				tmpB2 = Img[imgpos + 2] - Img[imgpos2 + 2];
				tmpR = tmpR2; tmpR2 = tmpR2 >> 31; tmpR = tmpR + tmpR2 ^ tmpR2;
				tmpG = tmpG2; tmpG2 = tmpG2 >> 31; tmpG = tmpG + tmpG2 ^ tmpG2;
				tmpB = tmpB2; tmpB2 = tmpB2 >> 31; tmpB = tmpB + tmpB2 ^ tmpB2;
				deltaColor = (double)(tmpR + tmpG + tmpB) / 3.0;

				float dP2 = m_P2 / ((float)deltaColor + 0.1f);
				if (dP2 < dP1 + 0.01f) dP2 = dP1 + 0.01f;
				if (dP2 > m_P2) dP2 = m_P2;

				float minpreCost, minpreL;
				minpreL = preLr[0];
				int td;
				for (td = 1; td < m_Disprange; td++)
				{
					minpreL = (minpreL < preLr[td]) ? minpreL : preLr[td];
				}
				for (td = 0; td < m_Disprange; td++)
				{
					Lr[td] = -minpreL;
				}
				minpreL += dP2;

				Pos = ty*LineRange + tx*m_Disprange;
				//d=0
				min1 = (((preLr[1] + dP1) < minpreL) ? (preLr[1] + dP1) : minpreL);
				minpreCost = ((preLr[0] < min1) ? preLr[0] : min1);
				Lr[0] += (C[Pos] + minpreCost);
				S[Pos] += (Lr[0] - C[Pos]);
				Pos++;
				//0<d<m_Disprange-1
				for (d = 1; d < m_Disprange - 1; d++)
				{
					min1 = ((preLr[d - 1] < preLr[d + 1]) ? preLr[d - 1] : preLr[d + 1]) + dP1;
					min2 = ((min1 < minpreL) ? min1 : minpreL);
					minpreCost = ((preLr[d] < min2) ? preLr[d] : min2);
					Lr[d] += (C[Pos] + minpreCost);
					S[Pos] += (Lr[d] - C[Pos]);
					Pos++;
				}
				//d=m_Disprange-1
				d = m_Disprange - 1;
				min1 = (((preLr[d - 1] + dP1) < minpreL) ? (preLr[d - 1] + dP1) : minpreL);
				minpreCost = ((preLr[d] < min1) ? preLr[d] : min1);
				Lr[d] += (C[Pos] + minpreCost);
				S[Pos] += (Lr[d] - C[Pos]);

				tx = tx + dx;
				ty = ty + dy;
				memcpy(preLr, Lr, sizeof(float)*m_Disprange);
			}
		}
	}

	delete []preLr; preLr=NULL;
	delete []Lr; Lr=NULL;

	return TRUE;
}
