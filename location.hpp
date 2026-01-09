#pragma once
#include <string>

namespace errors {
    inline std::string phone_number_incorrect  = "Phone number incorrect";
    inline std::string year_incorrect          = "Year incorrect";
    inline std::string month_incorrect         = "Month incorrect";
    inline std::string day_incorrect           = "Day incorrect";
    inline std::string hour_incorrect          = "Hour incorrect";
    inline std::string min_incorrect           = "Min incorrect";
    inline std::string file_open_error         = "Failed to open the file";
    inline std::string not_enough_products     = "Not enough products";
    inline std::string client_add_incorrect    = "The client already exists";
    inline std::string client_not_found        = "Client not found";
    inline std::string phone_number_bus        = "The phone number is busy";
    inline std::string invalid_currency_format = "Invalid currency format";
    inline std::string uint_constructor_error  = "Use only numbers 0...9";
    inline std::string negative_date_range     = "Negative date range";

}  // namespace errors

namespace warning {
    inline std::string internal_employee_removed =
        "Internal employee has been removed from the database";
    inline std::string external_employee_removed =
        "External employee has been removed from the database";
    inline std::string client_removed = "Client has been removed from the database";
    inline std::string person_removed = "Person has been removed from the database";
    inline std::string deal_removed = "Deal has been removed from the database";
}  // namespace warning
namespace names_str {
    inline std::string addDock     = "New document";
    inline std::string delDock     = "Delete document";
    inline std::string deal        = "Deal";
    inline std::string interaction = "Interaction";
    inline std::string file        = "File";
}  // namespace names_str
namespace month_str {
    inline std::string january   = "Jan";
    inline std::string february  = "Feb";
    inline std::string march     = "Mar";
    inline std::string april     = "Apr";
    inline std::string may       = "May";
    inline std::string june      = "Jun";
    inline std::string july      = "Jul";
    inline std::string august    = "Aug";
    inline std::string september = "Sep";
    inline std::string october   = "Oct";
    inline std::string november  = "Nov";
    inline std::string december  = "Dec";
}  // namespace month_str
namespace time_str {
    inline std::string week   = "wk";
    inline std::string weeks  = "wks";
    inline std::string day    = "d";
    inline std::string hour   = "hr";
    inline std::string minute = "min";
    inline std::string second = "sec";
}  // namespace time_str

namespace interaction_result_status_str {
    inline std::string success         = "The meeting ended successfully";
    inline std::string failure         = "The meeting ended unsuccessfully";
    inline std::string partialSuccess  = "Partial progress was achieved";
    inline std::string followUpNeeded  = "Further interaction is required";
    inline std::string canceled        = "The meeting was canceled before completion";
    inline std::string postponed       = "The meeting was postponed";
    inline std::string issueIdentified = "An issue was identified requiring resolution";
    inline std::string noOutcome       = "The meeting resulted in no specific outcome";
    inline std::string other           = "Other result status";
}  // namespace interaction_result_status_str

namespace meeting_status_str {
    inline std::string scheduled  = "The meeting is scheduled";
    inline std::string inProgress = "The meeting is currently in progress";
    inline std::string completed  = "The meeting has been completed";
    inline std::string canceled   = "The meeting was canceled";
    inline std::string postponed  = "The meeting was postponed";
}  // namespace meeting_status_str

namespace meeting_outcome_str {
    inline std::string closedWon            = "The meeting resulted in a successful deal";
    inline std::string closedLost           = "The meeting resulted in a lost deal";
    inline std::string progressMade         = "Progress was made during the meeting";
    inline std::string followUpScheduled    = "A follow-up meeting was scheduled";
    inline std::string informationProvided  = "Information was provided during the meeting";
    inline std::string decisionPending      = "A decision is pending after the meeting";
    inline std::string additionalInfoNeeded = "Additional information is required";
    inline std::string postponed            = "The meeting was postponed";
    inline std::string canceled             = "The meeting was canceled";
    inline std::string redirected           = "The meeting was redirected to another party";
    inline std::string issueIdentified      = "An issue was identified during the meeting";
    inline std::string other                = "Other outcome";
}  // namespace meeting_outcome_str

namespace meeting_type_str {
    inline std::string negotiation  = "The meeting is a negotiation session";
    inline std::string presentation = "The meeting is a presentation";
    inline std::string training     = "The meeting is a training session";
    inline std::string other        = "Other meeting type";
}  // namespace meeting_type_str

namespace email_letter_type_str {
    inline std::string incoming = "The email is incoming";
    inline std::string outgoing = "The email is outgoing";
}  // namespace email_letter_type_str

