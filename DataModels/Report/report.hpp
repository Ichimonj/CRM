#pragma once
#include <memory>

#include "BigNum/big_uint.hpp"
#include "DateTime/date.hpp"
#include "Person/Employee/external_employee.hpp"

using DatePtr             = std::shared_ptr<Date>;
using InternalEmployeePtr = std::shared_ptr<InternalEmployee>;
using StringPair          = std::pair<std::string, std::string>;

enum class ReportType : uint8_t {
    SalesSummary,
    Pipeline,
    RevenueByManager,
    ClientActivity,
    ProductPerformance,
    EmployeeKPI,
    InteractionSummary,
    FinancialForecast,
    other,
    COUNT
};
enum class ExportFormat : uint8_t { CSV, PDF, JSON, XLSX, COUNT };
class Report {
public:
    Report(
        const BigUint&                 id,
        const ReportType&              type,
        const OptionalStr&             other_type,
        std::vector<std::string>       data,
        const DatePtr&                 generated_date,
        const std::vector<StringPair>& parameters,
        const InternalEmployeePtr&     creator,
        const ExportFormat&            export_format
    );

    /// @name Getters
    /// @{
    auto getId() const -> const BigUint&;
    auto getType() const -> ReportType;
    auto getOtherType() const -> const OptionalStr&;
    auto getData() const -> const std::vector<std::string>&;
    auto getGeneratedDate() const -> const DatePtr&;
    auto getParameters() const -> const std::vector<StringPair>&;
    auto getCreator() const -> const InternalEmployeePtr&;
    auto getExportFormat() const -> ExportFormat;
    /// @}

    /// @name Setters
    /// @{
    bool setType(ReportType type, const InternalEmployeePtr& changer);
    bool setOtherType(const OptionalStr& other_type, const InternalEmployeePtr& changer);

    bool addData(const std::string& data, const InternalEmployeePtr& changer);
    bool delData(size_t index, const InternalEmployeePtr& changer);

    bool addParameter(const StringPair& parameter, const InternalEmployeePtr& changer);
    bool delParameter(size_t index, const InternalEmployeePtr& changer);

    bool setCreator(const InternalEmployeePtr& creator, const InternalEmployeePtr& changer);
    bool setExportFormat(ExportFormat export_format, const InternalEmployeePtr& changer);
    /// @}

private:
    BigUint                   id;
    ReportType                type;
    OptionalStr               other_type;
    std::vector<std::string>  data;
    DatePtr                   generated_date;
    std::vector<StringPair>   parameters;
    InternalEmployeePtr       creator;
    ExportFormat              export_format = ExportFormat::JSON;

    std::vector<ChangeLogPtr> change_logs;
};