#include <iostream>
#include <list>
#include <string>

struct ListNode
{
	ListNode* prev;
	ListNode* next;
	char data;
};

class List
{
public:
	List(const std::string& text)
	{
		for (const char symbol : text)
		{
			InsertNode(symbol);
		}

		tail->next = head;
		head->prev = tail;
	}

	ListNode* Encrypt(int startSymbol, int key) const
	{
		ListNode* node = head;
		for (int i = 1; i < startSymbol; ++i)
		{
			node = node->next;
		}

		for (int i = 0; i < key; ++i)
		{
			node = node->next;
		}
		return node;
	}

	ListNode* Decrypt(int startSymbol, int key) const
	{
		ListNode* node = head;
		for (int i = 1; i < startSymbol; ++i)
		{
			node = node->next;
		}

		for (int i = 0; i < key; ++i)
		{
			node = node->prev;
		}
		return node;
	}

	ListNode* InsertNode(const char& data);

public:
	ListNode* head;
	ListNode* tail;
};

ListNode* List::InsertNode(const char& data)
{
	ListNode* newNode = new ListNode;
	newNode->next = nullptr;
	newNode->data = data;

	if (head)
	{
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
	else
	{
		newNode->prev = nullptr;
		head = tail = newNode;
	}

	return newNode;
}

static const std::string lowerCase{ "abcdefghijklmnopqrstuvwxyz" };
static const std::string upperCase{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
static const List lowerCaseSymbols{ lowerCase };
static const List upperCaseSymbols{ upperCase };

void Encrypt(std::string& text, int key)
{
	for (char& symbol : text)
	{
		bool isLowerCase{ true };
		auto symbolId = lowerCase.find(symbol);
		if (symbolId == std::string::npos)
		{
			isLowerCase = false;
			symbolId = upperCase.find(symbol);
		}

		symbol = isLowerCase ? lowerCaseSymbols.Encrypt(symbolId + 1, key)->data : upperCaseSymbols.Encrypt(symbolId + 1, key)->data;
	}
}

void Decrypt(std::string& encryptedText, int key)
{
	for (char& symbol : encryptedText)
	{
		bool isLowerCase{ true };
		auto symbolId = lowerCase.find(symbol);
		if (symbolId == std::string::npos)
		{
			isLowerCase = false;
			symbolId = upperCase.find(symbol);
		}

		symbol = isLowerCase ? lowerCaseSymbols.Decrypt(symbolId + 1, key)->data : upperCaseSymbols.Decrypt(symbolId + 1, key)->data;
	}
}

int main()
{
	int key = 1; // Key for encryption
	std::string text;
	std::cin >> text;


	Encrypt(text, key);

	std::cout << text << std::endl;

	Decrypt(text, key);

	std::cout << text;


	return 0;
}