#pragma once
#pragma once
#include <memory>
#include <string>
#include <variant>

#include "BigNum/money.hpp"
#include "Campaign/campaign.hpp"
#include "Campaign/campaign_lead.hpp"
#include "Case/case.hpp"
#include "ChangeLog/fields_enums.hpp"
#include "Company/ExternalCompany/external_company.hpp"
#include "Currencies/currencies.hpp"
#include "DateTime/date.hpp"
#include "Deal/deal.hpp"
#include "Document/document.hpp"
#include "Interaction/email_letter.hpp"
#include "Interaction/meeting.hpp"
#include "Interaction/phone_call_data.hpp"
#include "Note/note.hpp"
#include "Offering/offer_deal.hpp"
#include "Offering/offering.hpp"
#include "Payment/payment.hpp"
#include "Person/Client/client.hpp"
#include "Person/Employee/employee_enums.hpp"
#include "Person/Employee/external_employee.hpp"
#include "Person/Employee/internal_employee.hpp"
#include "Report/report.hpp"
#include "SocialNetwork/social_network.hpp"
#include "Task/task.hpp"

/**
 * @struct ChangeLog
 * @brief A structure that represents a single entry in the change log, capturing modifications to
 * fields in interactions or related entities.
 *
 * This structure logs changes such as additions, removals, or modifications to various fields,
 * including their types, old and new values, and the employee responsible for the change.
 */
class ChangeLog {
public:
    enum class FieldType : uint8_t {
        Int,
        Uint,
        Double,
        String,
        PhoneNumber,
        Date,
        Person,
        CallType,
        Meeting,
        Client,
        InternalEmployee,
        ExternalEmployee,
        Bool,
        MeetingStatus,
        MeetingType,
        MeetingOutcome,
        Document,
        Deal,
        BaseInteraction,
        FileMetadata,
        Campaign,
        CampaignLead,
        StringPair,
        PersonMoneyPair,
        ResultStatus,
        EmailLetter,
        EmailStatus,
        EmailLetterType,
        Message,
        CommentarySocialNetworks,
        TimeDuration,
        InteractionResult,
        InteractionType,
        Address,
        Priority,
        Currencies,
        Payment,
        DealStatus,
        Offer,
        OfferDeal,
        DocumentStatus,
        Task,
        TaskStatus,
        Gender,
        Note,
        Money,
        AccessLevel,
        EmployeeStatus,
        ClientType,
        LeadStatus,
        LeadSource,
        Company,
        CompanyType,
        CompanyRating,
        CompanyRiskLevel,
        SocialNetwork,
        TaxInfo,
        CompanyStatus,
        CompanySize,
        ComplianceLevel,
        InfluenceLevel,
        IntegrationStatus,
        PaymentStatus,
        ReportType,
        ExportFormat,
        CampaignType,
        CaseStatus,
        null
    };

    using FieldVariant = std::variant<
        BaseInteractionFields,
        CommentarySocialNetworksFields,
        CommentarySocialNetworksThreadFields,
        CorrespondenceFields,
        EmailLetterFields,
        EmailThreadFields,
        InteractionResultFields,
        MeetingFields,
        MeetingThreadFields,
        MessageFields,
        PhoneCallFields,
        DocumentFields,
        FileMetadataFields,
        DealFields,
        TaskFields,
        PersonFields,
        InternalEmployeeFields,
        ClientFields,
        CompanyFields,
        ExternalCompanyFields,
        ExternalEmployeeFields,
        PaymentFields,
        ReportFields,
        CampaignFields,
        CaseField>;

    enum class Action : uint8_t { Add, Remove, Change };
    using ValueVariant = std::variant<
        double,
        bool,
        int,
        uint32_t,
        std::shared_ptr<PhoneNumber>,
        std::shared_ptr<Date>,
        std::shared_ptr<Person>,
        std::shared_ptr<Client>,
        std::shared_ptr<Meeting>,
        std::shared_ptr<InternalEmployee>,
        std::shared_ptr<ExternalEmployee>,
        std::shared_ptr<Address>,
        std::shared_ptr<Document>,
        std::shared_ptr<Deal>,
        std::shared_ptr<BaseInteraction>,
        std::shared_ptr<FileMetadata>,
        std::shared_ptr<std::pair<const std::string, const std::string>>,
        std::shared_ptr<EmailLetter>,
        std::shared_ptr<Message>,
        std::shared_ptr<CommentarySocialNetworks>,
        std::shared_ptr<TimeDuration>,
        std::shared_ptr<InteractionResult>,
        std::shared_ptr<Note>,
        std::shared_ptr<std::pair<std::shared_ptr<Person>, Money>>,
        std::shared_ptr<Payment>,
        std::shared_ptr<Offer>,
        std::shared_ptr<OfferDeal>,
        std::shared_ptr<Task>,
        std::shared_ptr<SocialNetwork>,
        std::shared_ptr<TaxInfo>,
        std::shared_ptr<Money>,
        std::shared_ptr<Company>,
        std::shared_ptr<Campaign>,
        std::shared_ptr<CampaignLead>,
        StringPtr,
        PhoneCallData::CallType,
        Meeting::MeetingStatus,
        Meeting::MeetingType,
        Meeting::MeetingOutcome,
        InteractionResult::ResultStatus,
        EmailLetter::EmailStatus,
        EmailLetter::EmailLetterType,
        BaseInteraction::InteractionType,
        Priority,
        Currencies,
        Deal::Status,
        Document::DocumentStatus,
        Task::Status,
        Gender,
        EmployeeStatus,
        AccessRole,
        Client::ClientType,
        Client::LeadStatus,
        Client::LeadSource,
        Company::CompanyStatus,
        ExternalCompany::CompanyType,
        ExternalCompany::Rating,
        ExternalCompany::RiskLevel,
        ExternalCompany::CompanySize,
        ExternalCompany::ComplianceLevel,
        ExternalEmployee::InfluenceLevel,
        ExternalCompany::IntegrationStatus,
        PaymentStatus,
        ReportType,
        ExportFormat,
        CampaignType,
        CaseStatus>;

