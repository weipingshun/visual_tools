#ifndef I_VISUAL_H_
#define I_VISUAL_H_

#include <iostream>
using namespace std;

typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned int UINT;

class IVisual{
public:
	IVisual();
	~IVisual();

	void setName(const string name);
	void setName(const char *name);
	
	void setWidth(const UINT width);
	//bool setHeight(UINT height);

	/*
	 * 将数据附加到_buffer中
	 * 输入：
	 *     buf
	 * 操作：
	 * 	将buf中的内容拷贝到_buffer中
	 * */
	void appendRows(FLOAT *buf, int rows);   
	void save();

//private:
//	void buffer2Image();

private:
	//BYTE *_image;
	FLOAT *_buffer;
	UINT _width;
	UINT _height;
	//UINT _maxWidth;
	UINT _maxHeight;
	string _filename;
};
#endif
