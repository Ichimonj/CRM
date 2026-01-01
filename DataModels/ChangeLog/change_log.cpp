#include "change_log.hpp"

#include <format>
#include <string>

#include "FileMetadata/file_metadata.hpp"
#include "Interaction/base_interaction.hpp"
#include "Interaction/commentary_social_networks.hpp"
#include "Interaction/message.hpp"
#include "Person/Client/client.hpp"
#include "Person/Employee/internal_employee.hpp"
#include "location.hpp"
#include "Payment/payment.hpp"
#include "UserSession/session_manager.hpp"
#include "DateTime/time_duration.hpp"
ChangeLog::ChangeLog(
    std::shared_ptr<InternalEmployee> changer,
    std::optional<ValueVariant>       old_value,
    std::optional<ValueVariant>       new_value,
    FieldVariant                      field,
    FieldType                         old_field_type,
    FieldType                         new_field_type,
    Action                            action,
    Date                              change_date
)
    : changer(changer)
    , change_date(change_date)
    , old_value(old_value)
    , new_value(new_value)
    , field(field)
    , old_field_type(old_field_type)
    , new_field_type(new_field_type)
    , action(action)
{
    SessionManager::getInstance().addChangeToSession(this);
}

ChangeLog::~ChangeLog() {}

StringPtr ChangeLog::valueToStr(FieldType type, ValueVariant value, StringPtr& str)
{
    switch (type) {
        case FieldType::Int: {
            str = std::make_shared<std::string>(std::to_string(std::get<int>(value)));
            return str;
        }
        case FieldType::Uint: {
            str = std::make_shared<std::string>(std::to_string(std::get<uint32_t>(value)));
            return str;
        }
        case FieldType::Double: {
            str = std::make_shared<std::string>(std::format("{}", std::get<double>(value)));
            return str;
        }
        case FieldType::String: {
            str = std::get<StringPtr>(value);
            return str;
        }
        case FieldType::PhoneNumber: {
            str = std::make_shared<std::string>(
                std::get<std::shared_ptr<PhoneNumber>>(value)->getNumber()
            );
            return str;
        }
        case FieldType::Date: {
            str =
                std::make_shared<std::string>(std::get<std::shared_ptr<Date>>(value)->getDateStr());
            return str;
        }
        case FieldType::Person: {
            auto& person = std::get<std::shared_ptr<Person>>(value);
            str = std::make_shared<std::string>(person->getName() + ' ' + person->getSurname());
            return str;
        }
        case FieldType::CallType: {
            str = std::make_shared<std::string>(
                this->callTypeToStr(std::get<PhoneCallData::CallType>(value))
            );
            return str;
        }
        case FieldType::Meeting: {
            str = std::make_shared<std::string>(std::get<std::shared_ptr<Meeting>>(value)->getTitle(
            ));
            return str;
        }
        case FieldType::Client: {
            auto& client = std::get<std::shared_ptr<Client>>(value);
            str = std::make_shared<std::string>(client->getName() + ' ' + client->getSurname());
            return str;
        }
        case FieldType::InternalEmployee: {
            auto& employee = std::get<std::shared_ptr<InternalEmployee>>(value);
            str = std::make_shared<std::string>(employee->getName() + ' ' + employee->getSurname());
            return str;
        }
        case FieldType::ExternalEmployee: {
            auto& employee = std::get<std::shared_ptr<ExternalEmployee>>(value);
            str = std::make_shared<std::string>(employee->getName() + ' ' + employee->getSurname());
            return str;
        }
        case FieldType::Bool: {
            str = std::get<bool>(value) ? std::make_shared<std::string>("True")
                                        : std::make_shared<std::string>("False");
            return str;
        }
        case FieldType::MeetingStatus: {
            str = std::make_shared<std::string>(
                meetingStatusToStr(std::get<Meeting::MeetingStatus>(value))
            );
            return str;
        }
        case FieldType::MeetingType: {
            str =
                std::make_shared<std::string>(meetingTypeToStr(std::get<Meeting::MeetingType>(value)
                ));
            return str;
        }
        case FieldType::MeetingOutcome: {
            str = std::make_shared<std::string>(
                meetingOutcomeToStr(std::get<Meeting::MeetingOutcome>(value))
            );
            return str;
        }
        case FieldType::Document: {
            str =
                std::make_shared<std::string>(std::get<std::shared_ptr<Document>>(value)->getTitle()
                );
            return str;
        }
        case FieldType::Deal: {
            str = std::make_shared<std::string>(std::get<std::shared_ptr<Deal>>(value)->getTitle());
            return str;
        }
        case FieldType::BaseInteraction: {
            str = std::make_shared<std::string>(
                std::get<std::shared_ptr<BaseInteraction>>(value)->getTitle()
            );
            return str;
        }
        case FieldType::FileMetadata: {
            str = std::make_shared<std::string>(
                std::get<std::shared_ptr<FileMetadata>>(value)->getFileName()
            );
            return str;
        }
        case FieldType::Campaign: {
            str = std::make_shared<std::string>(std::get<std::shared_ptr<Campaign>>(value)->getName(
            ));
            return str;
        }
        case FieldType::CampaignLead: {
            auto lead = std::get<std::shared_ptr<CampaignLead>>(value)->getLead();
            str       = std::make_shared<std::string>(lead->getName() + ' ' + lead->getSurname());
            return str;
        }
        case FieldType::StringPair: {
            auto& pair =
                std::get<std::shared_ptr<std::pair<const std::string, const std::string>>>(value);
            str = std::make_shared<std::string>(pair->first + ' ' + pair->second);
            return str;
        }
        case FieldType::PersonMoneyPair: {
            auto& pair =
                std::get<std::shared_ptr<std::pair<std::shared_ptr<Person>, Money>>>(value);
            str = std::make_shared<std::string>(
                pair->first->getName() + ' ' + pair->first->getSurname() + " - " + pair->second.num
            );
            return str;
        }
        case FieldType::ResultStatus: {
            str = std::make_shared<std::string>(
                interactionResultStatusToStr(std::get<InteractionResult::ResultStatus>(value))
            );
            return str;
        }
        case FieldType::EmailLetter: {
            str = std::make_shared<std::string>(
                std::get<std::shared_ptr<EmailLetter>>(value)->getTitle()
            );
            return str;
        }
        case FieldType::EmailStatus: {
            str = std::make_shared<std::string>(
                emailStatusToStr(std::get<EmailLetter::EmailStatus>(value))
            );
            return str;
        }
        case FieldType::EmailLetterType: {
            str = std::make_shared<std::string>(
                emailLetterTypeToStr(std::get<EmailLetter::EmailLetterType>(value))
            );
            return str;
        }
        case FieldType::Message: {
            str = std::make_shared<std::string>(
                std::get<std::shared_ptr<Message>>(value)->getMessage()
            );
            return str;
        }
        case FieldType::CommentarySocialNetworks: {
            str = std::make_shared<std::string>(
                std::get<std::shared_ptr<CommentarySocialNetworks>>(value)->getTitle()
            );
            return str;
        }
        case FieldType::TimeDuration: {
            str = std::make_shared<std::string>(
                std::get<std::shared_ptr<TimeDuration>>(value)->getDurationStr()
            );
            return str;
        }
        case FieldType::InteractionResult: {
            str = std::make_shared<std::string>(
                std::get<std::shared_ptr<InteractionResult>>(value)->getTitle()
            );
            return str;
        }
        case FieldType::Note: {
            str = std::make_shared<std::string>(std::get<std::shared_ptr<Note>>(value)->getTitle());
            return str;
        }
        case FieldType::InteractionType: {
            str = std::make_shared<std::string>(
                interactionTypeToStr(std::get<BaseInteraction::InteractionType>(value))
            );
            return str;
        }
        case FieldType::Address: {
            auto& address = std::get<std::shared_ptr<Address>>(value);
            str           = std::make_shared<std::string>(
                address->getCountry() + ' ' + address->getCity() + ' ' + address->getStreet() +
                ' ' + address->getHouse()
            );
            return str;
        }
        case FieldType::Priority: {
            str = std::make_shared<std::string>(priorityToStr(std::get<Priority>(value)));
            return str;
        }
        case FieldType::Currencies: {
            str = std::make_shared<std::string>(currencyToString(std::get<Currencies>(value)));
            return str;
        }
        case FieldType::Payment: {
            auto&       payment = std::get<std::shared_ptr<Payment>>(value);

            std::string amount;

            if (payment->getReceivedDate() != nullptr)
                amount = payment->getRequestedAmount()->num;
            else if (payment->getSendingAmount() != nullptr)
                amount = payment->getSendingAmount()->num;
            else
                amount = "NULL";

            str = std::make_shared<std::string>(
                amount + ' ' + currencyToString(payment->getCurrency()) + ' ' +
                paymentStatusToStr(payment->getPaymentStatus())
            );
            return str;
        }
        case FieldType::DealStatus: {
            str = std::make_shared<std::string>(dealStatusToStr(std::get<Deal::Status>(value)));
            return str;
        }
        case FieldType::Offer: {
            str = std::make_shared<std::string>(std::get<std::shared_ptr<Offer>>(value)->getName());
            return str;
        }
        case FieldType::DocumentStatus: {
            str = std::make_shared<std::string>(
                documentStatusToStr(std::get<Document::DocumentStatus>(value))
            );
            return str;
        }
        case FieldType::Task: {
            str = std::make_shared<std::string>(std::get<std::shared_ptr<Task>>(value)->getTitle());
            return str;
        }
        case FieldType::TaskStatus: {
            str = std::make_shared<std::string>(taskStatusToStr(std::get<Task::Status>(value)));
            return str;
        }
        case FieldType::Gender: {
            str = std::make_shared<std::string>(genderToStr(std::get<Gender>(value)));
            return str;
        }
        case FieldType::Money: {
            auto money = std::get<std::shared_ptr<Money>>(value);
            str =
                std::make_shared<std::string>(money->num + ' ' + currencyToString(money->currency));
            return str;
        }
        case FieldType::AccessLevel: {
            str = std::make_shared<std::string>(accessLevelStr(std::get<AccessRole>(value)));
            return str;
        }
        case FieldType::EmployeeStatus: {
            str =
                std::make_shared<std::string>(employeeStatusToStr(std::get<EmployeeStatus>(value)));
            return str;
        }
        case FieldType::ClientType: {
            str =
                std::make_shared<std::string>(clientTypeToStr(std::get<Client::ClientType>(value)));
            return str;
        }
        case FieldType::LeadStatus: {
            str =
                std::make_shared<std::string>(leadStatusToStr(std::get<Client::LeadStatus>(value)));
            return str;
        }
        case FieldType::LeadSource: {
            str =
                std::make_shared<std::string>(leadSourceToStr(std::get<Client::LeadSource>(value)));
            return str;
        }
        case FieldType::Company: {
            str = std::make_shared<std::string>(
                std::get<std::shared_ptr<Company>>(value)->getCompanyName()
            );
            return str;
        }
        case FieldType::CompanyType: {
            str = std::make_shared<std::string>(
                companyTypeToStr(std::get<ExternalCompany::CompanyType>(value))
            );
            return str;
        }
        case FieldType::CompanyRating: {
            str = std::make_shared<std::string>(
                companyRatingToStr(std::get<ExternalCompany::Rating>(value))
            );
            return str;
        }
        case FieldType::CompanyRiskLevel: {
            str = std::make_shared<std::string>(
                companyRiskLevelToStr(std::get<ExternalCompany::RiskLevel>(value))
            );
            return str;
        }
        case FieldType::SocialNetwork: {
            str =
                std::make_shared<std::string>(std::get<std::shared_ptr<SocialNetwork>>(value)->name
                );
            return str;
        }
        case FieldType::TaxInfo: {
            auto tax = std::get<std::shared_ptr<TaxInfo>>(value);
            str      = std::make_shared<std::string>(tax->code + ' ' + std::to_string(tax->rate));
        }
        case FieldType::CompanyStatus: {
            str = std::make_shared<std::string>(
                companyStatusToStr(std::get<Company::CompanyStatus>(value))
            );
            return str;
        }
        case FieldType::CompanySize: {
            str = std::make_shared<std::string>(
                companySizeToStr(std::get<ExternalCompany::CompanySize>(value))
            );
            return str;
        }
        case FieldType::ComplianceLevel: {
            str = std::make_shared<std::string>(
                companyComplianceLevelToStr(std::get<ExternalCompany::ComplianceLevel>(value))
            );
            return str;
        }
        case FieldType::InfluenceLevel: {
            str = std::make_shared<std::string>(
                influenceLevelToStr(std::get<ExternalEmployee::InfluenceLevel>(value))
            );
            return str;
        }
        case FieldType::IntegrationStatus: {
            str = std::make_shared<std::string>(
                integrationStatusToStr(std::get<ExternalCompany::IntegrationStatus>(value))
            );
            return str;
        }
        case FieldType::ReportType: {
            str = std::make_shared<std::string>(reportTypeToStr(std::get<ReportType>(value)));
            return str;
        }
        case FieldType::ExportFormat: {
            str = std::make_shared<std::string>(exportFormatToStr(std::get<ExportFormat>(value)));
            return str;
        }
        case FieldType::CampaignType: {
            str = std::make_shared<std::string>(campaignTypeToStr(std::get<CampaignType>(value)));
            return str;
        }
        case FieldType::CaseStatus: {
            str = std::make_shared<std::string>(caseStatusToStr(std::get<CaseStatus>(value)));
            return str;
        }
    }
    return nullptr;
}

