#pragma once
#include "DateTime/date.hpp"
#include "Usings/type_usings.hpp"

class Note {
public:
    Note(
        const WeakInternalEmployee& creator,
        const PersonPtr&           author,
        const std::string&         title,
        const std::string&         text
    );

    bool operator==(const Note& other) const;
    bool operator!=(const Note& other) const;

    auto getCreatedDate() const -> const Date&;
    auto getCreator() const -> const WeakInternalEmployee&;
    auto getAuthor() const -> const PersonPtr&;
    auto getTitle() const -> const std::string&;
    auto getText() const -> const std::string&;

    auto setTitle(const std::string& title);
    auto setText(const std::string& text);

private:
    Date                 created_date;
    WeakInternalEmployee creator;
    PersonPtr            author;
    std::string          title;
    std::string          text;
};