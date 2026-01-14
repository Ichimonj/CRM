#pragma once
#include <map>
#include <unordered_map>

#include "DataModels/Interaction/base_interaction.hpp"
#include "Usings/type_usings.hpp"

using InteractionType = BaseInteraction::InteractionType;
class InteractionDataBase {
public:
    void add(const InteractionPtr& interaction);
    void safe_remove(const BigUint& id, const Date& remove_date);
    void hard_remove(const size_t index);

    /// @name Getters
    /// @{
    auto size() const -> size_t;
    bool empty() const;
    auto getAll() const -> const std::unordered_map<BigUint, InteractionPtr>&;
    auto getByExternalId() const -> const std::unordered_map<std::string, InteractionPtr>&;
    auto getByTitle() const -> const std::multimap<std::string, InteractionPtr>&;
    auto getByCreatedDate() const -> const std::multimap<Date, InteractionPtr>&;
    auto getByStartDate() const -> const std::multimap<Date, InteractionPtr>&;
    auto getByEndDate() const -> const std::multimap<Date, InteractionPtr>&;
    auto getByType() const
        -> const std::unordered_map<InteractionType, std::vector<InteractionPtr>>&;
    auto getByPriority() const -> const std::unordered_map<Priority, std::vector<InteractionPtr>>&;
    auto getByTags() const -> const std::unordered_map<std::string, std::vector<InteractionPtr>>&;
    auto getByManager() const -> const std::unordered_map<BigUint, std::vector<InteractionPtr>>&;
    auto getByParticipants() const
        -> const std::unordered_map<BigUint, std::vector<InteractionPtr>>&;
    auto getRemoved() const -> const std::vector<std::pair<Date, InteractionPtr>>&;
    ///@}

    /// @name Find functions
    /// @{
    auto findById(const BigUint& id) const -> const InteractionPtr;
    auto findByExternalId(const std::string& extrenal_id) const -> const InteractionPtr;
    auto findByTitleSubstr(const std::string& title) const -> const std::vector<InteractionPtr>;

    auto findByCreatedDate(const Date& date) const -> const std::vector<InteractionPtr>;
    auto findByCreatedDateRange(const Date& first_date, const Date& second_date) const
        -> const std::vector<InteractionPtr>;

    auto findByStartDate(const Date& date) const -> const std::vector<InteractionPtr>;
    auto findByStartDateRange(const Date& first_date, const Date& second_date) const
        -> const std::vector<InteractionPtr>;

    auto findByEndDate(const Date& date) const -> const std::vector<InteractionPtr>;
    auto findByEndDateRange(const Date& first_date, const Date& second_date) const
        -> const std::vector<InteractionPtr>;

    auto findByType(const InteractionType type) const -> const std::vector<InteractionPtr>&;
    auto findByPriority(const Priority priority) const -> const std::vector<InteractionPtr>&;
    auto findByTag(const std::string& tag) const -> const std::vector<InteractionPtr>&;
    auto findByManger(const BigUint& id) const -> const std::vector<InteractionPtr>&;
    auto findByParticipants(const BigUint& id) const -> const std::vector<InteractionPtr>&;
    /// @}

    /// @name Change functions
    /// @{
    void changeExternalId(
        const BigUint& id, const OptionalStr& external_id, const InternalEmployeePtr& changer
    );
    void changeTitle(
        const BigUint& id, const std::string& title, const InternalEmployeePtr& changer
    );
    void changeStartDate(
        const BigUint& id, const DatePtr& date, const InternalEmployeePtr& changer
    );
    void changeEndDate(const BigUint& id, const DatePtr& date, const InternalEmployeePtr& changer);
    void changePriority(
        const BigUint& id, const Priority priority, const InternalEmployeePtr& changer
    );

    void addTag(const BigUint& id, const std::string& tag, const InternalEmployeePtr& changer);
    void delTag(const BigUint& id, const size_t index, const InternalEmployeePtr& changer);

    void changeManager(
        const BigUint& id, const WeakInternalEmployee& manager, const InternalEmployeePtr& changer
    );
    void addParticipants(
        const BigUint& id, const WeakPersonPtr& participant, const InternalEmployeePtr& changer
    );
    void delParticipants(const BigUint& id, const size_t index, const InternalEmployeePtr& changer);
    /// @}

    /// @name Auxiliary functions
    /// @{
    void removeManager(const BigUint& id);
    void removeParticipant(const BigUint& id);
    /// @}

private:
    static const std::vector<InteractionPtr>                         empty_vector;
    std::unordered_map<BigUint, InteractionPtr>                      by_id;
    std::unordered_map<std::string, InteractionPtr>                  by_external_id;
    std::multimap<std::string, InteractionPtr>                       by_title_substr_search;

    std::multimap<Date, InteractionPtr>                              by_created_date;
    std::multimap<Date, InteractionPtr>                              by_start_date;
    std::multimap<Date, InteractionPtr>                              by_end_date;

    std::unordered_map<InteractionType, std::vector<InteractionPtr>> by_type;
    std::unordered_map<Priority, std::vector<InteractionPtr>>        by_priority;
    std::unordered_map<std::string, std::vector<InteractionPtr>>     by_tags;

    //
    std::unordered_map<BigUint, std::vector<InteractionPtr>> by_manager;
    std::unordered_map<BigUint, std::vector<InteractionPtr>> by_participants;
    std::vector<std::pair<Date, InteractionPtr>>             removed;

    //
    void safeRemoveFromMap(
        auto&                 map,
        const auto&           key,
        const InteractionPtr& interaction,
        const size_t          line,
        const std::string&    index_name
    );
    void safeRemoveFromVector(
        auto&                 map,
        const auto&           key,
        const InteractionPtr& interaction,
        const size_t          line,
        const std::string&    index_name
    );

    void logEmptyContainer(
        const std::string& file,
        const size_t       line,
        const std::string& interaction_id,
        const std::string& index_name
    );
};