StringPtr ChangeLog::getOldValueStr()
{
    if (this->old_value_str != nullptr) return old_value_str;
    if (this->old_value == std::nullopt || this->old_field_type == FieldType::null) return nullptr;

    return valueToStr(old_field_type, old_value.value(), old_value_str);
}

StringPtr ChangeLog::getNewValueStr()
{
    if (this->new_value_str != nullptr) return new_value_str;
    if (this->new_value == std::nullopt || this->new_field_type == FieldType::null) return nullptr;

    return valueToStr(new_field_type, new_value.value(), new_value_str);
}

auto ChangeLog::getChanger() const -> const std::shared_ptr<InternalEmployee>
{
    return this->changer;
}
auto ChangeLog::getChangeDate() const -> const Date& { return this->change_date; }
auto ChangeLog::getOldValue() const -> const std::optional<ValueVariant>&
{
    return this->old_value;
}
auto ChangeLog::getNewValue() const -> const std::optional<ValueVariant>&
{
    return this->new_value;
}
auto        ChangeLog::getField() const -> const FieldVariant { return this->field; }
auto        ChangeLog::getOldValueFieldType() const -> FieldType { return this->old_field_type; }
auto        ChangeLog::getNewValueFieldType() const -> FieldType { return this->new_field_type; }
auto        ChangeLog::getAction() const -> Action { return this->action; }

