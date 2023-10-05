#pragma once
#include "DBConnection.h"

class ClassThatUsesDB {
public:
    ClassThatUsesDB(DBConnection* connection) : connection_(connection), isOpen_(false) {}
    bool openConnection() {
        if (!connection_) {
            return false;
        }

        if (!connection_->open()) {
            return false;
        }

        isOpen_ = true;
        return true;
    }

    int useConnection(const std::string& query) {
        if (!isOpen_) {
            return false;
        }

        return connection_->execQuery(query);
    }

    void closeConnection() {
        if (isOpen_) {
            connection_->close();
            isOpen_ = false;
        }
    }

private:
    DBConnection* connection_;
    bool isOpen_;
};