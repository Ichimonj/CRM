#pragma once
#include <memory>

#include "date.hpp"
class InternalEmployee;
class Person;
using InternalEmployeePtr = std::shared_ptr<InternalEmployee>;
using PersonPtr           = std::shared_ptr<Person>;

class Note {
public:
    Note(
        const InternalEmployeePtr& creator,
        const PersonPtr&           author,
        const std::string&         title,
        const std::string&         text
    );
    bool operator==(const Note& other)const;

    auto getCreatedDate() const -> const Date&;
    auto getCreator() const -> const InternalEmployeePtr&;
    auto getAuthor() const -> const PersonPtr&;
    auto getTitle() const -> const std::string&;
    auto getText() const -> const std::string&;

    auto setTitle(const std::string& title);
    auto setText(const std::string& text);

private:
    Date                created_date;
    InternalEmployeePtr creator;
    PersonPtr           author;
    std::string         title;
    std::string         text;
};