std::string ChangeLog::callTypeToStr(PhoneCallData::CallType type)
{
    switch (type) {
        case PhoneCallData::CallType::incoming:
            return call_type_str::incoming;
        case PhoneCallData::CallType::missed:
            return call_type_str::missed;
        case PhoneCallData::CallType::outgoing:
            return call_type_str::outgoing;
    }
    return std::string();
}

std::string ChangeLog::meetingStatusToStr(Meeting::MeetingStatus status)
{
    switch (status) {
        case Meeting::MeetingStatus::Canceled:
            return meeting_status_str::canceled;
        case Meeting::MeetingStatus::Completed:
            return meeting_status_str::completed;
        case Meeting::MeetingStatus::InProgress:
            return meeting_status_str::inProgress;
        case Meeting::MeetingStatus::Postponed:
            return meeting_status_str::postponed;
        case Meeting::MeetingStatus::Scheduled:
            return meeting_status_str::scheduled;
    }
    return std::string();
}

std::string ChangeLog::meetingTypeToStr(Meeting::MeetingType type)
{
    switch (type) {
        case Meeting::MeetingType::Negotiation:
            return meeting_type_str::negotiation;
        case Meeting::MeetingType::Presentation:
            return meeting_type_str::presentation;
        case Meeting::MeetingType::Training:
            return meeting_type_str::training;
        case Meeting::MeetingType::Other:
            return meeting_type_str::other;
    }
    return std::string();
}

