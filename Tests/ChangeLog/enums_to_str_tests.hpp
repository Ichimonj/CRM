#include "ChangeLog/change_log.hpp"  
#include "gtest/gtest.h"
#include "Interaction/priority.hpp"
namespace unit {
    TEST(EnumToStrTests, PriorityTest)
    {
        for (size_t i = 0; i < (size_t)Priority::COUNT; i++) {
            Priority priority = (Priority)i;
            EXPECT_NE(priorityToStr(priority), std::string());
        }
    }
    TEST(EnumToStrTests, CallTypeTest)
    {
        for (size_t i = 0; i < (size_t)PhoneCallData::CallType::COUNT; i++) {
            PhoneCallData::CallType type = (PhoneCallData::CallType)i;
            EXPECT_NE(ChangeLog::callTypeToStr(type), std::string());
        }
    }

    TEST(EnumToStrTests, MeetingStatusTest)
    {
        for (size_t i = 0; i < (size_t)Meeting::MeetingStatus::COUNT; i++) {
            Meeting::MeetingStatus status = (Meeting::MeetingStatus)i;
            EXPECT_NE(ChangeLog::meetingStatusToStr(status), std::string());
        }
    }

    TEST(EnumToStrTests, MeetingTypeTest)
    {
        for (size_t i = 0; i < (size_t)Meeting::MeetingType::COUNT; i++) {
            Meeting::MeetingType type = (Meeting::MeetingType)i;
            EXPECT_NE(ChangeLog::meetingTypeToStr(type), std::string());
        }
    }

    TEST(EnumToStrTests, MeetingOutcomeTest)
    {
        for (size_t i = 0; i < (size_t)Meeting::MeetingOutcome::COUNT; i++) {
            Meeting::MeetingOutcome outcome = (Meeting::MeetingOutcome)i;
            EXPECT_NE(ChangeLog::meetingOutcomeToStr(outcome), std::string());
        }
    }

    TEST(EnumToStrTests, InteractionResultStatusTest)
    {
        for (size_t i = 0; i < (size_t)InteractionResult::ResultStatus::COUNT; i++) {
            InteractionResult::ResultStatus status = (InteractionResult::ResultStatus)i;
            EXPECT_NE(ChangeLog::interactionResultStatusToStr(status), std::string());
        }
    }

    TEST(EnumToStrTests, EmailStatusTest)
    {
        for (size_t i = 0; i < (size_t)EmailLetter::EmailStatus::COUNT; i++) {
            EmailLetter::EmailStatus status = (EmailLetter::EmailStatus)i;
            EXPECT_NE(ChangeLog::emailStatusToStr(status), std::string());
        }
    }

    TEST(EnumToStrTests, EmailLetterTypeTest)
    {
        for (size_t i = 0; i < (size_t)EmailLetter::EmailLetterType::COUNT; i++) {
            EmailLetter::EmailLetterType type = (EmailLetter::EmailLetterType)i;
            EXPECT_NE(ChangeLog::emailLetterTypeToStr(type), std::string());
        }
    }

    TEST(EnumToStrTests, InteractionTypeTest)
    {
        for (size_t i = 0; i < (size_t)BaseInteraction::InteractionType::COUNT; i++) {
            BaseInteraction::InteractionType type = (BaseInteraction::InteractionType)i;
            EXPECT_NE(ChangeLog::interactionTypeToStr(type), std::string());
        }
    }

    TEST(EnumToStrTests, PaymentStatusTest)
    {
        for (size_t i = 0; i < (size_t)PaymentStatus::COUNT; i++) {
            PaymentStatus status = (PaymentStatus)i;
            EXPECT_NE(ChangeLog::paymentStatusToStr(status), std::string());
        }
    }

    TEST(EnumToStrTests, DealStatusTest)
    {
        for (size_t i = 0; i < (size_t)Deal::Status::COUNT; i++) {
            Deal::Status status = (Deal::Status)i;
            EXPECT_NE(ChangeLog::dealStatusToStr(status), std::string());
        }
    }

    TEST(EnumToStrTests, DocumentStatusTest)
    {
        for (size_t i = 0; i < (size_t)Document::DocumentStatus::COUNT; i++) {
            Document::DocumentStatus status = (Document::DocumentStatus)i;
            EXPECT_NE(ChangeLog::documentStatusToStr(status), std::string());
        }
    }

    TEST(EnumToStrTests, TaskStatusTest)
    {
        for (size_t i = 0; i < (size_t)Task::Status::COUNT; i++) {
            Task::Status status = (Task::Status)i;
            EXPECT_NE(ChangeLog::taskStatusToStr(status), std::string());
        }
    }

    TEST(EnumToStrTests, GenderTest)
    {
        for (size_t i = 0; i < (size_t)Gender::COUNT; i++) {
            Gender gender = (Gender)i;
            EXPECT_NE(ChangeLog::genderToStr(gender), std::string());
        }
    }

    TEST(EnumToStrTests, EmployeeStatusTest)
    {
        for (size_t i = 0; i < (size_t)EmployeeStatus::COUNT; i++) {
            EmployeeStatus status = (EmployeeStatus)i;
            EXPECT_NE(ChangeLog::employeeStatusToStr(status), std::string());
        }
    }

