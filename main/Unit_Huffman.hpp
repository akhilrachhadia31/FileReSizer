#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <bitset>
#include <thread>
#include <mutex>

class Node
{
public:
    char value;
    unsigned freq;
    std::string codeWord;
    Node *left, *right;

    Node() : left(nullptr), right(nullptr) {}

    Node(int f, Node *l, Node *r) : freq(f), left(l), right(r) {}
};

struct comp
{
    bool operator()(Node *one, Node *two)
    {
        return one->freq > two->freq;
    }
};

int BinaryToDec(const std::string &bin)
{
    std::bitset<8> bit(bin);
    int ans = bit.to_ulong();
    return ans;
}

std::string DeToBinary(int dec)
{
    std::bitset<8> bit(dec);
    std::string ans = bit.to_string();
    return ans;
}

class Huffman
{
private:
    std::vector<Node *> Vec_Node;
    std::string SourceFileName, DestFilename;
    std::fstream Source, Dest;
    Node *root;
    std::priority_queue<Node *, std::vector<Node *>, comp> pq;

public:
    Huffman(const std::string &s, const std::string &d) : SourceFileName(s), DestFilename(d), root(nullptr)
    {
        for (int i = 0; i < 256; ++i)
        {
            Vec_Node.push_back(new Node());
            Vec_Node[i]->value = i;
            Vec_Node[i]->freq = 0;
        }
    }

    void make_codeword(Node *root, std::string code)
    {
        if (!root->left && !root->right)
        {
            root->codeWord = code;
            return;
        }
        make_codeword(root->left, code + '0');
        make_codeword(root->right, code + '1');
    }

    void Build_Huffman_Tree()
    {
        Source.open(SourceFileName, std::ios::in | std::ios::binary);
        if (!Source.is_open())
        {
            std::cerr << "Failed to open the source file." << std::endl;
            return;
        }

        char c;
        while (Source.get(c))
        {
            Vec_Node[static_cast<unsigned char>(c)]->freq++;
        }

        Source.close();

        for (int i = 0; i < 256; ++i)
        {
            if (Vec_Node[i]->freq > 0)
            {
                pq.push(Vec_Node[i]);
            }
        }

        std::priority_queue<Node *, std::vector<Node *>, comp> temp(pq);
        while (temp.size() > 1)
        {
            Node *l = temp.top();
            temp.pop();

            Node *r = temp.top();
            temp.pop();

            root = new Node(l->freq + r->freq, l, r);
            temp.push(root);
        }

        make_codeword(root, "");
    }

    void Write_Encoded_code()
    {
        Source.open(SourceFileName, std::ios::in | std::ios::binary);
        Dest.open(DestFilename, std::ios::out | std::ios::binary);
        if (!Source.is_open())
        {
            std::cerr << "Error opening source file." << std::endl;
            return;
        }
        if (!Dest.is_open())
        {
            std::cerr << "Error opening destination file." << std::endl;
            return;
        }

        std::string decoded_code;
        std::string s;

        decoded_code += char(pq.size());
        std::priority_queue<Node *, std::vector<Node *>, comp> temp_pq(pq);

        while (!temp_pq.empty())
        {
            Node *curr = temp_pq.top();
            temp_pq.pop();

            decoded_code += curr->value;

            s.assign(127 - curr->codeWord.length(), '0');
            s += '1';
            s += curr->codeWord;

            for (size_t i = 0; i < s.size(); i += 8)
            {
                decoded_code += static_cast<char>(BinaryToDec(s.substr(i, 8)));
            }
        }

        s.clear();

        char c;
        while (Source.get(c))
        {
            s += Vec_Node[static_cast<unsigned char>(c)]->codeWord;
            while (s.length() >= 8)
            {
                decoded_code += static_cast<char>(BinaryToDec(s.substr(0, 8)));
                s.erase(0, 8);
            }
        }

        int padding = 8 - s.size();
        if (!s.empty())
        {
            s.append(padding, '0');
        }

        decoded_code += static_cast<char>(BinaryToDec(s));
        decoded_code += static_cast<char>(padding);

        Dest.write(decoded_code.c_str(), decoded_code.size());

        Source.close();
        Dest.close();
    }

    void Get_Huffman_Tree()
    {
        Source.open(SourceFileName, std::ios::in | std::ios::binary);
        if (!Source.is_open())
        {
            std::cerr << "Failed to open the source file." << std::endl;
            return;
        }
        if (Source.eof())
        {

            std::cerr << "This File is empty." << std::endl;
            return;
        }

        unsigned char treeSize;
        Source.read(reinterpret_cast<char *>(&treeSize), 1);

        root = new Node();
        for (int i = 0; i < treeSize; ++i)
        {
            char charcode;
            Source.read(&charcode, 1);
            unsigned char codewordLen[16];

            Source.read(reinterpret_cast<char *>(&codewordLen), 16);

            std::string codestr = "";
            for (int i = 0; i < 16; i++)
            {
                codestr += (DeToBinary(codewordLen[i]));
            }

            int k = 0;
            while (codestr[k] == '0')
            {
                k++;
            }
            codestr = codestr.substr(k + 1);

            Node *node = root;
            for (char bit : codestr)
            {
                if (bit == '0')
                {
                    if (node->left == nullptr)
                    {
                        node->left = new Node();
                    }
                    node = node->left;
                }
                else
                {
                    if (node->right == nullptr)
                    {
                        node->right = new Node();
                    }
                    node = node->right;
                }
            }
            node->value = charcode;
        }

        Source.close();
    }

    void Write_Decoded_Data()
    {
        Source.open(SourceFileName, std::ios::in | std::ios::binary);
        if (!Source.is_open())
        {
            std::cerr << "Failed to open the source file." << std::endl;
            return;
        }
        Dest.open(DestFilename, std::ios::out);
        if (!Dest.is_open())
        {
            std::cerr << "Failed to open the destination file." << std::endl;
            return;
        }

        unsigned char treeSize;
        Source.read(reinterpret_cast<char *>(&treeSize), 1);

        Source.seekg(-1, std::ios::end);
        char padding;
        Source.read((&padding), 1);

        Source.seekg(1 + 17 * treeSize, std::ios::beg);

        std::string encoded_data = "";
        unsigned char c;
        Source.read(reinterpret_cast<char *>(&c), 1);
        while (!Source.eof())
        {
            encoded_data += c;
            Source.read(reinterpret_cast<char *>(&c), 1);
        }

        Node *node = root;
        std::string path = "";
        for (size_t i = 0; i <= encoded_data.size() - 2; ++i)
        {
            path = DeToBinary(encoded_data[i]);

            if (i == encoded_data.size() - 2)
            {
                path = path.substr(0, 8 - padding);
            }

            for (int j = 0; j < path.size(); j++)
            {

                if (path[j] == '0')
                {
                    node = node->left;
                }
                else
                {
                    node = node->right;
                }
                if (!node->left && !node->right)
                {
                    Dest.put(char(node->value));
                    node = root;
                }
            }
        }
        Source.close();
        Dest.close();
    }

    void compression()
    {
        Build_Huffman_Tree();
        Write_Encoded_code();
    }

    void decompression()
    {
        Get_Huffman_Tree();
        Write_Decoded_Data();
    }
};