std::string ChangeLog::meetingOutcomeToStr(Meeting::MeetingOutcome outcome)
{
    switch (outcome) {
        case Meeting::MeetingOutcome::ClosedWon:
            return meeting_outcome_str::closedWon;
        case Meeting::MeetingOutcome::ClosedLost:
            return meeting_outcome_str::closedLost;
        case Meeting::MeetingOutcome::ProgressMade:
            return meeting_outcome_str::progressMade;
        case Meeting::MeetingOutcome::FollowUpScheduled:
            return meeting_outcome_str::followUpScheduled;
        case Meeting::MeetingOutcome::InformationProvided:
            return meeting_outcome_str::informationProvided;
        case Meeting::MeetingOutcome::DecisionPending:
            return meeting_outcome_str::decisionPending;
        case Meeting::MeetingOutcome::AdditionalInfoNeeded:
            return meeting_outcome_str::additionalInfoNeeded;
        case Meeting::MeetingOutcome::Postponed:
            return meeting_outcome_str::postponed;
        case Meeting::MeetingOutcome::Canceled:
            return meeting_outcome_str::canceled;
        case Meeting::MeetingOutcome::Redirected:
            return meeting_outcome_str::redirected;
        case Meeting::MeetingOutcome::IssueIdentified:
            return meeting_outcome_str::issueIdentified;
        case Meeting::MeetingOutcome::Other:
            return meeting_outcome_str::other;
    }
    return std::string();
}

