#include "note.hpp"

#include "Person/Employee/internal_employee.hpp"
#include "Person/person.hpp"
Note::Note(
    const WeakInternalEmployee& creator,
    const PersonPtr&            author,
    const std::string&          title,
    const std::string&          text
)
    : creator(creator), author(author), title(title), text(text)
{
    this->created_date = Date();
}
bool Note::operator==(const Note& other) const
{
    if (this->created_date != other.created_date) return false;
    if (this->creator.owner_before(other.creator) || other.creator.owner_before(this->creator))
        return false;
    if (this->author != other.author) return false;
    if (this->title != other.title) return false;
    if (this->text != other.text) return false;
    return true;
}
bool Note::operator!=(const Note& other) const { return !(*this == other); }

auto Note::getCreatedDate() const -> const Date& { return this->created_date; }
auto Note::getCreator() const -> const WeakInternalEmployee& { return this->creator; }
auto Note::getAuthor() const -> const PersonPtr& { return this->author; }
auto Note::getTitle() const -> const std::string& { return this->title; }
auto Note::getText() const -> const std::string& { return this->text; }

auto Note::setTitle(const std::string& title) { this->title = title; }
auto Note::setText(const std::string& text)
{
    if (this->text != text) this->text = text;
}
