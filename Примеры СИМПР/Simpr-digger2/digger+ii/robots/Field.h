#pragma once

template <class Contents> class Field
{
public:
	Field(int width, int height);
	~Field(void);
	unsigned int Active;
	void ClearField();
	Contents*** cells;
	Contents* get(POINT pos);
	bool IsEmpty(POINT coord);
	bool IsBusy(POINT coord);
	bool IsFine(POINT coord);
	int width;
	int height;
	Contents* PutRandomThing();
	int FindInVector(Contents* c);
	vector <Contents*> ContentsVec;
};


template <class Contents>
Field<Contents>::Field(int width, int height)
{
	this->height=height;
	this->width=width;
	Active=0;
	cells=new Contents**[width];
	for(int i=0;i<width;i++)
		cells[i]=new Contents*[height];
	ClearField();
}

template <class Contents>
Field<Contents>::~Field(void)
{
	while(this->ContentsVec.size()!=0)
		this->ContentsVec.at(0)->Die();
	for(int i=0;i<width;i++)
		delete[] cells[i];
	
	delete[]cells;
}

template <class Contents>
Contents* Field<Contents>::get(POINT pos)
{
	return Contents[pos.x][pos.y];
}

template <class Contents>
int Field<Contents>::FindInVector(Contents* c)
{
	for(unsigned int i=0;i<ContentsVec.size();i++)
		if(ContentsVec.at(i)==c)
			return i;
	MessageBox(NULL,"Not found in ContentsVec","Error",MB_OK);
	return -1;
}


template <class Contents>
bool Field<Contents>::IsFine(POINT coord)
{
	if((coord.x<this->width)&&(coord.y<this->height)&&(coord.x>=0)&&(coord.y>=0))
		return 1;
	return 0;
}


template <class Contents>
bool Field<Contents>::IsEmpty(POINT coord)
{
	if(IsFine(coord))
		if(cells[coord.x][coord.y]==NULL)
			return 1;
	return 0;
}


template <class Contents>
bool Field<Contents>::IsBusy(POINT coord)
{
	if(IsEmpty(coord))
		return 0;
	return 1;
}

template <class Contents>
void Field<Contents>::ClearField()
{
	for(int i=0;i<width;i++)
		for(int n=0;n<height;n++)
			cells[i][n]=NULL;
}


template <class Contents>
Contents* Field<Contents>::PutRandomThing()
{
	Contents* k=new Contents();
	POINT dest;
	for(int i=0;i<100;i++)//100 attempts to put - field may be full
	{
		dest.x=true_rand(this->width-1);
		dest.y=true_rand(this->height-1);
		if(this->IsEmpty(dest))
		{
			this->cells[dest.x][dest.y]=k;
			ContentsVec.push_back(k);
			return k;
		}
	}
	return NULL;
}