std::string ChangeLog::interactionResultStatusToStr(InteractionResult::ResultStatus restultStatus)
{
    switch (restultStatus) {
        case InteractionResult::ResultStatus::Canceled:
            return interaction_result_status_str::canceled;
        case InteractionResult::ResultStatus::Failure:
            return interaction_result_status_str::failure;
        case InteractionResult::ResultStatus::FollowUpNeeded:
            return interaction_result_status_str::followUpNeeded;
        case InteractionResult::ResultStatus::IssueIdentified:
            return interaction_result_status_str::issueIdentified;
        case InteractionResult::ResultStatus::NoOutcome:
            return interaction_result_status_str::noOutcome;
        case InteractionResult::ResultStatus::other:
            return interaction_result_status_str::other;
        case InteractionResult::ResultStatus::PartialSuccess:
            return interaction_result_status_str::partialSuccess;
        case InteractionResult::ResultStatus::Postponed:
            return interaction_result_status_str::postponed;
        case InteractionResult::ResultStatus::Success:
            return interaction_result_status_str::success;
    }
    return std::string();
}

std::string ChangeLog::emailStatusToStr(EmailLetter::EmailStatus status)
{
    switch (status) {
        case EmailLetter::EmailStatus::Delivered:
            return email_status_str::delivered;
        case EmailLetter::EmailStatus::Draft:
            return email_status_str::draft;
        case EmailLetter::EmailStatus::Failed:
            return email_status_str::failed;
        case EmailLetter::EmailStatus::Forwarded:
            return email_status_str::forwarded;
        case EmailLetter::EmailStatus::Replied:
            return email_status_str::replied;
        case EmailLetter::EmailStatus::Scheduled:
            return email_status_str::scheduled;
        case EmailLetter::EmailStatus::Sent:
            return email_status_str::sent;
    }
    return std::string();
}

std::string ChangeLog::emailLetterTypeToStr(EmailLetter::EmailLetterType type)
{
    switch (type) {
        case EmailLetter::EmailLetterType::incoming:
            return email_letter_type_str::incoming;
        case EmailLetter::EmailLetterType::outgoing:
            return email_letter_type_str::outgoing;
    }
    return std::string();
}

std::string ChangeLog::interactionTypeToStr(BaseInteraction::InteractionType type)
{
    switch (type) {
        case BaseInteraction::InteractionType::commentarySocialNetworks:
            return interaction_type_str::commentarySocialNetworks;
        case BaseInteraction::InteractionType::commentarySocialNetworksThread:
            return interaction_type_str::commentarySocialNetworksThread;
        case BaseInteraction::InteractionType::correspondence:
            return interaction_type_str::correspondence;
        case BaseInteraction::InteractionType::emailLetter:
            return interaction_type_str::emailLetter;
        case BaseInteraction::InteractionType::emailThread:
            return interaction_type_str::emailThread;
        case BaseInteraction::InteractionType::meeting:
            return interaction_type_str::meeting;
        case BaseInteraction::InteractionType::meetingThread:
            return interaction_type_str::meetingThread;
        case BaseInteraction::InteractionType::message:
            return interaction_type_str::message;
        case BaseInteraction::InteractionType::phoneCall:
            return interaction_type_str::phoneCall;
        case BaseInteraction::InteractionType::unknown:
            return interaction_type_str::unknown;
    }
    return std::string();
}

std::string ChangeLog::paymentStatusToStr(PaymentStatus status)
{
    switch (status) {
        case PaymentStatus::pending:
            return payment_status_str::pending;
        case PaymentStatus::completed:
            return payment_status_str::completed;
        case PaymentStatus::failed:
            return payment_status_str::failed;
        case PaymentStatus::refunded:
            return payment_status_str::refunded;
        case PaymentStatus::partial:
            return payment_status_str::partial;
        case PaymentStatus::overdue:
            return payment_status_str::overdue;
    }
    return std::string();
}

