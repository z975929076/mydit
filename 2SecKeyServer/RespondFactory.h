#pragma once
#include "FactoryCodec.h"
class RespondFactory : public FactoryCodec
{
public:
	RespondFactory();
	~RespondFactory();

	//������Ӧ���ı�������
	Codec *createCodec(void *arg = NULL);
};