    TEST(EnumToStrTests, AccessLevelTest)
    {
        for (size_t i = 0; i < (size_t)AccessRole::COUNT; i++) {
            AccessRole level = (AccessRole)i;
            EXPECT_NE(ChangeLog::accessLevelStr(level), std::string());
        }
    }

    TEST(EnumToStrTests, ClientTypeTest)
    {
        for (size_t i = 0; i < (size_t)Client::ClientType::COUNT; i++) {
            Client::ClientType type = (Client::ClientType)i;
            EXPECT_NE(ChangeLog::clientTypeToStr(type), std::string());
        }
    }

    TEST(EnumToStrTests, LeadStatusTest)
    {
        for (size_t i = 0; i < (size_t)Client::LeadStatus::COUNT; i++) {
            Client::LeadStatus status = (Client::LeadStatus)i;
            EXPECT_NE(ChangeLog::leadStatusToStr(status), std::string());
        }
    }

    TEST(EnumToStrTests, LeadSourceTest)
    {
        for (size_t i = 0; i < (size_t)Client::LeadSource::COUNT; i++) {
            Client::LeadSource source = (Client::LeadSource)i;
            EXPECT_NE(ChangeLog::leadSourceToStr(source), std::string());
        }
    }

    TEST(EnumToStrTests, CompanyTypeTest)
    {
        for (size_t i = 0; i < (size_t)ExternalCompany::CompanyType::COUNT; i++) {
            ExternalCompany::CompanyType type = (ExternalCompany::CompanyType)i;
            EXPECT_NE(ChangeLog::companyTypeToStr(type), std::string());
        }
    }

    TEST(EnumToStrTests, CompanyRatingTest)
    {
        for (size_t i = 0; i < (size_t)ExternalCompany::Rating::COUNT; i++) {
            ExternalCompany::Rating rating = (ExternalCompany::Rating)i;
            EXPECT_NE(ChangeLog::companyRatingToStr(rating), std::string());
        }
    }

    TEST(EnumToStrTests, CompanyRiskLevelTest)
    {
        for (size_t i = 0; i < (size_t)ExternalCompany::RiskLevel::COUNT; i++) {
            ExternalCompany::RiskLevel riskLevel = (ExternalCompany::RiskLevel)i;
            EXPECT_NE(ChangeLog::companyRiskLevelToStr(riskLevel), std::string());
        }
    }

    TEST(EnumToStrTests, CompanyStatusTest)
    {
        for (size_t i = 0; i < (size_t)Company::CompanyStatus::COUNT; i++) {
            Company::CompanyStatus status = (Company::CompanyStatus)i;
            EXPECT_NE(ChangeLog::companyStatusToStr(status), std::string());
        }
    }

    TEST(EnumToStrTests, CompanySizeTest)
    {
        for (size_t i = 0; i < (size_t)ExternalCompany::CompanySize::COUNT; i++) {
            ExternalCompany::CompanySize size = (ExternalCompany::CompanySize)i;
            EXPECT_NE(ChangeLog::companySizeToStr(size), std::string());
        }
    }

    TEST(EnumToStrTests, CompanyComplianceLevelTest)
    {
        for (size_t i = 0; i < (size_t)ExternalCompany::ComplianceLevel::COUNT; i++) {
            ExternalCompany::ComplianceLevel level = (ExternalCompany::ComplianceLevel)i;
            EXPECT_NE(ChangeLog::companyComplianceLevelToStr(level), std::string());
        }
    }

    TEST(EnumToStrTests, InfluenceLevelTest)
    {
        for (size_t i = 0; i < (size_t)ExternalEmployee::InfluenceLevel::COUNT; i++) {
            ExternalEmployee::InfluenceLevel level = (ExternalEmployee::InfluenceLevel)i;
            EXPECT_NE(ChangeLog::influenceLevelToStr(level), std::string());
        }
    }

    TEST(EnumToStrTests, IntegrationStatusTest)
    {
        for (size_t i = 0; i < (size_t)ExternalCompany::IntegrationStatus::COUNT; i++) {
            ExternalCompany::IntegrationStatus status = (ExternalCompany::IntegrationStatus)i;
            EXPECT_NE(ChangeLog::integrationStatusToStr(status), std::string());
        }
    }

    TEST(EnumToStrTests, ReportTypeTest)
    {
        for (size_t i = 0; i < (size_t)ReportType::COUNT; i++) {
            ReportType type = (ReportType)i;
            EXPECT_NE(ChangeLog::reportTypeToStr(type), std::string());
        }
    }

    TEST(EnumToStrTests, ExportFormatTest)
    {
        for (size_t i = 0; i < (size_t)ExportFormat::COUNT; i++) {
            ExportFormat format = (ExportFormat)i;
            EXPECT_NE(ChangeLog::exportFormatToStr(format), std::string());
        }
    }

    TEST(EnumToStrTests, CampaignTypeTest)
    {
        for (size_t i = 0; i < (size_t)CampaignType::COUNT; i++) {
            CampaignType type = (CampaignType)i;
            EXPECT_NE(ChangeLog::campaignTypeToStr(type), std::string());
        }
    }

    TEST(EnumToStrTests, CaseStatusTest)
    {
        for (size_t i = 0; i < (size_t)CaseStatus::COUNT; i++) {
            CaseStatus status = (CaseStatus)i;
            EXPECT_NE(ChangeLog::caseStatusToStr(status), std::string());
        }
    }
}  // namespace unit