std::string ChangeLog::dealStatusToStr(Deal::Status status)
{
    switch (status) {
        case Deal::Status::Draft:
            return deal_status_str::draft;
        case Deal::Status::ReadyForCoordination:
            return deal_status_str::readyForCoordination;
        case Deal::Status::ReadyForSigned:
            return deal_status_str::readyForSigned;
        case Deal::Status::Coordination:
            return deal_status_str::coordination;
        case Deal::Status::SignedByCounterparty:
            return deal_status_str::signedByCounterparty;
        case Deal::Status::SignedBySecondSide:
            return deal_status_str::signedBySecondSide;
        case Deal::Status::AllSigned:
            return deal_status_str::allSigned;
        case Deal::Status::Deleted:
            return deal_status_str::deleted;
        case Deal::Status::Canceled:
            return deal_status_str::canceled;
        case Deal::Status::Registered:
            return deal_status_str::registered;
        case Deal::Status::BeginningDealBroken:
            return deal_status_str::beginningDealBroken;
        case Deal::Status::EndDealBroken:
            return deal_status_str::endDealBroken;
        case Deal::Status::ObligationsAreProcess:
            return deal_status_str::obligationsAreProcess;
        case Deal::Status::ObligationsAreFulfilled:
            return deal_status_str::obligationsAreFulfilled;
        case Deal::Status::ObligationsAreNotFulfilled:
            return deal_status_str::obligationsAreNotFulfilled;
        case Deal::Status::Other:
            return deal_status_str::other;
    }
    return std::string();
}

std::string ChangeLog::documentStatusToStr(Document::DocumentStatus status)
{
    switch (status) {
        case Document::DocumentStatus::Active:
            return document_status_str::active;
        case Document::DocumentStatus::Archived:
            return document_status_str::archived;
        case Document::DocumentStatus::Draft:
            return document_status_str::draft;
        case Document::DocumentStatus::Expired:
            return document_status_str::expired;
    }
    return std::string();
}

std::string ChangeLog::taskStatusToStr(Task::Status status)
{
    switch (status) {
        case Task::Status::NotStarted:
            return task_status_str::not_started;
        case Task::Status::Completed:
            return task_status_str::completed;
        case Task::Status::InProgress:
            return task_status_str::in_progress;
        case Task::Status::Overdue:
            return task_status_str::overdue;
    }
    return std::string();
}

std::string ChangeLog::genderToStr(Gender gender)
{
    switch (gender) {
        case Gender::female:
            return gender_str::female;
        case Gender::male:
            return gender_str::male;
        case Gender::unknown:
            return gender_str::unknown;
    }
    return std::string();
}

std::string ChangeLog::employeeStatusToStr(EmployeeStatus status)
{
    switch (status) {
        case EmployeeStatus::active:
            return employee_status_str::active;
        case EmployeeStatus::vacation:
            return employee_status_str::vacation;
        case EmployeeStatus::fired:
            return employee_status_str::fired;
        case EmployeeStatus::education:
            return employee_status_str::education;
        case EmployeeStatus::internship:
            return employee_status_str::internship;
        case EmployeeStatus::probation:
            return employee_status_str::probation;
        case EmployeeStatus::suspended:
            return employee_status_str::suspended;
        case EmployeeStatus::sick_leave:
            return employee_status_str::sick_leave;
        case EmployeeStatus::retired:
            return employee_status_str::retired;
        case EmployeeStatus::other:
            return employee_status_str::other;
    }
    return std::string();
}

std::string ChangeLog::accessLevelStr(AccessRole level)
{
    switch (level) {
        case AccessRole::Admin:
            return access_level_str::admin;
        case AccessRole::SalesRep:
            return access_level_str::sales_rep;
        case AccessRole::Executive:
            return access_level_str::executive;
        case AccessRole::Manager:
            return access_level_str::manager;
        case AccessRole::MarketingUser:
            return access_level_str::marketing_user;
        case AccessRole::ReadOnly:
            return access_level_str::read_only;
        case AccessRole::SalesManager:
            return access_level_str::sales_manager;
        case AccessRole::ServiceManager:
            return access_level_str::service_manager;
        case AccessRole::Support:
            return access_level_str::support;
        case AccessRole::DecisionMaker:
            return access_level_str::decision_maker;
        case AccessRole::Influencer:
            return access_level_str::influencer;
        case AccessRole::User:
            return access_level_str::user;
        case AccessRole::Gatekeeper:
            return access_level_str::gatekeeper;
        case AccessRole::other:
            return access_level_str::other;
    }
    return std::string();
}

