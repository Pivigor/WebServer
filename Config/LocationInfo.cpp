//
// Created by polya on 5/16/22.
//

#include "LocationInfo.hpp"

LocationInfo::LocationInfo() {
//
//    this->root = nullptr;
//    this->location_name = nullptr;
    this->autoindex = 0;
    this->body_size = 100;
//    this->allowed_methods = {nullptr};
//    this->index = nullptr;
//    this->upload_path = nullptr;
//    this->error_page[0] = nullptr; // NOT OBLIGATORY PARAM

} // default init I WILL INITIALIZE WITH NULL AND YOU WILL CATCH THIS ERROR IN YOUR FUNC SIDE

LocationInfo::~LocationInfo() {
}

LocationInfo& LocationInfo::operator=(LocationInfo const &obj) {
    if (this == &obj) {
        return *this;
    }

    this->root = obj.root;
    this->location_name = obj.location_name;
    this->autoindex = obj.autoindex;
    this->body_size = obj.body_size;
    this->allowed_methods = obj.allowed_methods;
    this->index = obj.index;
    this->upload_path = obj.upload_path;
    this->error_page = obj.error_page;
    this->return_page = obj.return_page;

    return *this;
}

LocationInfo::LocationInfo(LocationInfo const &obj) {
    *this = obj;
}

//LocationInfo::LocationInfo(LocationInfo *obj) {
//
//    this->root = obj->root;
//    this->location_name = obj->location_name;
//    this->autoindex = obj->autoindex;
//    this->body_size = obj->body_size;
//    this->allowed_methods = obj->allowed_methods;
//    this->index = obj->index;
//    this->upload_path = obj->upload_path;
//    this->error_page = obj->error_page;
//    this->return_page = obj->return_page;
//}
