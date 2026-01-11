#include <stdint.h>
enum class PersonFields : uint8_t {
    Name,
    Surname,
    Patronymic,
    Birthday,
    UpdateAt,
    PhoneNumber,
    MorePhoneNumber,
    Address,
    MoreAddress,
    Email,
    RelatedDeals,
    MoreEmail,
    Gender,
    OtherDocuments,
    OtherFiles,
    InteractionHistory,
    Tags,
    PreferredLanguage,
    Notes
};

enum class BaseInteractionFields : uint8_t {
    Id,
    ExternalID,
    Title,
    Description,
    Subject,
    InteractionDuration,
    StartDate,
    EndDate,
    Type,
    Priority,
    Tags,
    MoreData,
    Manager,
    Checker,
    Participants,
    Results,
    Notes,
    RelatedInteractions,
    AttachmentFiles,
    Campaigns
};

enum class CommentarySocialNetworksFields : uint8_t {
    Nickname,
    Author,
    Commentary,
    AnswerTo,
    Answer,
    DateSending,
    IsFirst
};

enum class CommentarySocialNetworksThreadFields : uint8_t { Comments };

enum class CorrespondenceFields : uint8_t { Messages, Platform };

enum class EmailLetterFields : uint8_t {
    FromEmailAddress,
    ToEmailAddress,
    LetterType,
    EmailStatus,
    CcEmailAddresses,
    BccEmailAddresses,
    Sender,
    Recipient,
    Body,
    SendDate,
    ReceivedDate,
    ReadTime,
    EmailProvider,
    PreviousLetter,
    NextLetter,
    IsRead,
    IsFlagged
};

enum class EmailThreadFields : uint8_t {
    Letters,
    Clients,
    Employees
};

enum class InteractionResultFields : uint8_t {
    InteractionResultTitle,
    Description,
    ResultStatus,
    Documents,
    Deals,
    PlannedInteractions,
    Files,
    IdentifiedIssue,
    Tags,
    MoreData,
    ChangeLogs
};

enum class MeetingFields : uint8_t {
    Location,
    MeetingStatus,
    MeetingType,
    Outcomes,
    OtherOutcomes,
    OtherType,
    Record,
    Clients,
    Employees,
    Invitees,
    PreviousMeeting,
    NextMeeting,
    CreatedDate,
    IsConfirmed,
    IsVirtual
};

enum class MeetingThreadFields : uint8_t { Meetings, Clients, Employees };

enum class MessageFields : uint8_t { Nickname, Author, Message, Platform, DateSending };

enum class PhoneCallFields : uint8_t {
    FromNumber,
    ToNumber,
    StartCall,
    EndCall,
    CallCreator,
    CallProvider,
    CallType
};

enum class DocumentFields : uint8_t {
    Id,
    DocumentTitle,
    DocumentName,
    DocumentNumber,
    Path,
    EnteredForce,
    StoppedWorking,
    DocumentPath,
    Partners,
    Status,
    Creator,
    File
};

enum class FileMetadataFields : uint8_t {
    Id,
    FileName,
    FileFormat,
    FilePath,
    FileSize,
    UploadDate,
    Content
};

enum class DealFields : uint8_t {
    ContractNumber,
    Title,
    Description,
    Source,
    Tags,
    Buyers,
    TotalAmount,
    PaidAmount,
    Currency,
    OtherCurrency,
    PaymentTransactions,
    Status,
    OtherStatus,
    DealPriority,
    DrawingDate,
    DateApproval,
    CreationDate,
    Manager,
    AssignedEmployees,
    Offers,
    Offerings,
    Documents,
    Task,
    DealManager,
    Owner
};