std::string ChangeLog::clientTypeToStr(Client::ClientType type)
{
    switch (type) {
        case Client::ClientType::Visitor:
            return client_type_str::visitor;
        case Client::ClientType::Lead:
            return client_type_str::lead;
        case Client::ClientType::Prospect:
            return client_type_str::prospect;
        case Client::ClientType::Costomer:
            return client_type_str::customer;
        case Client::ClientType::LoyalCostomer:
            return client_type_str::loyal_customer;
        case Client::ClientType::Panter:
            return client_type_str::partner;
        case Client::ClientType::PetentialClient:
            return client_type_str::potential_client;
        case Client::ClientType::LostCostomer:
            return client_type_str::lost_customer;
        case Client::ClientType::Analytical:
            return client_type_str::analytical;
        case Client::ClientType::Emotional:
            return client_type_str::visitor;
        case Client::ClientType::other:
            return client_type_str::other;
    }
    return std::string();
}

std::string ChangeLog::leadStatusToStr(Client::LeadStatus status)
{
    switch (status) {
        case Client::LeadStatus::New:
            return lead_status_str::new_;
        case Client::LeadStatus::Open:
            return lead_status_str::open;
        case Client::LeadStatus::Working:
            return lead_status_str::working;
        case Client::LeadStatus::Qualified:
            return lead_status_str::qualified;
        case Client::LeadStatus::Unqualified:
            return lead_status_str::unqualified;
        case Client::LeadStatus::Converted:
            return lead_status_str::converted;
        case Client::LeadStatus::Closed:
            return lead_status_str::closed;
        case Client::LeadStatus::Disqualified:
            return lead_status_str::disqualified;
        case Client::LeadStatus::Nurturing:
            return lead_status_str::nurturing;
        case Client::LeadStatus::Lost:
            return lead_status_str::lost;
    }
    return std::string();
}

std::string ChangeLog::leadSourceToStr(Client::LeadSource source)
{
    switch (source) {
        case Client::LeadSource::Website:
            return lead_source_str::website;
        case Client::LeadSource::Referral:
            return lead_source_str::referral;
        case Client::LeadSource::EmailCampaing:
            return lead_source_str::email_campaign;
        case Client::LeadSource::SocialMedia:
            return lead_source_str::social_media;
        case Client::LeadSource::other:
            return lead_source_str::other;
    }
    return std::string();
}

std::string ChangeLog::companyTypeToStr(ExternalCompany::CompanyType type)
{
    switch (type) {
        case ExternalCompany::CompanyType::Client:
            return company_type_str::client;
        case ExternalCompany::CompanyType::Partner:
            return company_type_str::partner;
        case ExternalCompany::CompanyType::Vendor:
            return company_type_str::vendor;
        case ExternalCompany::CompanyType::Prospect:
            return company_type_str::prospect;
        case ExternalCompany::CompanyType::Supplier:
            return company_type_str::supplier;
        case ExternalCompany::CompanyType::Other:
            return company_type_str::other;
    }
    return std::string();
}

std::string ChangeLog::companyRatingToStr(ExternalCompany::Rating rating)
{
    switch (rating) {
        case ExternalCompany::Rating::Hot:
            return rating_str::hot;
        case ExternalCompany::Rating::Warm:
            return rating_str::warm;
        case ExternalCompany::Rating::Cold:
            return rating_str::cold;
        case ExternalCompany::Rating::Inactive:
            return rating_str::inactive;
    }
    return std::string();
}

std::string ChangeLog::companyRiskLevelToStr(ExternalCompany::RiskLevel risk_level)
{
    switch (risk_level) {
        case ExternalCompany::RiskLevel::Low:
            return risk_level_str::low;
        case ExternalCompany::RiskLevel::Medium:
            return risk_level_str::medium;
        case ExternalCompany::RiskLevel::High:
            return risk_level_str::high;
        case ExternalCompany::RiskLevel::Critical:
            return risk_level_str::critical;
    }
    return std::string();
}

