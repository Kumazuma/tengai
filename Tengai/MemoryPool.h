#pragma once
#include<iostream>
#include <list>
#include <new.h>
#define dfMemoryPool_Default_Size 2000
#define dfMemoryPool_MagicNumber 0x12345678

using namespace std;
//typedef int T;
template <class T>
class MemoryPool
{
public:
	struct DataNode
	{
		T pData;
		DataNode* pNext = nullptr;
		int check = dfMemoryPool_MagicNumber;
	};
public:
	MemoryPool(int _size = dfMemoryPool_Default_Size)
	{
		Initialize(_size);
	}
	~MemoryPool()
	{
		Release();
	}

private:
	void Initialize(int _size)
	{
		top = (DataNode*)malloc(sizeof(DataNode));

		DataNode* node = nullptr;
		for (int i = 0; i < _size; i++)
		{
			node = (DataNode*)malloc(sizeof(DataNode));
			node->pNext = nullptr;
			node->check = dfMemoryPool_MagicNumber;
			Push(node);
			clearList.push_back(node);
		}
	}
	void Release()
	{
		Clear();
		free(top);
	}
	
public:
	T* Alloc()
	{
		DataNode* pNode = nullptr;
		if (!Pop(&pNode))
		{
			// 여기서 터지면 메모리풀 생성한계 초과입니다.
			Crash();
		}

		T* pData = (T*)pNode;
		new (pData)T;
		return pData;
	}
	bool Free(T* _data)
	{
		DataNode* pNode = (DataNode*)_data;
		if (pNode->check != dfMemoryPool_MagicNumber)
		{
			// 여기서 터지면 매직넘버 오류 (외부에서 생성한 데이터를 넣어줄 경우)
			Crash();
			return false;
		}

		_data->~T();

		Push(pNode);

		return true;
	}
private:
	void Push(DataNode* pNode)
	{
		DataNode* pTemp = top->pNext;
		top->pNext = pNode;
		pNode->pNext = pTemp;
	}
	bool Pop(DataNode** pOutNode)
	{
		if (IsEmpty())
		{
			// 여기서 터지면 메모리풀 생성한계 초과입니다.
			Crash();
			return false;
		}

		DataNode* popNode = top->pNext;
		DataNode* pFront = popNode->pNext;
		top->pNext = pFront;

		*pOutNode = popNode;

		return true;
	}
	bool IsEmpty()
	{
		return (top->pNext == nullptr);
	}
	void Clear()
	{
		auto iter = clearList.begin();
		auto end = clearList.end();
		for (; iter != end;)
		{
			free(*iter);
			iter = clearList.erase(iter);
		}
	}
	
	void Crash()
	{
		int* p = nullptr;
		*p = 10;
	}

private:
	DataNode* top = nullptr;
	list<DataNode*> clearList;
	int size = 0;
};