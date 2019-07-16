//========= Copyright 2015-2018, HTC Corporation. All rights reserved. ===========

#pragma once

class ITextureObject {
public:
	virtual ~ITextureObject() {}
	virtual void create(void* handler, unsigned int width, unsigned int height) = 0;
	virtual void getResourcePointers(void*& ptry, void*& ptru, void*& ptrv, void*& ptrmv_u, void*& ptrmv_v) = 0;
	virtual void upload(unsigned char* ych, unsigned char* uch, unsigned char* vch, unsigned char* mv_uch, unsigned char* mv_vch) = 0;
	virtual void destroy() = 0;

	static const unsigned int CPU_ALIGMENT = 64;
	static const unsigned int TEXTURE_NUM = 5;
};