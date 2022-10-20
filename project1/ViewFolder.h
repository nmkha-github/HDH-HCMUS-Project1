#pragma once
#ifndef ViewFolder
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class Component {
private:
    std::string name;
public:
    Component(const std::wstring& path);
    std::string getName();
    virtual uintmax_t getSize() = 0;
    virtual void showAllChildren(int level = 1) = 0;
};

class File : public Component {
private:
    uintmax_t size;
public:
    File(const std::wstring& path);
    uintmax_t getSize();
    void showAllChildren(int level);
};


class Folder :public Component {
private:
    std::vector <Component*> children;
public:
    Folder(const std::wstring& path) : Component::Component(path) {
        for (const auto& child : fs::directory_iterator(path)) {
            if (fs::is_directory(child.path())) {
                Folder* temp = new Folder(child.path());
                this->add(temp);
            }
            else {
                File* temp = new File(child.path());
                this->add(temp);
            }
        }
    };
    ~Folder() {
        for (auto p : children)
            delete p;
    }
    uintmax_t getSize() {
        int sumSize = 0;
        for (int i = 0; i < children.size(); i++)
            sumSize += children[i]->getSize();
        return sumSize;
    }
    void add(Component* p) {
        children.push_back(p);
    }
    void showChildren() {
        std::cout << this->getName() << '\n';
        for (int i = 0; i < children.size(); i++)
            if (children[i]->getName() != "System Volume Information") 
                std::cout << "|-- " << children[i]->getName() << '\n';
    }
    void showAllChildren(int level = 1) {
        if (level == 1) std::cout << this->getName() << '\n';
        for (int i = 0; i < children.size(); i++) {
            if (children[i]->getName() != "System Volume Information") {
                for (int j = 0; j < level - 1; j++) std::cout << "    ";
                std::cout << "|-- " << children[i]->getName() << '\n';
                children[i]->showAllChildren(level + 1);
            }
        }
    }
};
#endif // !ViewFolder