namespace email_status_str {
    inline std::string sent      = "The email was sent";
    inline std::string delivered = "The email was delivered";
    inline std::string failed    = "The email failed to send or deliver";
    inline std::string draft     = "The email is a draft";
    inline std::string scheduled = "The email is scheduled for sending";
    inline std::string replied   = "The email has been replied to";
    inline std::string forwarded = "The email has been forwarded";
}  // namespace email_status_str

namespace call_type_str {
    inline std::string incoming = "The call is incoming";
    inline std::string outgoing = "The call is outgoing";
    inline std::string missed   = "The call was missed";
}  // namespace call_type_str

namespace interaction_type_str {
    inline std::string phoneCall                = "Interaction is a phone call";
    inline std::string emailLetter              = "Interaction is an email letter";
    inline std::string emailThread              = "Interaction is an email thread";
    inline std::string meeting                  = "Interaction is a meeting";
    inline std::string meetingThread            = "Interaction is a meeting thread";
    inline std::string message                  = "Interaction is a message";
    inline std::string correspondence           = "Interaction is correspondence";
    inline std::string commentarySocialNetworks = "Interaction is a commentary on social networks";
    inline std::string commentarySocialNetworksThread =
        "Interaction is a social networks commentary thread";
    inline std::string unknown = "Interaction type is unknown";
}  // namespace interaction_type_str

namespace priority_str {
    inline std::string low      = "Low";
    inline std::string medium   = "Medium";
    inline std::string high     = "High";
    inline std::string critical = "Critical";
    inline std::string null     = "Other";
}  // namespace priority_str

namespace payment_status_str {
    inline std::string pending   = "Waiting for payment";
    inline std::string completed = "Completed";
    inline std::string failed    = "Not paid for";
    inline std::string refunded  = "Refunded";
    inline std::string partial   = "Partially paid for";
    inline std::string overdue   = "Overdue";
}  // namespace payment_status_str

namespace deal_status_str {
    inline std::string draft                      = "Draft";
    inline std::string readyForCoordination       = "Ready for coordination";
    inline std::string readyForSigned             = "Ready for signed";
    inline std::string coordination               = "Coordination is underway";
    inline std::string signedByCounterparty       = "Signed by the counterparty";
    inline std::string signedBySecondSide         = "Signed by the second side";
    inline std::string allSigned                  = "All parties signed";
    inline std::string deleted                    = "Deleted";
    inline std::string canceled                   = "Canceled";
    inline std::string registered                 = "Registered";
    inline std::string beginningDealBroken        = "Beginning of the rupture of the deal";
    inline std::string endDealBroken              = "End of the rupture of the deal";
    inline std::string obligationsAreProcess      = "In the process of fulfilling obligations";
    inline std::string obligationsAreFulfilled    = "All obligations are fulfilled";
    inline std::string obligationsAreNotFulfilled = "The obligations are not fulfilled";
    inline std::string other                      = "Other";
}  // namespace deal_status_str

namespace document_status_str {
    inline std::string draft    = "Draft";
    inline std::string active   = "Active";
    inline std::string expired  = "Time expired";
    inline std::string archived = "Archived";
}  // namespace document_status_str

namespace task_status_str {
    inline std::string not_started = "Not started";
    inline std::string in_progress = "In progress";
    inline std::string completed   = "Complited";
    inline std::string overdue     = "Overdue";
}  // namespace task_status_str

namespace gender_str {
    inline std::string male    = "Male";
    inline std::string female  = "Female";
    inline std::string unknown = "Unknown";
}  // namespace gender_str

namespace access_level_str {
    inline std::string admin           = "Administrator";
    inline std::string sales_rep       = "Sales Representative";
    inline std::string executive       = "Executive";
    inline std::string manager         = "Manager";
    inline std::string marketing_user  = "Marketing User";
    inline std::string read_only       = "Read Only";
    inline std::string sales_manager   = "Sales Manager";
    inline std::string service_manager = "Service Manager";
    inline std::string support         = "Support";
    inline std::string decision_maker  = "Decision Maker";
    inline std::string influencer      = "Influencer";
    inline std::string user            = "User";
    inline std::string gatekeeper      = "Gatekeeper";
    inline std::string other           = "Other";
}  // namespace access_level_str

namespace employee_status_str {
    inline std::string active     = "Active";
    inline std::string vacation   = "Vacation";
    inline std::string fired      = "Fired";
    inline std::string education  = "Education";
    inline std::string internship = "Internship";
    inline std::string probation  = "Probation";
    inline std::string suspended  = "Suspended";
    inline std::string sick_leave = "Sick Leave";
    inline std::string retired    = "Retired";
    inline std::string other      = "Other";
}  // namespace employee_status_str

