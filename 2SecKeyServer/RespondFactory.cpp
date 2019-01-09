#include "RespondFactory.h"
#include "RespondCodec.h"


//���캯��
RespondFactory::RespondFactory()
{
}

//��������
RespondFactory::~RespondFactory()
{
}

//����ģʽ��Ա����   ֻ���𴴽���Ӧ���ĵı�������
Codec * RespondFactory::createCodec(void * arg)
{
	Codec *codec = NULL;

	if (NULL == arg)
	{
		//����һ����Ӧ���Ľ������
		codec = new RespondCodec;
	}
	else
	{
		//����һ����Ӧ���ı������
		codec = new RespondCodec((RespondMsg*)arg);
	}

	return codec;
}