    ChangeLog(
        const std::weak_ptr<InternalEmployee>& changer,
        const std::optional<ValueVariant>&     old_value,
        const std::optional<ValueVariant>&     new_value,
        FieldVariant                           field,
        FieldType                              old_field_type,
        FieldType                              new_field_type,
        Action                                 action,
        Date                                   change_date = Date()
    );

    virtual ~ChangeLog();

    /// @name New/Old value to str
    /// @{
    StringPtr valueToStr(FieldType type, ValueVariant value, StringPtr& str);
    StringPtr getOldValueStr();
    StringPtr getNewValueStr();
    /// @}

    /// @name Getters
    /// @{
    auto getChanger() const -> std::weak_ptr<InternalEmployee>;
    auto getChangeDate() const -> const Date&;
    auto getOldValue() const -> const std::optional<ValueVariant>&;
    auto getNewValue() const -> const std::optional<ValueVariant>&;
    auto getField() const -> const FieldVariant;
    auto getOldValueFieldType() const -> FieldType;
    auto getNewValueFieldType() const -> FieldType;
    auto getAction() const -> Action;
    /// @}

private:
    std::weak_ptr<InternalEmployee> changer;
    Date                            change_date;
    StringPtr                       old_value_str;
    StringPtr                       new_value_str;

    std::optional<ValueVariant>     old_value;
    std::optional<ValueVariant>     new_value;
    FieldVariant                    field;

    FieldType                       old_field_type;
    FieldType                       new_field_type;
    Action                          action;

public:
    /// @name Enums value to str
    /// @{
    static std::string callTypeToStr(PhoneCallData::CallType type);
    static std::string meetingStatusToStr(Meeting::MeetingStatus status);
    static std::string meetingTypeToStr(Meeting::MeetingType type);
    static std::string meetingOutcomeToStr(Meeting::MeetingOutcome outcome);
    static std::string interactionResultStatusToStr(InteractionResult::ResultStatus restultStatus);
    static std::string emailStatusToStr(EmailLetter::EmailStatus status);
    static std::string emailLetterTypeToStr(EmailLetter::EmailLetterType type);
    static std::string interactionTypeToStr(BaseInteraction::InteractionType type);
    static std::string paymentStatusToStr(PaymentStatus status);
    static std::string dealStatusToStr(Deal::Status status);
    static std::string documentStatusToStr(Document::DocumentStatus status);
    static std::string taskStatusToStr(Task::Status status);
    static std::string genderToStr(Gender gender);
    static std::string employeeStatusToStr(EmployeeStatus status);
    static std::string accessLevelStr(AccessRole level);
    static std::string clientTypeToStr(Client::ClientType type);
    static std::string leadStatusToStr(Client::LeadStatus status);
    static std::string leadSourceToStr(Client::LeadSource source);
    static std::string companyTypeToStr(ExternalCompany::CompanyType type);
    static std::string companyRatingToStr(ExternalCompany::Rating rating);
    static std::string companyRiskLevelToStr(ExternalCompany::RiskLevel risk_level);
    static std::string companyStatusToStr(Company::CompanyStatus status);
    static std::string companySizeToStr(ExternalCompany::CompanySize size);
    static std::string companyComplianceLevelToStr(ExternalCompany::ComplianceLevel level);
    static std::string influenceLevelToStr(ExternalEmployee::InfluenceLevel level);
    static std::string integrationStatusToStr(ExternalCompany::IntegrationStatus status);
    static std::string reportTypeToStr(ReportType type);
    static std::string exportFormatToStr(ExportFormat format);
    static std::string campaignTypeToStr(CampaignType type);
    static std::string caseStatusToStr(CaseStatus status);
    /// @}
};

#define PTR_TO_OPTIONAL(ptr) \
    (ptr == nullptr ? std::nullopt : std::make_optional<ChangeLog::ValueVariant>(ptr))

#define OPTIONAL_STR_TO_VALUE(STR)      \
    (STR == std::nullopt ? std::nullopt \
                         : std::make_optional(std::make_shared<std::string>(STR.value())))