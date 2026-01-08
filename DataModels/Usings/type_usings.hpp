#pragma once
#include <memory>
#include <optional>
#include <string>
#include <utility>

struct BaseInteraction;
class Client;
class Money;
struct Date;
class InternalEmployee;
class ChangeLog;
class CampaignLead;
class FileMetadata;
class Task;
struct Deal;
struct PhoneNumber;
struct Address;
class ExternalEmployee;
class Campaign;
class TimeDuration;
class Person;
struct Message;
struct CommentarySocialNetworks;
struct Document;
class OfferDeal;
struct Payment;
struct InteractionResult;
struct EmailLetter;
struct Meeting;
struct Offer;
class Company;
class ExternalCompany;
class InternalEmployeeDataBase;
class UserSession;
struct TenantContext;

using UserSessionPtr              = std::shared_ptr<UserSession>;
using DurationPtr                 = std::shared_ptr<TimeDuration>;
using FileMetadataPtr             = std::shared_ptr<FileMetadata>;
using ExternalCompanyPtr          = std::shared_ptr<ExternalCompany>;
using InteractionPtr              = std::shared_ptr<BaseInteraction>;
using WeakDealPtr                 = std::weak_ptr<Deal>;
using CompanyPtr                  = std::shared_ptr<Company>;
using WeakInternalEmployee        = std::weak_ptr<InternalEmployee>;
using InternalEmployeePtr         = std::shared_ptr<InternalEmployee>;
using OfferPtr                    = std::shared_ptr<Offer>;
using DealPtr                     = std::shared_ptr<Deal>;
using WeakPersonPtr               = std::weak_ptr<Person>;
using PersonPtr                   = std::shared_ptr<Person>;
using MeetingPtr                  = std::shared_ptr<Meeting>;
using AddressPtr                  = std::shared_ptr<Address>;
using WeakClientPtr               = std::weak_ptr<Client>;
using ClientPtr                   = std::shared_ptr<Client>;
using DocumentPtr                 = std::shared_ptr<Document>;
using FilePtr                     = std::shared_ptr<FileMetadata>;
using StringPair                  = std::pair<std::string, std::string>;
using EmailLetterPtr              = std::shared_ptr<EmailLetter>;
using MessagePtr                  = std::shared_ptr<Message>;
using CommentarySocialNetworksPtr = std::shared_ptr<CommentarySocialNetworks>;
using WeakCampaignPtr             = std::weak_ptr<Campaign>;
using StringPtr                   = std::shared_ptr<std::string>;
using OptionalStr                 = std::optional<std::string>;
using BaseInteractionPtr          = std::shared_ptr<BaseInteraction>;
using MoneyPtr                    = std::shared_ptr<Money>;
using DatePtr                     = std::shared_ptr<Date>;
using CampaignLeadPtr             = std::shared_ptr<CampaignLead>;
using ChangeLogPtr                = std::shared_ptr<ChangeLog>;
using CampaignPtr                 = std::shared_ptr<Campaign>;
using PhoneNumberPtr              = std::shared_ptr<PhoneNumber>;
using ExternalEmployeePtr         = std::shared_ptr<ExternalEmployee>;
using WeakExternalEmployee        = std::weak_ptr<ExternalEmployee>;
using TaskPtr                     = std::shared_ptr<Task>;
using WeakBuyerShare              = std::pair<std::weak_ptr<Person>, Money>;
using PaymentPtr                  = std::shared_ptr<Payment>;
using OfferDealPtr                = std::shared_ptr<OfferDeal>;