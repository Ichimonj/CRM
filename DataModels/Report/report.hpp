#pragma once
#include <memory>

#include "big_uint.hpp"
#include "date.hpp"
#include "external_employee.hpp"

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
    auto getType() const -> const ReportType;
    auto getOtherType() const -> const OptionalStr&;
    auto getData() const -> const std::vector<std::string>&;
    auto getGeneratedDate() const -> const DatePtr&;
    auto getParameters() const -> const std::vector<StringPair>&;
    auto getCreator() const -> const InternalEmployeePtr&;
    auto getExportFormat() const -> const ExportFormat;
    /// @}

    /// @name Setters
    /// @{
    void setType(ReportType type, const InternalEmployeePtr& changer);
    void setOtherType(const OptionalStr& other_type, const InternalEmployeePtr& changer);

    void addData(const std::string& data, const InternalEmployeePtr& changer);
    void delData(size_t index, const InternalEmployeePtr& changer);

    void addParameter(const StringPair& parameter, const InternalEmployeePtr& changer);
    void delParameter(size_t index, const InternalEmployeePtr& changer);

    void setCreator(const InternalEmployeePtr& creator, const InternalEmployeePtr& changer);
    void setExportFormat(ExportFormat export_format, const InternalEmployeePtr& changer);
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