#pragma once

#include "Codec.h"

class FactoryCodec
{
public:
	FactoryCodec();
	~FactoryCodec();

	//���𴴽���Ӧ��Ķ���
	virtual Codec *createCodec(void *arg = NULL);
};

