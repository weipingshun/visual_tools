#ifndef I_VISUAL_H_
#define I_VISUAL_H_

#include <iostream>
using namespace std;

typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned int UINT;

class IVisual{
public:
	enum ROTATETYPE{CLOCKWISE=1,REVCLOCKWISE};

public:
	IVisual();
	~IVisual();

	void setName(const string name);
	void setName(const char *name);
	
	void setWidth(const UINT width);

	/*
	 * 将数据附加到_buffer中
	 * 输入：
	 *     buf
	 * 操作：
	 * 	将buf中的内容拷贝到_buffer中
	 * */
	void appendRows(FLOAT *buf, int rows);   
	
	/*
	 * 
	 * */
	void save();

	/*
	 * 图像进行对称操作
	 * */
	void reverse();

	/*
	 * 图像进行旋转
	 * */
	void rotate(ROTATETYPE type);

private:
	bool isNullImage();

private:
	FLOAT *_buffer;
	UINT _width;
	UINT _height;
	UINT _maxHeight;
	string _filename;
};
#endif
