//========= Copyright 2015-2018, HTC Corporation. All rights reserved. ===========

#pragma once
#include "IDecoder.h"
#include <queue>
#include <mutex>

extern "C" {
#include <libavformat\avformat.h>
#include <libavcodec\avcodec.h>
#include <libswresample\swresample.h>
#include <libavutil/avutil.h>
#include <vector>

}

class DecoderFFmpeg : public virtual IDecoder
{
public:
	DecoderFFmpeg();
	~DecoderFFmpeg();

	bool init(const char* filePath);
	bool decode();
	void seek(double time);
	void destroy();
	
	VideoInfo getVideoInfo();
	AudioInfo getAudioInfo();
	void setVideoEnable(bool isEnable);
	void setAudioEnable(bool isEnable);
	void setAudioAllChDataEnable(bool isEnable);
	int	getVideoMotionVectors(unsigned char** outputU, unsigned char** outputV);
	double getVideoFrame(unsigned char** outputY, unsigned char** outputU, unsigned char** outputV);
	double getAudioFrame(unsigned char** outputFrame, int& frameSize);
	void freeVideoFrame();
	void freeAudioFrame();

	int getMetaData(char**& key, char**& value);
	
private:
	bool mIsInitialized;
	bool mIsAudioAllChEnabled;
	bool mUseTCP;				//	For RTSP stream.

	AVInputFormat *mInFormat; // optmisation paramter added on 26/6 by nitesh

	AVFormatContext* mAVFormatContext;
	AVStream*		mVideoStream;
	AVStream*		mAudioStream;
	AVCodec*		mVideoCodec;
	AVCodec*		mAudioCodec;
	AVCodecContext*	mVideoCodecContext;
	AVCodecContext*	mAudioCodecContext;

	AVPacket	mPacket;
	std::queue<AVFrame*> mVideoFrames;
	std::queue<AVFrame*> mAudioFrames;
	unsigned int mVideoBuffMax;
	unsigned int mAudioBuffMax;

	unsigned char* motionvectorU;
	unsigned char* motionvectorV;

	SwrContext*	mSwrContext;
	int initSwrContext();

	VideoInfo	mVideoInfo;
	AudioInfo	mAudioInfo;
	void updateBufferState();

	int mFrameBufferNum;
	
	bool isBuffBlocked();
	void updateVideoFrame();
	void updateAudioFrame();
	void freeFrontFrame(std::queue<AVFrame*>* frameBuff, std::mutex* mutex);
	void flushBuffer(std::queue<AVFrame*>* frameBuff, std::mutex* mutex);
	std::mutex mVideoMutex;
	std::mutex mAudioMutex;
	
	bool mIsSeekToAny;

	int loadConfig();
	void printErrorMsg(int errorCode);
};