#include "ViewFolder.h"

Component::Component(const std::wstring& path) {
    fs::path file(path);
    this->name = file.filename().generic_string();
    const std::string temp(path.begin(), path.end());
    if (this->name == "") this->name = temp;
}
std::string Component::getName() {
    return name;
};

File::File(const std::wstring& path) : Component::Component(path) {
    this->size = fs::file_size(path);
}
uintmax_t File::getSize() {
    return size;
}
void File::showAllChildren(int level = 1) {};
