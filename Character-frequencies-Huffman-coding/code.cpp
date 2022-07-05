#include <bits/stdc++.h>
using namespace std;

class node{    
public:
    string name;
    long long int frequency;
    node* left;
    node* right;
    string code_word;
    
    node(string name, long long int f){
        this->name = name;
        this->frequency = f;
        this->left = nullptr;
        this->right = nullptr;
        this->code_word = "";
    }
    
};



priority_queue<pair<long long int, string>,
                vector<pair<long long int, string>>,
                greater<pair<long long int, string>>> pq;

pair<long long int, string> left_node, right_node;

map<string, pair<long long int, string>> code_words;
map<string, node*> nodes;

string name, s;
long long int frequency;
unsigned int max_name_length = 1, max_code_word_length = 0;

void tree_track(node* current_node, string code){
    if(current_node->left == nullptr && current_node->right == nullptr){
        code_words[current_node->name] = {current_node->frequency, code};
        max_code_word_length = max(max_code_word_length, (unsigned int)code.length());
        return;
    }
    if(current_node->left != nullptr)
        tree_track(current_node->left, code + "0");
    if(current_node->right != nullptr)
        tree_track(current_node->right, code + "1");
    current_node->code_word = code;
}

int main()
{
    cin >> s;
    set<char> characters;
    for (int i = 0; i < s.length(); ++i) {
        if (characters.find(s[i]) == characters.end()){
            characters.insert(s[i]);
            node* pointer = new node(string(1, s[i]), count(s.begin(), s.end(), s[i]));
            pq.push({pointer->frequency, pointer->name});
            nodes[pointer->name] = pointer;
        }
    }
    
    node* root;
    
    while(!pq.empty()){
        left_node = pq.top(); pq.pop();
        
        if(pq.empty()){
            root = nodes[left_node.second];
            break;
        }
        
        right_node = pq.top(); pq.pop();
        
        name = left_node.second + right_node.second;
        node* pointer = new node(name, right_node.first + left_node.first);
        pointer->right = nodes[right_node.second];
        pointer->left = nodes[left_node.second];
        nodes[pointer->name] = pointer;
        pq.push({pointer->frequency, pointer->name});
    }

    tree_track(root, "");

    cout << code_words.size() << endl;
    for(auto answer: code_words)
        cout << answer.first << " " << answer.second.first << " " << answer.second.second << endl;
    
    return 0;
}
