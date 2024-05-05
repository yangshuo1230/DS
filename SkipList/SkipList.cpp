#include <bits/stdc++.h> 
#include <vector>
#include <iostream>
#include <stdlib.h>

namespace YS{
	class SkipList
	{
		private:
			size_t RandomLevel()
			{
				size_t level = 1;
				while(rand() % 2)
				{
					level++;
				}
				return level > level_ ? level_ : level;
			}
		    struct SkipNode{
		 	    int key_;
		 	    std::vector<SkipNode*> forward_; 
		 	    SkipNode(int key ,size_t level):key_(key), forward_(level, NULL){}  
		    };	
		    size_t level_;
		    SkipNode* head_;
		public:
			SkipList(size_t level = 4):level_(level)
			{
				head_ = new SkipNode(-1, level);
			}
			bool search(int key)
			{
				SkipNode* head = head_;
				for(int i = level_ - 1; i >= 0; --i)
				{
					while(head -> forward_[i] != NULL && head -> forward_[i] -> key_  < key)
					{
						head = head -> forward_[i];
					}
					if(head -> forward_[i] != NULL && head -> forward_[i] -> key_ == key)
					{
						return true;
					} 
				}
				return false; 
			}
			void add(int key)
			{
				size_t level = RandomLevel();
				SkipNode* node = new SkipNode(key, level);
				SkipNode* head = head_;
				for(int i = level_ - 1; i >= 0 ; --i)
				{
					while(head -> forward_[i] != NULL && head -> forward_[i] -> key_ < key)
					{
						head = head -> forward_[i];
					}
					if(level > i)
					{
						node -> forward_[i] = head -> forward_[i];
						head -> forward_[i] = node; 
					}
				}
			}
			bool erase(int key)
			{
				SkipNode* head = head_;
				SkipNode* node = NULL;
				for(int i = level_ - 1; i >= 0; --i)
				{
					while(head -> forward_[i] != NULL && head -> forward_[i] -> key_  < key)
					{
						head = head -> forward_[i];
					}
					if(head -> forward_[i] != NULL && head -> forward_[i] -> key_ == key)
					{
						node = head -> forward_[i]; 
						head -> forward_[i] = node -> forward_[i]; 
					} 
				}
				if(node == NULL) return false;
				delete node;
				node = NULL;
				return true; 
			}
			void printSkipList()
			{
				for(int i = level_ - 1; i >= 0; --i)
				{
					SkipNode* head = head_;
					while(head -> forward_[0] != NULL)
					{
						if(head -> forward_.size() > i)
						{
							std::cout << head -> forward_[0] -> key_ << "\t"; 
						}
						else
						{
							std::cout << "\t"; 
						}
						head = head -> forward_[0];
					}
					std::cout << std::endl;
				}
			}
	};
}

int main()
{
	YS::SkipList skip_list;
	srand(time(0));
	for(int i = 0; i < 10; i++)
	{
		skip_list.add(rand() % 100);
	}
	skip_list.printSkipList();
	return 0;
}
