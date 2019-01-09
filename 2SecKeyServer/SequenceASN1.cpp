#include "SequenceASN1.h"

#include <iostream>
using namespace std;

SequenceASN1::SequenceASN1():BaseASN1()
{

}

//��һ���ڵ���int����
int SequenceASN1::writeHeadNode(int iValue)
{
	int ret = 0;

	ret = DER_ItAsn1_WriteInteger(iValue, &m_header);
	if (0 != ret)
	{
		cout << "DER_ItAsn1_WriteInteger failed...." << endl;
		return ret;
	}

	//m_nextָ����������һ���ڵ�
	m_next = m_header;

	return 0;
}

//�����ַ���  ����ĵ�һ���ڵ�
int SequenceASN1::writeHeadNode(char * sValue, int len)
{
	int ret = 0;

	ret = EncodeChar(sValue, len, &m_header);
	if (0 != ret)
	{
		cout << "EncodeChar failed... " << endl;
		return ret;
	}

	//m_nextָ����������һ���ڵ�
	m_next = m_header;

	return 0;
}

//�����̽ڵ�
int SequenceASN1::writeNextNode(int iValue)
{
	int ret = 0;

	//������������
	ret = DER_ItAsn1_WriteInteger(iValue, &(m_next->next));
	if (0 != ret)
	{
		cout << "DER_ItAsn1_WriteInteger failed...." << endl;
		return ret;
	}

	//m_next��Զָ����������һ���ڵ�
	m_next = m_next->next;

	return 0;
}

//�����̽ڵ�
int SequenceASN1::writeNextNode(char * sValue, int len)
{
	int ret = 0;

	ret = EncodeChar(sValue, len, &(m_next->next));
	if (0 != ret)
	{
		cout << "EncodeChar failed... " << endl;
		return ret;
	}

	//m_next��Զָ����������һ���ڵ�
	m_next = m_next->next;

	return 0;
}

//���� ����
int SequenceASN1::readHeadNode(int & iValue)
{
	int num = -1;
	int ret = -1;

	ret = DER_ItAsn1_ReadInteger(m_header, (ITCAST_UINT32*)&num);
	if (0 != ret)
	{
		cout << "DER_ItAsn1_ReadInteger failed..." << endl;
		return ret;
	}

	iValue = num;

	//ָ����һ���ڵ�
	m_next = m_header->next;

	return 0;
}

//���� char*
int SequenceASN1::readHeadNode(char * sValue)
{
	int ret = -1;
	ret = DER_ItAsn1_ReadPrintableString(m_header, &m_temp); //1.free
	if (0 != ret)
	{
		cout << "DER_ItAsn1_ReadPrintableString failed..." << endl;
		return ret;
	}

	//��������
	memcpy(sValue, m_temp->pData, m_temp->dataLen);

	//ָ����һ���ڵ�
	m_next = m_header->next;

	//�ͷ���ʱ�ڵ�
	DER_ITCAST_FreeQueue(m_temp);

	return 0;
}

//���벻�ǵ�һ���ڵ�Ľڵ� ���������
int SequenceASN1::readNextNode(int & iValue)
{
	int ret = -1;
	ret = DER_ItAsn1_ReadInteger(m_next, (ITCAST_UINT32 *)&iValue);
	if (0 != ret)
	{
		cout << "DER_ItAsn1_ReadInteger failed..." << endl;
		return ret;
	}

	//ָ����һ���ڵ�
	m_next = m_next->next;

	return 0;
}

int SequenceASN1::readNextNode(char * sValue)
{
	int ret = -1;
	ret = DER_ItAsn1_ReadPrintableString(m_next, &m_temp); //1.free
	if (0 != ret)
	{
		cout << "DER_ItAsn1_ReadPrintableString failed..." << endl;
		return ret;
	}

	//��������
	memcpy(sValue, m_temp->pData, m_temp->dataLen);

	//ָ����һ���ڵ�
	m_next = m_next->next;

	//�ͷ��ڴ�
	DER_ITCAST_FreeQueue(m_temp);

	return 0;
}

//����ṹ��
int SequenceASN1::packSequence(char ** outData, int & outLen)
{
	int ret = -1;

	char *out = NULL;

	//����ṹ��
	ret = DER_ItAsn1_WriteSequence(m_header, &m_temp);
	if (0 != ret)
	{
		cout << "DER_ItAsn1_WriteSequence failed..." << endl;
		return ret;
	}

	//����ռ�
	out = new char[m_temp->dataLen + 1];
	if (NULL == out)
	{
		cout << "new out failed.." << endl;
		return 1;
	}

	//��������
	memcpy(out, m_temp->pData, m_temp->dataLen);

	//����
	*outData = out;
	outLen = m_temp->dataLen;

	//�ͷ���ʱ�ڴ�
	DER_ITCAST_FreeQueue(m_temp);

	return 0;
}

//����ṹ��
int SequenceASN1::unpackSequence(char * inData, int inLen)
{
	int ret = -1;

	//��char*����ת��ΪANYBUF����
	ret = DER_ITCAST_String_To_AnyBuf(&m_temp, (unsigned char *)inData, inLen); //1. free
	if (0 != ret)
	{
		cout << "DER_ITCAST_String_To_AnyBuf failed..." << endl;
		return ret;
	}

	//����ṹ�� �õ�����
	ret = DER_ItAsn1_ReadSequence(m_temp, &m_header);
	if (0 != ret)
	{
		cout << "DER_ItAsn1_ReadSequence failed..." << endl;
		return ret;
	}

	//�ͷ���ʱ�ڵ���ڴ�
	DER_ITCAST_FreeQueue(m_temp);

	return 0;
}

//�ͷ��ڴ�
void SequenceASN1::freeSequence(ITCAST_ANYBUF * node)
{
	//nodeΪNULL���ͷ� ����
	if (NULL == node)
	{
		DER_ITCAST_FreeQueue(m_header);
	}
	else
	{
		//node��ΪNULL ���ͷŽڵ�
		DER_ITCAST_FreeQueue(node);
	}
}
