#include "RequestFactory.h"
#include "RequestCodec.h"

//���캯��
RequestFactory::RequestFactory()
{
}

//��������
RequestFactory::~RequestFactory()
{
}

//���������ı�������ķ���
//����ģʽ  �������๤��
Codec * RequestFactory::createCodec(void * arg)
{
	Codec *codec = NULL;

	if (NULL == arg)
	{
		//���������Ľ������
		codec = new RequestCodec();
	}
	else
	{
		//���������ı������
		codec = new RequestCodec((RequestMsg*)arg);
	}

	return codec;
}