enum class TaskFields : uint8_t {
    Title,
    Description,
    Subject,
    Status,
    Priority,
    CreatedDate,
    Deadline,
    StartDate,
    ETC,
    ATS,
    CreatedBy,
    Manager,
    Deals,
    Task,
    File,
    Notes,
    MoreData,
    Teem
};
enum class InternalEmployeeFields : uint8_t {
    Id,
    Manager,
    Position,
    Department,
    Role,
    Status,
    SalesTerritory,
    LastLoginDate,
    LastActionDate,
    TimeZone,
    Leads,
    CommissionRate,
    Notes,
    MonthlyQuota,
    Tasks,
    OwnedDeals,
    Documents,
    BaseSalary,
    Skills,
    PerformanceScore,
    DirectReports,
    HireDate,
    DismissalDate,
    IsActive,
    ManagerDeals,
    ProposedOffers,
    NextReviewDate
};

enum class ClientFields : uint8_t {
    Owner,
    Type,
    OtherType,
    LeadSource,
    OtherLeadSource,
    Interactions,
    ActivInteraction,
    BoughtDeals,
    ActivDeal,
    InterestedOffers,
    LeadStatus,
    LeadScore,
    AnnualRevenue,
    LifetimeValue,
    Tags,
    Notes,
    MoreData,
    CommunicationChannel,
    ReferralCode,
    CustomerAcquisitionCost,
    OwnedDeals,
    MarketingConsent
};

enum class CompanyFields : uint8_t {
    CompanyName,
    LegalName,
    WebsiteUrl,
    SicCode,
    PhoneNumber,
    Email,
    Notes,
    RegisteredAddress,
    CreatedAt,
    MorePhoneNumbers,
    MoreEmails,
    EmployeeCount,
    AnnualRevenue,
    Industry,
    CountryCode,
    FoundedDate,
    TaxId,
    Status,
    Budget,
    TaxRates,
    Deals,
    Tasks
};

enum class ExternalCompanyFields : uint8_t {
    Type,
    OtherType,
    Size,
    Rating,
    RiskLevel,
    AccountManager,
    VatNumber,
    LastInteractionDate,
    PreferredContactMethod,
    PaymentTerms,
    PreferredCurrency,
    WinRate,
    Contacts,
    ComplianceStatus,
    AssociatedClients,
    CreditLimit,
    TotalRevenueGenerated,
    OutstandingBalance,
    Documents,
    ChurnProbability,
    ServiceLevelAgreement,
    PreferredIntegrationTool,
    IntegrationStatus
};
enum class ExternalEmployeeFields : uint8_t {
    Company,
    JobTitle,
    Department,
    Role,
    OtherRole,
    CurrentInteraction,
    LastContactDate,
    InfluenceScore,
    Salary,
    AssignedDeals,
    CompletedDeals,
    AssignedTasks,
    CompletedTasks,
    SocialNetworks,
    MoreData,
    Notes,
    InteractionHistory,
    TimeZone,
    PreferredContactTime,
    DecisionInfluence,
    BudgetAuthority,
    PainPoints,
    Status
};

enum class PaymentFields : uint8_t {
    RequestedAmount,
    SendingAmount,
    ReceivedAmount,
    TaxAmount,
    Currencies,
    SendingDate,
    ReceivedDate,
    CreationDate,
    PaymentStatus,
    PaymentMethod,
    Deal,
    Payer,
    PayerCompany,
    InvoiceNumber,
    TransactionId,
    PaymentPurpose,
    Documents,
    Comments,
    CreatedBy,
    ChangeLogs
};

enum class ReportFields : uint8_t {
    Type,
    Data,
    GeneratedDate,
    Parameters,
    Creator,
    ExportFormat
};
enum class CampaignFields : uint8_t {
    Name,
    Type,
    OtherType,
    StartDate,
    EndDate,
    Budget,
    BudgetSpent,
    TotalJoined,
    TotalConverted,
    Creator,
    ConversionRate,
    Notes,
    TargetLeads
};
enum class CaseField : uint8_t {
    Title,
    Description,
    Status,
    Priority,
    CreateDate,
    ResolvedDate,
    AssignedTo,
    RelatedClient,
    Notes,
    RelatedInteractions
};