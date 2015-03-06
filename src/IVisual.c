/*
 * =====================================================================================
 *
 *       Filename:  IVisual.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年02月09日 15时46分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wps, 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <IVisual.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits> 


IVisual::IVisual(){
	_width = 0;
	_height = 0;
	_maxHeight = 0;
	_buffer = NULL;
	_filename.clear();
}

IVisual::~IVisual(){
	if (NULL != _buffer){
		free(_buffer);
		_buffer = NULL;
	}
	_width = 0;
	_height = 0;
	_maxHeight = 0;
	_filename.clear();
}

void IVisual::setName(const string name){
	_filename = name;
}

void IVisual::setName(const char *name){
	_filename = name;
}

void IVisual::setWidth(const UINT width){
	_width = width;
}


void IVisual::appendRows(FLOAT *buf, int rows){
	if(rows<=0)	return;
	
	/*realloc memcpy*/
	if(rows + _height > _maxHeight){
		_maxHeight = _maxHeight==0
			? (rows<1024?1024:rows)
			: _maxHeight<<1;
		_buffer = (FLOAT*) realloc(_buffer,sizeof(float)*_width*_maxHeight);	
	}
	memcpy(_buffer+_width*_height,buf, sizeof(FLOAT)*_width*rows);
	_height += rows;
	return;
}


void IVisual::save(){
	UINT len = _width*_height;
	FLOAT scale=0.0f;
	FLOAT max=std::numeric_limits<FLOAT>::min();
	FLOAT min=std::numeric_limits<FLOAT>::max();
	BYTE *image = (BYTE*)malloc(sizeof(BYTE)*len);
	FILE *file;
	UINT i;
	//change _buffer to image
	for(i=0;i<len;i++){
		max = _buffer[i] > max ? _buffer[i] : max;
		min = _buffer[i] < min ? _buffer[i] : min;
	}
	scale = 254.0f/(max-min);
	for(i=0;i<len;i++){	
		image[i] = (BYTE)((_buffer[i]-min)*scale);
	}
	//save
	char filename[1024];
	sprintf(filename,"%s_%0.6f_%0.6f_%0.6f_%d_%d.raw",_filename.c_str(),scale,max,min,_width,_height);
	file = fopen(filename,"wb");
	if(NULL == file){
		fprintf(stderr,"[ERROR]:file[%s]open failure\n",filename);
	}else{
		fwrite(image,_width*_height, sizeof(BYTE),file);
		fclose(file);
	}
	
	free(image);
	image = NULL;
	return;
}

//
// array resverse have fast alg ?
// change two data have fast alg ?
//
void IVisual::reverse(){
	if(isNullImage()){
		printf("WARNING:null image can't reverse!\n");
		return;
	}

	int curX=0,curY=0;
	float *pCurRow = NULL;
	float tmp;
	for(curY=0,pCurRow=_buffer;curY<_height;curY++,pCurRow+=_width){
		for(curX=0;curX<_width>>1;curX++){
			tmp = pCurRow[curX];
			pCurRow[curX] = pCurRow[_width-curX-1];
			pCurRow[_width-curX-1] = tmp;
		}
	}
	return;
}

void IVisual::rotate(ROTATETYPE type){
	if(isNullImage()){
		printf("WARNING:null image can't rotate\n");
		return;
	}

	int oldX=0,oldY=0;
	int newX=0,newY=0;
	int len=_width*_height;
	float *tmp = (float*)malloc(len*sizeof(FLOAT));
	float *src,*dst;
	if(NULL == tmp){
		printf("WARNING:tmp malloc error\n");
		return;
	}
	for(oldY=0;oldY<_height;oldY++){
		for(oldX=0;oldX<_width;oldX++){
			newX=oldY;
			newY=_width-oldX-1;
			*(tmp+newY*_height+newX) = *(_buffer+oldY*_width+oldX);
		}
	}

	memcpy(_buffer,tmp, len*sizeof(float));
	
	int n = _width;
	_width = _height;
	_height = n;

	free(tmp);
	tmp = NULL;
}

bool IVisual::isNullImage(){
	return (_width <= 0 || _height <= 0);
} 