namespace client_type_str {
    inline std::string visitor          = "Visitor";
    inline std::string lead             = "Lead";
    inline std::string prospect         = "Prospect";
    inline std::string customer         = "Costomer";
    inline std::string loyal_customer   = "Loyal Customer";
    inline std::string partner          = "Partner";
    inline std::string potential_client = "Potential Client";
    inline std::string lost_customer    = "Lost Customer";
    inline std::string analytical       = "Analytical";
    inline std::string emotional        = "Emotional";
    inline std::string other            = "Other";
}  // namespace client_type_str

namespace lead_status_str {
    inline std::string new_         = "New";
    inline std::string open         = "Open";
    inline std::string working      = "Working";
    inline std::string qualified    = "Qualified";
    inline std::string unqualified  = "Unqualified";
    inline std::string converted    = "Converted";
    inline std::string closed       = "Closed";
    inline std::string disqualified = "Disqualified";
    inline std::string nurturing    = "Nurturing";
    inline std::string lost         = "Lost";
}  // namespace lead_status_str

namespace lead_source_str {
    inline std::string website        = "Website";
    inline std::string referral       = "Referral";
    inline std::string email_campaign = "Email campaign";
    inline std::string social_media   = "Social media";
    inline std::string other          = "Other";
}  // namespace lead_source_str

namespace company_type_str {
    inline std::string client   = "Client";
    inline std::string partner  = "Partner";
    inline std::string vendor   = "Vendor";
    inline std::string prospect = "Prospect";
    inline std::string supplier = "Supplier";
    inline std::string other    = "Other";
}  // namespace company_type_str

namespace rating_str {
    inline std::string hot      = "Hot";
    inline std::string warm     = "Warm";
    inline std::string cold     = "Cold";
    inline std::string inactive = "Inactive";
}  // namespace rating_str

namespace risk_level_str {
    inline std::string low      = "Low";
    inline std::string medium   = "Medium";
    inline std::string high     = "High";
    inline std::string critical = "Critical";
}  // namespace risk_level_str

namespace company_status_str {
    inline std::string active   = "Active";
    inline std::string inactive = "Inactive";
    inline std::string archived = "Archived";
}  // namespace company_status_str

namespace company_size_str {
    inline std::string micro      = "Micro";
    inline std::string small      = "Small";
    inline std::string medium     = "Medium";
    inline std::string large      = "Large";
    inline std::string enterprise = "Enterprise";
}  // namespace company_size_str

namespace compliance_level_str {
    inline std::string compliant     = "Compliant";
    inline std::string warning       = "Warning";
    inline std::string non_compliant = "NonCompliant";
}  // namespace compliance_level_str

namespace influence_level_str {
    inline std::string critical = "Critical";
    inline std::string high     = "High";
    inline std::string medium   = "Medium";
    inline std::string low      = "Low";
    inline std::string very_low = "Very Low";
}  // namespace influence_level_str

namespace integration_status_str {
    inline std::string connected = "Connected";
    inline std::string pending   = "Pending";
    inline std::string failed    = "Failed";
}  // namespace integration_status_str

namespace report_type_str {
    inline std::string SalesSummary       = "Sales Summary";
    inline std::string Pipeline           = "Pipeline";
    inline std::string RevenueByManager   = "Revenue by Manager";
    inline std::string ClientActivity     = "Client Activity";
    inline std::string ProductPerformance = "Product Performance";
    inline std::string EmployeeKPI        = "Employee KPI";
    inline std::string InteractionSummary = "Interaction Summary";
    inline std::string FinancialForecast  = "Financial Forecast";
    inline std::string other              = "Other";
}  // namespace report_type_str

namespace export_format_str {
    inline std::string CSV  = "CSV";
    inline std::string PDF  = "PDF";
    inline std::string JSON = "JSON";
    inline std::string XLSX = "XLSX";
}  // namespace export_format_str

namespace campaign_type_str {
    inline std::string email      = "Email";
    inline std::string social_ads = "Social Ads";
    inline std::string webinar    = "Webinar";
    inline std::string event      = "Event";
    inline std::string other      = "Other";
}  // namespace campaign_type_str

namespace case_status_str {
    inline std::string open        = "Open";
    inline std::string in_progress = "In Progress";
    inline std::string resolved    = "Resolved";
    inline std::string closed      = "Closed";
}  // namespace case_status_str
