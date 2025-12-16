#include "phone_call_data.hpp"

#include "change_log.hpp"

PhoneCallData::PhoneCallData(const BigUint& id) : BaseInteraction(id, InteractionType::phoneCall) {}

PhoneCallData::PhoneCallData(
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
    const PhoneNumberPtr&              from_number,
    const PhoneNumberPtr&              to_number,
    const DatePtr&                     start_call,
    const DatePtr&                     end_call,
    const PersonPtr&                   call_creator,
    const std::string&                 call_provider,
    const std::optional<CallType>&     call_type
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
          InteractionType::phoneCall,
          std::move(tags),
          std::move(results),
          std::move(notes),
          std::move(more_data),
          std::move(related_interactions),
          std::move(attachment_files),
          std::move(participants)
      )
    , from_number(from_number)
    , to_number(to_number)
    , start_call(start_call)
    , end_call(end_call)
    , call_creator(call_creator)
    , call_provider(call_provider)
    , call_type(call_type)
{
}

auto PhoneCallData::getFromNumber() const -> const PhoneNumberPtr { return this->from_number; }
auto PhoneCallData::getToNumber() const -> const PhoneNumberPtr { return this->to_number; }
auto PhoneCallData::getStartCall() const -> const DatePtr { return this->start_call; }
auto PhoneCallData::getEndCall() const -> const DatePtr { return this->end_call; }
auto PhoneCallData::getCallType() const -> const std::optional<CallType> { return this->call_type; }
auto PhoneCallData::getCallCreator() const -> const PersonPtr { return this->call_creator; }
auto PhoneCallData::getCallProvider() const -> const std::string& { return this->call_provider; }

bool PhoneCallData::setFromNumber(const PhoneNumberPtr& number, const InternalEmployeePtr& changer)
{
    if (this->from_number != number) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->from_number),
            PTR_TO_OPTIONAL(number),
            PhoneCallFields::FromNumber,
            this->from_number ? ChangeLog::FieldType::PhoneNumber : ChangeLog::FieldType::null,
            number ? ChangeLog::FieldType::PhoneNumber : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->from_number = number;
        return true;
    }
    return false;
}

bool PhoneCallData::setToNumber(const PhoneNumberPtr& number, const InternalEmployeePtr& changer)
{
    if (this->to_number != number) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->to_number),
            PTR_TO_OPTIONAL(number),
            PhoneCallFields::ToNumber,
            this->to_number ? ChangeLog::FieldType::PhoneNumber : ChangeLog::FieldType::null,
            number ? ChangeLog::FieldType::PhoneNumber : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->to_number = number;
        return true;
    }
    return false;
}

bool PhoneCallData::setStartCall(const DatePtr& start, const InternalEmployeePtr& changer)
{
    if (this->start_call == nullptr || start == nullptr) {
        if (this->start_call == start) {
            return false;
        }
    } else if (*this->start_call == *start) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->start_call),
        PTR_TO_OPTIONAL(start),
        PhoneCallFields::StartCall,
        this->start_call ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        start ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->start_call = start;
    return true;
}

bool PhoneCallData::setEndCall(const DatePtr& end, const InternalEmployeePtr& changer)
{
    if (this->end_call == nullptr || end == nullptr) {
        if (this->end_call == end) {
            return false;
        }
    } else if (*this->end_call == *end) {
        return false;
    }

    this->change_logs.emplace_back(std::make_shared<ChangeLog>(
        changer,
        PTR_TO_OPTIONAL(this->end_call),
        PTR_TO_OPTIONAL(end),
        PhoneCallFields::EndCall,
        this->end_call ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        end ? ChangeLog::FieldType::Date : ChangeLog::FieldType::null,
        ChangeLog::Action::Change
    ));
    this->end_call = end;
    return true;
}

bool PhoneCallData::setCallType(
    const std::optional<CallType>& type, const InternalEmployeePtr& changer
)
{
    if (this->call_type != type) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->call_type ? std::make_optional<ChangeLog::ValueVariant>(this->call_type.value())
                            : std::nullopt,
            type ? std::make_optional<ChangeLog::ValueVariant>(type.value()) : std::nullopt,
            PhoneCallFields::CallType,
            this->call_type ? ChangeLog::FieldType::CallType : ChangeLog::FieldType::null,
            type ? ChangeLog::FieldType::CallType : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->call_type = type;
        return true;
    }
    return false;
}

bool PhoneCallData::setCallCreator(const PersonPtr& creator, const InternalEmployeePtr& changer)
{
    if (this->call_creator != creator) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            PTR_TO_OPTIONAL(this->call_creator),
            PTR_TO_OPTIONAL(creator),
            PhoneCallFields::CallCreator,
            this->call_creator ? ChangeLog::FieldType::Person : ChangeLog::FieldType::null,
            creator ? ChangeLog::FieldType::Person : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->call_creator = creator;
        return true;
    }
    return false;
}

bool PhoneCallData::setCallProvider(const std::string& provider, const InternalEmployeePtr& changer)
{
    if (this->call_provider != provider) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::string>(this->call_provider)
            ),
            std::make_optional<ChangeLog::ValueVariant>(std::make_shared<std::string>(provider)),
            PhoneCallFields::CallProvider,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Change
        ));
        this->call_provider = provider;
        return true;
    }
    return false;
}