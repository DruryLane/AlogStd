// AlgoStd.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <stack>
#include <string.h>

#pragma warning(disable:4996)
class TreeNode
{
public:
	TreeNode(char data) : _data(data), _isClose(false), _pNode(nullptr), _lNode(nullptr), _rNode(nullptr)
	{
	}
	~TreeNode()
	{
	
	}

	void AddChild(TreeNode* node)
	{
		if (node == nullptr)
		{
			return;
		}

		TreeNode* preLNode = _lNode;
		_lNode = node;
		_lNode->SetRNode(preLNode);
		_lNode->SetPNode(this);
	}

	bool SetClose(char data)
	{
		if ((_data == '{' && data == '}') || (_data == '(' && data == ')') || (_data == '[' && data == ']'))
		{
			_isClose = true;
			return true;
		}
		else
		{
			_isClose = false;
			return false;
		}
	}

	void SetPNode(TreeNode* node)
	{
		_pNode = node;
	}

	void SetRNode(TreeNode* node)
	{
		_rNode = node;
	}

	int GetData()
	{
		return _data;
	}

	TreeNode* GetPNode()
	{
		return _pNode;
	}

	TreeNode* GetLNode()
	{
		return _lNode;
	}

	TreeNode* GetRNode()
	{
		return _rNode;
	}

	bool IsClose()
	{
		return _isClose;
	}

	int Calc()
	{
		int result = 0;

		TreeNode* child = _lNode;
		if (child == nullptr)
		{
			if (_data == '(')
			{
				return 2;
			}
			else if (_data == '[')
			{
				return 3;
			}
			else
			{
				return 0;
			}
		}

		while (child != nullptr)
		{
			result += child->Calc();
			child = child->GetRNode();
		}

		if (_data == '(')
		{
			return 2 * result;
		}
		else if (_data == '[')
		{
			return 3 * result;
		}
		else
		{
			return result;
		}
	}

private:
	char _data;
	TreeNode* _pNode;
	TreeNode* _lNode;
	TreeNode* _rNode;

	bool _isClose;
};



int calcRecursive(char* expression, int size)
{
	int offset = 0;
	int openCount = 0;
	int closeCount = 0;
	int result = 0;

	if (size == 0)
	{
		return 1;
	}
	else if (size == 2)
	{
		if (expression[0] == '(')
		{
			return 2;
		}
		else
		{
			return 3;
		}
	}

	for (int i = 0; i < size; i++)
	{
		if ((expression[i] == '(') || (expression[i] == '['))
		{
			openCount++;
		}
		else
		{
			closeCount++;
		}

		if (openCount == closeCount)
		{
			int mul = 1;
			if (expression[i] == ')')
			{
				mul = 2;
			}
			else
			{
				mul = 3;
			}
			result += (mul * calcRecursive(&expression[offset + 1], i - offset - 1));
			openCount = 0;
			closeCount = 0;
			offset = i + 1;
		}
	}
	return result;
}

bool IsValid(char* expression, int size)
{
	std::stack<char> stack;

	if (size == 0)
	{
		return false;
	}

	for (int i = 0; i < size; i++)
	{
		if (expression[i] == '(' || expression[i] == '[')
		{
			stack.push(expression[i]);
		}
		else
		{
			char top = '\0';
			if (stack.size() > 0)
			{
				top = stack.top();
			}
			
			if (expression[i] == ')')
			{
				if (top == '(')
				{
					stack.pop();
				}
				else
				{
					stack.push(expression[i]);
				}
			}
			else
			{
				if (top == '[')
				{
					stack.pop();
				}
				else
				{
					stack.push(expression[i]);
				}
			}
		}
	}

	if (stack.size() != 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);

	char str[32] = {0, };
	int result = 0;

	scanf("%s", str);

	/* (IsValid(str, strlen(str)))
	{
		result = calcRecursive(str, strlen(str));
	}*/

	str[strlen(str)] = '}';
	TreeNode* root = new TreeNode('{');
	TreeNode* curNode = root;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == '(' || str[i] == '[')
		{
			TreeNode* child = new TreeNode(str[i]);
			curNode->AddChild(child);
			curNode = child;
		}
		else
		{
			if (!curNode->SetClose(str[i]))
			{
				break;
			}
			curNode = curNode->GetPNode();
		}
	}

	if (root->IsClose())
	{
		result = root->Calc();
	}
	printf("%d\n", result);
	return 0;
}