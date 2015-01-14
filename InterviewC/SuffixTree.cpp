#include <string>
#include <map>
#include <memory>
#include <iostream>

namespace trie {
	class SuffixNode;
	typedef std::unique_ptr<SuffixNode> Node;

	unsigned long node_id = 0;
	class SuffixNode {
	  private:
		std::map<wchar_t, Node> children_;

	  public:
		SuffixNode* suffix;
		unsigned long id;

		SuffixNode(SuffixNode *node = NULL) {
			suffix = node == NULL ? this : node;
			id = node_id++;
		}

		~SuffixNode() {
			std::cout << this->id << std::endl;
		}

		SuffixNode* operator[](wchar_t c) {
			return children_.find(c) == children_.end() ? nullptr : children_[c].get();
		}

		void add_link(wchar_t c, SuffixNode* node) {
			children_[c] = Node(node);
		}

		bool contains(const std::wstring &pattern) {
			auto current = this;
			for (auto c : pattern) {
				if ((*current)[c] == NULL) return false;
				current = (*current)[c];
			}
			return true;
		}
	};

	Node build_trie(const std::wstring &s) {
		if (s.size() == 0) return Node(new SuffixNode());

		auto root = new SuffixNode();
		auto longest = new SuffixNode(root);
		root->add_link(s[0], longest);

		for (auto c : s.substr(1)) {
			SuffixNode *current = longest, *previous = NULL;
			bool added_to_root = false;

			while ((*current)[c] == NULL) {
				auto new_node = new SuffixNode();
				if (previous != NULL) previous->suffix = new_node;

				current->add_link(c, new_node);
				previous = new_node;

				if (current == root) added_to_root = true;
				current = current->suffix;
			}

			previous->suffix = added_to_root ? root : (*current)[c];

			longest = (*longest)[c];
		}
		return Node(root);
	}
}

//int main() {
//	auto trie = trie::build_trie(L"abaabcdeaaabb");
//
//	auto r1 = trie->contains(L"abc");
//	auto r2 = trie->contains(L"abcd");
//	auto r3 = trie->contains(L"abcde");
//	auto r4 = trie->contains(L"abcdx");
//
//	return 0;
//}