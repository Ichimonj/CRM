#include "report.hpp"

#include "ChangeLog/change_log.hpp"

Report::Report(
    const BigUint&                 id,
    const ReportType&              type,
    const OptionalStr&             other_type,
    std::vector<std::string>       data,
    const DatePtr&                 generated_date,
    const std::vector<StringPair>& parameters,
    const WeakInternalEmployee&    creator,
    const ExportFormat&            export_format
)
    : id(id)
    , type(type)
    , other_type(other_type)
    , data(std::move(data))
    , generated_date(generated_date)
    , parameters(parameters)
    , creator(creator)
    , export_format(export_format)
{
}

auto Report::getId() const -> const BigUint& { return this->id; }

auto Report::getType() const -> ReportType { return this->type; }

auto Report::getOtherType() const -> const OptionalStr& { return this->other_type; }

auto Report::getData() const -> const std::vector<std::string>& { return this->data; }

auto Report::getGeneratedDate() const -> const DatePtr& { return this->generated_date; }

auto Report::getParameters() const -> const std::vector<StringPair>& { return this->parameters; }

auto Report::getCreator() const -> const WeakInternalEmployee& { return this->creator; }

auto Report::getExportFormat() const -> ExportFormat { return this->export_format; }

bool Report::setType(ReportType type, const InternalEmployeePtr& changer)
{
    if (this->type != type) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_type
                ? std::make_optional(std::make_shared<std::string>(this->other_type.value()))
                : std::make_optional<ChangeLog::ValueVariant>(this->type),
            std::make_optional(type),
            ReportFields::Type,
            this->other_type ? ChangeLog::FieldType::String : ChangeLog::FieldType::ReportType,
            ChangeLog::FieldType::ReportType,
            ChangeLog::Action::Change
        ));
        this->type       = type;
        this->other_type = std::nullopt;
        return true;
    }
    return false;
}

bool Report::setOtherType(const OptionalStr& other_type, const InternalEmployeePtr& changer)
{
    if (this->other_type != other_type) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            this->other_type
                ? std::make_optional(std::make_shared<std::string>(this->other_type.value()))
                : std::make_optional<ChangeLog::ValueVariant>(this->type),
            OPTIONAL_STR_TO_VALUE(other_type),
            ReportFields::Type,
            this->other_type ? ChangeLog::FieldType::String : ChangeLog::FieldType::ReportType,
            other_type ? ChangeLog::FieldType::String : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->other_type = other_type;
        this->type       = ReportType::other;
        return true;
    }
    return false;
}

bool Report::addData(const std::string& data, const InternalEmployeePtr& changer)
{
    if (std::find(this->data.begin(), this->data.end(), data) == this->data.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional(std::make_shared<std::string>(data)),
            ReportFields::Data,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::String,
            ChangeLog::Action::Add
        ));
        this->data.push_back(data);
        return true;
    }
    return false;
}

bool Report::delData(size_t index, const InternalEmployeePtr& changer)
{
    if (this->data.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(std::make_shared<std::string>(this->data[index])),
            std::nullopt,
            ReportFields::Data,
            ChangeLog::FieldType::String,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->data.erase(this->data.begin() + index);
        return true;
    }
    return false;
}

bool Report::addParameter(const StringPair& parameter, const InternalEmployeePtr& changer)
{
    if (std::find(this->parameters.begin(), this->parameters.end(), parameter) ==
        this->parameters.end()) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::nullopt,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::pair<const std::string, const std::string>>(parameter)
            ),
            ReportFields::Parameters,
            ChangeLog::FieldType::null,
            ChangeLog::FieldType::StringPair,
            ChangeLog::Action::Add
        ));
        this->parameters.push_back(parameter);
        return true;
    }
    return false;
}

bool Report::delParameter(size_t index, const InternalEmployeePtr& changer)
{
    if (this->parameters.size() > index) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional<ChangeLog::ValueVariant>(
                std::make_shared<std::pair<const std::string, const std::string>>(
                    this->parameters[index]
                )
            ),
            std::nullopt,
            ReportFields::Parameters,
            ChangeLog::FieldType::StringPair,
            ChangeLog::FieldType::null,
            ChangeLog::Action::Remove
        ));
        this->parameters.erase(this->parameters.begin() + index);
        return true;
    }
    return false;
}

bool Report::setCreator(const WeakInternalEmployee& creator, const InternalEmployeePtr& changer)
{
    if (this->creator.owner_before(creator) || creator.owner_before(this->creator)) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            WEAK_PTR_TO_OPTIONAL(this->creator),
            WEAK_PTR_TO_OPTIONAL(creator),
            ReportFields::Creator,
            this->creator.lock() ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            creator.lock() ? ChangeLog::FieldType::InternalEmployee : ChangeLog::FieldType::null,
            ChangeLog::Action::Change
        ));
        this->creator = creator;
        return true;
    }
    return false;
}

bool Report::setExportFormat(ExportFormat export_format, const InternalEmployeePtr& changer)
{
    if (this->export_format != export_format) {
        this->change_logs.emplace_back(std::make_shared<ChangeLog>(
            changer,
            std::make_optional(this->export_format),
            std::make_optional(export_format),
            ReportFields::ExportFormat,
            ChangeLog::FieldType::ExportFormat,
            ChangeLog::FieldType::ExportFormat,
            ChangeLog::Action::Change
        ));
        this->export_format = export_format;
        return true;
    }
    return false;
}