#include "commentary_social_networks.hpp"

#include "change_log.hpp"
#include "time_duration.hpp"

CommentarySocialNetworks::CommentarySocialNetworks(const BigUint& id)
    : BaseInteraction(id, InteractionType::commentarySocialNetworks), is_first(true)
{
}

CommentarySocialNetworks::CommentarySocialNetworks(
    const BigUint&                     id,
    const std::string&                 title,
    const OptionalStr&                 external_id,
    const OptionalStr&                 description,
    const OptionalStr&                 subject,
    const std::optional<TimeDuration>& interaction_duration,
    const Priority&                    priority,
    const InternalEmployeePtr&         manager,
    const DatePtr&                     start_date,
    const DatePtr&                     end_date,
    const InternalEmployeePtr&         checker,
    std::vector<std::string>           tags,
    std::vector<InteractionResult>     results,
    std::vector<Note>                  notes,
    std::vector<StringPair>            more_data,
    std::vector<InteractionPtr>        related_interactions,
    std::vector<FilePtr>               attachment_files,
    std::vector<PersonPtr>             participants,
    const std::string&                 nickname,
    const PersonPtr&                   author,
    const std::string&                 commentary,
    const CommentarySocialNetworksPtr& answer_to,
    const CommentarySocialNetworksPtr& answer,
    const Date&                        date_sending,
    bool                               is_first
)
    : BaseInteraction(
          id,
          title,
          external_id,
          description,
          subject,
          interaction_duration,
          priority,
          manager,
          start_date,
          end_date,
          checker,
          InteractionType::commentarySocialNetworks,
          std::move(tags),
          std::move(results),
          std::move(notes),
          std::move(more_data),
          std::move(related_interactions),
          std::move(attachment_files),
          std::move(participants)
      )
    , nickname(nickname)
    , author(author)
    , commentary(commentary)
    , date_sending(date_sending)
    , answer_to(answer_to)
    , answer(answer)
    , is_first(is_first)
{
}

auto CommentarySocialNetworks::getNickname() const -> const std::string& { return nickname; }
auto CommentarySocialNetworks::getAuthor() const -> const PersonPtr { return author; }
auto CommentarySocialNetworks::getCommentary() const -> const std::string& { return commentary; }
auto CommentarySocialNetworks::getAnswerTo() const -> const CommentarySocialNetworksPtr
{
    return answer_to;
}
auto CommentarySocialNetworks::getAnswer() const -> const CommentarySocialNetworksPtr
{
    return answer;
}
auto CommentarySocialNetworks::getDateSending() const -> const Date& { return date_sending; }
auto CommentarySocialNetworks::getIsFirst() const -> bool { return is_first; }

void CommentarySocialNetworks::setNickname(
    const std::string& nickname, const InternalEmployeePtr& changer
)
{
    if (this->nickname != nickname) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(this->nickname
            )),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(nickname)),
            CommentarySocialNetworksFields::Nickname,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->nickname = nickname;
    }
}

void CommentarySocialNetworks::setAuthor(
    const PersonPtr& author, const InternalEmployeePtr& changer
)
{
    if (this->author != author) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->author),
            std::make_optional<ChangeLog::ValueVariant>(author),
            CommentarySocialNetworksFields::Author,
            ChangeLog::FieldType::Person,
            ChangeLog::FieldType::Person,
            ChangeLog::Action::Change
        ));
        this->author = author;
    }
}

void CommentarySocialNetworks::setCommentary(
    const std::string& commentary, const InternalEmployeePtr& changer
)
{
    if (this->commentary != commentary) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(this->commentary)
            ),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(commentary)),
            CommentarySocialNetworksFields::Commentary,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->commentary = commentary;
    }
}

void CommentarySocialNetworks::setAnswerTo(
    const CommentarySocialNetworksPtr& answer_to, const InternalEmployeePtr& changer
)
{
    if (this->answer_to != answer_to) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->answer_to),
            PTR_TO_OPTIONAL(answer_to),
            CommentarySocialNetworksFields::AnswerTo,
            this->answer_to ? ChangeLog::FieldType::CommentarySocialNetworks
                            : ChangeLog::FieldType::null,
            answer_to ? ChangeLog::FieldType::CommentarySocialNetworks : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->answer_to = answer_to;
    }
}

void CommentarySocialNetworks::setAnswer(
    const CommentarySocialNetworksPtr& answer, const InternalEmployeePtr& changer
)
{
    if (this->answer != answer) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->answer),
            PTR_TO_OPTIONAL(answer),
            CommentarySocialNetworksFields::Answer,
            this->answer ? ChangeLog::FieldType::CommentarySocialNetworks
                         : ChangeLog::FieldType::null,
            answer ? ChangeLog::FieldType::CommentarySocialNetworks : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->answer = answer;
    }
}

void CommentarySocialNetworks::setDateSending(const Date& date, const InternalEmployeePtr& changer)
{
    if (this->date_sending != date) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<Date>(this->date_sending)),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<Date>(date)),
            CommentarySocialNetworksFields::DateSending,
            ChangeLog::FieldType::Date,
            ChangeLog::FieldType::Date,
            ChangeLog::Action::Change
        ));
        this->date_sending = date;
    }
}

void CommentarySocialNetworks::setIsFirst(bool first, const InternalEmployeePtr& changer)
{
    if (this->is_first != first) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(this->is_first),
            std::make_optional<ChangeLog::ValueVariant>(first),
            CommentarySocialNetworksFields::IsFirst,
            ChangeLog::FieldType::Bool,
            ChangeLog::FieldType::Bool,
            ChangeLog::Action::Change
        ));
        this->is_first = first;
    }
}