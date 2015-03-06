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
	//	if(NULL == _buffer){
	//		malloc()
	//	}else{
		_buffer = (FLOAT*) realloc(_buffer,sizeof(float)*_width*_maxHeight);	
	//	}
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