std::string ChangeLog::companyStatusToStr(Company::CompanyStatus status)
{
    switch (status) {
        case Company::CompanyStatus::Active:
            return company_status_str::active;
        case Company::CompanyStatus::Archived:
            return company_status_str::archived;
        case Company::CompanyStatus::Inactive:
            return company_status_str::inactive;
    }
    return std::string();
}

std::string ChangeLog::companySizeToStr(ExternalCompany::CompanySize size)
{
    switch (size) {
        case ExternalCompany::CompanySize::Enterprise:
            return company_size_str::enterprise;
        case ExternalCompany::CompanySize::Large:
            return company_size_str::large;
        case ExternalCompany::CompanySize::Medium:
            return company_size_str::medium;
        case ExternalCompany::CompanySize::Micro:
            return company_size_str::micro;
        case ExternalCompany::CompanySize::Small:
            return company_size_str::small;
    }
    return std::string();
}

std::string ChangeLog::companyComplianceLevelToStr(ExternalCompany::ComplianceLevel level)
{
    switch (level) {
        case ExternalCompany::ComplianceLevel::Compliant:
            return compliance_level_str::compliant;
        case ExternalCompany::ComplianceLevel::NonCompliant:
            return compliance_level_str::non_compliant;
        case ExternalCompany::ComplianceLevel::Warning:
            return compliance_level_str::warning;
    }
    return std::string();
}

std::string ChangeLog::influenceLevelToStr(ExternalEmployee::InfluenceLevel level)
{
    switch (level) {
        case ExternalEmployee::InfluenceLevel::Critical:
            return influence_level_str::critical;
        case ExternalEmployee::InfluenceLevel::High:
            return influence_level_str::high;
        case ExternalEmployee::InfluenceLevel::Low:
            return influence_level_str::low;
        case ExternalEmployee::InfluenceLevel::Medium:
            return influence_level_str::medium;
        case ExternalEmployee::InfluenceLevel::VeryLow:
            return influence_level_str::very_low;
    }
    return std::string();
}

std::string ChangeLog::integrationStatusToStr(ExternalCompany::IntegrationStatus status)
{
    switch (status) {
        case ExternalCompany::IntegrationStatus::Connected:
            return integration_status_str::connected;
        case ExternalCompany::IntegrationStatus::Failed:
            return integration_status_str::failed;
        case ExternalCompany::IntegrationStatus::Pending:
            return integration_status_str::pending;
    }
    return std::string();
}

std::string ChangeLog::reportTypeToStr(ReportType type)
{
    switch (type) {
        case ReportType::SalesSummary:
            return report_type_str::SalesSummary;
        case ReportType::Pipeline:
            return report_type_str::Pipeline;
        case ReportType::RevenueByManager:
            return report_type_str::RevenueByManager;
        case ReportType::ClientActivity:
            return report_type_str::ClientActivity;
        case ReportType::ProductPerformance:
            return report_type_str::ProductPerformance;
        case ReportType::EmployeeKPI:
            return report_type_str::EmployeeKPI;
        case ReportType::InteractionSummary:
            return report_type_str::InteractionSummary;
        case ReportType::FinancialForecast:
            return report_type_str::FinancialForecast;
        case ReportType::other:
            return report_type_str::other;
    }
    return std::string();
}

std::string ChangeLog::exportFormatToStr(ExportFormat format)
{
    switch (format) {
        case ExportFormat::CSV:
            return export_format_str::CSV;
        case ExportFormat::PDF:
            return export_format_str::PDF;
        case ExportFormat::JSON:
            return export_format_str::JSON;
        case ExportFormat::XLSX:
            return export_format_str::XLSX;
    }
    return std::string();
}

std::string ChangeLog::campaignTypeToStr(CampaignType type)
{
    switch (type) {
        case CampaignType::Email:
            return campaign_type_str::email;
        case CampaignType::Event:
            return campaign_type_str::event;
        case CampaignType::SocialAds:
            return campaign_type_str::social_ads;
        case CampaignType::Webinar:
            return campaign_type_str::webinar;
        case CampaignType::other:
            return campaign_type_str::other;
    }
    return std::string();
}

std::string ChangeLog::caseStatusToStr(CaseStatus status)
{
    switch (status) {
        case CaseStatus::Open:
            return case_status_str::open;
        case CaseStatus::Closed:
            return case_status_str::closed;
        case CaseStatus::InProgress:
            return case_status_str::in_progress;
        case CaseStatus::Resolved:
            return case_status_str::resolved;
    }
    return std::string();
}
