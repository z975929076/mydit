#pragma once
#include "FactoryCodec.h"

//�����Ĺ�����  ��Ҫ���������ı��������߽�����󴴽�
class RequestFactory :public FactoryCodec
{
public:
	RequestFactory();
	~RequestFactory();
	Codec *createCodec(void *arg = NULL);
};

