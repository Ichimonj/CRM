#include "interaction_data_base.hpp"

#include <algorithm>

#include "DataModels/Person/Employee/internal_employee.hpp"
#include "Logger/events_log.hpp"

const std::vector<InteractionPtr> InteractionDataBase::empty_vector;
//
void InteractionDataBase::add(const InteractionPtr& interaction)
{
    if (interaction == nullptr) return;

    if (this->by_id.find(interaction->getId()) != by_id.end()) return;

    this->by_id[interaction->getId()] = interaction;

    if (interaction->getExternalId()) {
        const std::string& interaction_id = interaction->getExternalId().value();
        this->by_external_id.emplace(interaction_id, interaction);
    }
    if (!interaction->getTitle().empty()) {
        std::string title = interaction->getTitle();
        std::transform(title.begin(), title.end(), title.begin(), ::tolower);
        this->by_title_substr_search.emplace(title, interaction);
    }

    this->by_created_date.emplace(interaction->getCreatedDate(), interaction);

    if (interaction->getStartDate()) {
        const Date date = *interaction->getStartDate();
        this->by_start_date.emplace(date, interaction);
    }
    if (interaction->getEndDate()) {
        const Date date = *interaction->getEndDate();
        this->by_end_date.emplace(date, interaction);
    }

    this->by_type[interaction->getType()].push_back(interaction);
    this->by_priority[interaction->getPriority()].push_back(interaction);

    for (const auto& tag : interaction->getTags()) {
        this->by_tags[tag].push_back(interaction);
    }

    if (!interaction->getManager().expired()) {
        const BigUint& manager_id = interaction->getManager().lock()->getId();
        this->by_manager[manager_id].push_back(interaction);
    }
    for (const auto& person : interaction->getParticipants()) {
        if (!person.expired()) {
            this->by_participants[person.lock()->getId()].push_back(interaction);
        }
    }
}

void InteractionDataBase::safe_remove(const BigUint& id, const Date& remove_date)
{
    auto id_it = this->by_id.find(id);
    if (id_it == by_id.end()) {
        return;
    }

    InteractionPtr interaction = id_it->second;

    if (interaction->getExternalId()) {
        const std::string& interaction_id = interaction->getExternalId().value();
        safeRemoveFromMap(
            this->by_external_id, interaction_id, interaction, __LINE__, "by_external_id"
        );
    }
    if (!interaction->getTitle().empty()) {
        std::string title = interaction->getTitle();
        std::transform(title.begin(), title.end(), title.begin(), ::tolower);
        safeRemoveFromMap(
            this->by_title_substr_search, title, interaction, __LINE__, "by_title_substr_search"
        );
    }

    safeRemoveFromMap(
        this->by_created_date,
        interaction->getCreatedDate(),
        interaction,
        __LINE__,
        "by_created_date"
    );

    if (interaction->getStartDate()) {
        const Date date = *interaction->getStartDate();
        safeRemoveFromMap(this->by_start_date, date, interaction, __LINE__, "by_start_date");
    }
    if (interaction->getEndDate()) {
        const Date date = *interaction->getEndDate();
        safeRemoveFromMap(this->by_end_date, date, interaction, __LINE__, "by_end_date");
    }

    safeRemoveFromVector(this->by_type, interaction->getType(), interaction, __LINE__, "by_type");
    safeRemoveFromVector(
        this->by_priority, interaction->getPriority(), interaction, __LINE__, "by_priority"
    );
    for (const auto& tag : interaction->getTags()) {
        safeRemoveFromVector(this->by_tags, tag, interaction, __LINE__, "by_tags");
    }

    if (!interaction->getManager().expired()) {
        const auto manager = interaction->getManager().lock();
        safeRemoveFromVector(
            this->by_manager, manager->getId(), interaction, __LINE__, "by_manager"
        );
    }
    for (const auto& person : interaction->getParticipants()) {
        const BigUint& person_id = person.lock()->getId();
        safeRemoveFromVector(
            this->by_participants, person_id, interaction, __LINE__, "by_participants"
        );
    }
    this->removed.push_back({Date(), interaction});
    this->by_id.erase(interaction->getId());
}

void InteractionDataBase::hard_remove(const size_t index)
{
    if (index < this->removed.size()) {
        this->removed.erase(this->removed.begin() + index);
    }
}

auto InteractionDataBase::size() const -> size_t { return this->by_id.size(); }

bool InteractionDataBase::empty() const { return this->by_id.empty(); }

auto InteractionDataBase::getAll() const -> const std::unordered_map<BigUint, InteractionPtr>&
{
    return this->by_id;
}

auto InteractionDataBase::getByExternalId() const
    -> const std::unordered_map<std::string, InteractionPtr>&
{
    return this->by_external_id;
}

auto InteractionDataBase::getByTitle() const -> const std::multimap<std::string, InteractionPtr>&
{
    return this->by_title_substr_search;
}

auto InteractionDataBase::getByCreatedDate() const -> const std::multimap<Date, InteractionPtr>&
{
    return this->by_created_date;
}

auto InteractionDataBase::getByStartDate() const -> const std::multimap<Date, InteractionPtr>&
{
    return this->by_start_date;
}

auto InteractionDataBase::getByEndDate() const -> const std::multimap<Date, InteractionPtr>&
{
    return this->by_end_date;
}

auto InteractionDataBase::getByType() const
    -> const std::unordered_map<InteractionType, std::vector<InteractionPtr>>&
{
    return this->by_type;
}

auto InteractionDataBase::getByPriority() const
    -> const std::unordered_map<Priority, std::vector<InteractionPtr>>&
{
    return this->by_priority;
}

auto InteractionDataBase::getByTags() const
    -> const std::unordered_map<std::string, std::vector<InteractionPtr>>&
{
    return this->by_tags;
}

auto InteractionDataBase::getByManager() const
    -> const std::unordered_map<BigUint, std::vector<InteractionPtr>>&
{
    return this->by_manager;
}

auto InteractionDataBase::getByParticipants() const
    -> const std::unordered_map<BigUint, std::vector<InteractionPtr>>&
{
    return this->by_participants;
}

auto InteractionDataBase::getRemoved() const -> const std::vector<std::pair<Date, InteractionPtr>>&
{
    return this->removed;
}

auto InteractionDataBase::findById(const BigUint& id) const -> const InteractionPtr
{
    auto interaction = this->by_id.find(id);
    if (interaction != this->by_id.end()) {
        return interaction->second;
    }
    return nullptr;
}

auto InteractionDataBase::findByExternalId(const std::string& external_id) const
    -> const InteractionPtr
{
    auto interaction = this->by_external_id.find(external_id);
    if (interaction != this->by_external_id.end()) {
        return interaction->second;
    }
    return nullptr;
}

auto InteractionDataBase::findByTitleSubstr(const std::string& title) const
    -> const std::vector<InteractionPtr>
{
    if (title.empty()) return empty_vector;

    std::string key = title;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    auto first = this->by_title_substr_search.lower_bound(key);
    key.back()++;
    auto second = this->by_title_substr_search.lower_bound(key);

    if (first == second) return empty_vector;

    std::vector<InteractionPtr> result;
    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto InteractionDataBase::findByCreatedDate(const Date& date) const
    -> const std::vector<InteractionPtr>
{
    auto interaction = this->by_created_date.equal_range(date);
    if (interaction.first == interaction.second) return empty_vector;

    std::vector<InteractionPtr> result;
    for (auto it = interaction.first; it != interaction.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto InteractionDataBase::findByCreatedDateRange(const Date& first_date, const Date& second_date)
    const -> const std::vector<InteractionPtr>
{
    auto first  = this->by_created_date.lower_bound(first_date);
    auto second = this->by_created_date.lower_bound(second_date);

    if (first == second) return this->empty_vector;

    std::vector<InteractionPtr> result;

    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto InteractionDataBase::findByStartDate(const Date& date) const
    -> const std::vector<InteractionPtr>
{
    auto interaction = this->by_start_date.equal_range(date);
    if (interaction.first == interaction.second) return empty_vector;

    std::vector<InteractionPtr> result;
    for (auto it = interaction.first; it != interaction.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto InteractionDataBase::findByStartDateRange(const Date& first_date, const Date& second_date)
    const -> const std::vector<InteractionPtr>
{
    auto first  = this->by_start_date.lower_bound(first_date);
    auto second = this->by_start_date.lower_bound(second_date);

    if (first == second) return this->empty_vector;

    std::vector<InteractionPtr> result;

    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto InteractionDataBase::findByEndDate(const Date& date) const -> const std::vector<InteractionPtr>
{
    auto interaction = this->by_end_date.equal_range(date);
    if (interaction.first == interaction.second) return empty_vector;

    std::vector<InteractionPtr> result;
    for (auto it = interaction.first; it != interaction.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto InteractionDataBase::findByEndDateRange(const Date& first_date, const Date& second_date) const
    -> const std::vector<InteractionPtr>
{
    auto first  = this->by_end_date.lower_bound(first_date);
    auto second = this->by_end_date.lower_bound(second_date);

    if (first == second) return this->empty_vector;

    std::vector<InteractionPtr> result;

    for (auto it = first; it != second; ++it) {
        result.push_back(it->second);
    }
    return result;
}

auto InteractionDataBase::findByType(const InteractionType type) const
    -> const std::vector<InteractionPtr>&
{
    auto interactions = this->by_type.find(type);
    if (interactions != this->by_type.end()) {
        return interactions->second;
    }
    return empty_vector;
}

auto InteractionDataBase::findByPriority(const Priority priority) const
    -> const std::vector<InteractionPtr>&
{
    auto interactions = this->by_priority.find(priority);
    if (interactions != this->by_priority.end()) {
        return interactions->second;
    }
    return empty_vector;
}

auto InteractionDataBase::findByTag(const std::string& tag) const
    -> const std::vector<InteractionPtr>&
{
    auto interactions = this->by_tags.find(tag);
    if (interactions != this->by_tags.end()) {
        return interactions->second;
    }
    return empty_vector;
}

auto InteractionDataBase::findByManger(const BigUint& id) const
    -> const std::vector<InteractionPtr>&
{
    auto interactions = this->by_manager.find(id);
    if (interactions != this->by_manager.end()) {
        return interactions->second;
    }
    return empty_vector;
}

auto InteractionDataBase::findByParticipants(const BigUint& id) const
    -> const std::vector<InteractionPtr>&
{
    auto interactions = this->by_participants.find(id);
    if (interactions != this->by_participants.end()) {
        return interactions->second;
    }
    return empty_vector;
}

void InteractionDataBase::changeExternalId(
    const BigUint& id, const OptionalStr& external_id, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InteractionPtr interaction = id_it->second;

    //
    auto old_id = interaction->getExternalId();
    if (interaction->setExternalId(external_id, changer)) {
        if (old_id) {
            safeRemoveFromMap(
                this->by_external_id, old_id.value(), interaction, __LINE__, "by_external_id"
            );
        }
        if (external_id) {
            this->by_external_id.emplace(external_id.value(), interaction);
        }
    }
}

void InteractionDataBase::changeTitle(
    const BigUint& id, const std::string& title, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InteractionPtr interaction = id_it->second;

    //
    std::string old_title = interaction->getTitle();
    if (interaction->setTitle(title, changer)) {
        if (!old_title.empty()) {
            std::transform(old_title.begin(), old_title.end(), old_title.begin(), ::tolower);
            safeRemoveFromMap(
                this->by_title_substr_search,
                old_title,
                interaction,
                __LINE__,
                "by_title_substr_search"
            );
        }
        if (!title.empty()) {
            std::string new_title = title;
            std::transform(new_title.begin(), new_title.end(), new_title.begin(), ::tolower);
            this->by_title_substr_search.emplace(new_title, interaction);
        }
    }
}

void InteractionDataBase::changeStartDate(
    const BigUint& id, const DatePtr& date, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InteractionPtr interaction = id_it->second;

    //
    auto old_date = interaction->getStartDate();

    if (interaction->setStartDate(date, changer)) {
        if (old_date) {
            safeRemoveFromMap(
                this->by_start_date, *old_date, interaction, __LINE__, "by_start_date"
            );
        }
        if (date) {
            this->by_start_date.emplace(*date, interaction);
        }
    }
}

void InteractionDataBase::changeEndDate(
    const BigUint& id, const DatePtr& date, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InteractionPtr interaction = id_it->second;

    //
    auto old_date = interaction->getEndDate();

    if (interaction->setEndDate(date, changer)) {
        if (old_date) {
            safeRemoveFromMap(this->by_end_date, *old_date, interaction, __LINE__, "by_end_date");
        }
        if (date) {
            this->by_end_date.emplace(*date, interaction);
        }
    }
}

void InteractionDataBase::changePriority(
    const BigUint& id, const Priority priority, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InteractionPtr interaction = id_it->second;

    //
    Priority old_priority = interaction->getPriority();

    if (interaction->setPriority(priority, changer)) {
        safeRemoveFromVector(this->by_priority, old_priority, interaction, __LINE__, "by_priority");
        this->by_priority[priority].push_back(interaction);
    }
}

void InteractionDataBase::addTag(
    const BigUint& id, const std::string& tag, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InteractionPtr interaction = id_it->second;

    if (interaction->addTag(tag, changer)) {
        this->by_tags[tag].push_back(interaction);
    }
}

void InteractionDataBase::delTag(
    const BigUint& id, const size_t index, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InteractionPtr interaction = id_it->second;

    if (interaction->getTags().size() <= index) return;

    std::string old_tag = interaction->getTags()[index];

    if (interaction->delTag(index, changer)) {
        safeRemoveFromVector(this->by_tags, old_tag, interaction, __LINE__, "by_tags");
    }
}

void InteractionDataBase::changeManager(
    const BigUint& id, const WeakInternalEmployee& manager, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InteractionPtr interaction = id_it->second;

    auto           old_manager = interaction->getManager();

    if (interaction->setManager(manager, changer)) {
        if (!old_manager.expired()) {
            auto old_manager_id = old_manager.lock()->getId();
            safeRemoveFromVector(
                this->by_manager, old_manager_id, interaction, __LINE__, "by_manager"
            );
        }
        if (!manager.expired()) {
            auto manager_id = manager.lock()->getId();
            this->by_manager[manager_id].push_back(interaction);
        }
    }
}

void InteractionDataBase::addParticipants(
    const BigUint& id, const WeakPersonPtr& participant, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InteractionPtr interaction = id_it->second;

    if (interaction->addParticipants(participant, changer)) {
        auto participant_id = participant.lock()->getId();
        this->by_participants[participant_id].push_back(interaction);
    }
}

void InteractionDataBase::delParticipants(
    const BigUint& id, const size_t index, const InternalEmployeePtr& changer
)
{
    auto id_it = this->by_id.find(id);
    if (id_it == this->by_id.end()) return;

    InteractionPtr interaction = id_it->second;

    if (interaction->getParticipants().size() <= index) return;

    const BigUint& old_participant_id = interaction->getParticipants()[index].lock()->getId();

    if (interaction->delParticipants(index, changer)) {
        safeRemoveFromVector(
            this->by_participants, old_participant_id, interaction, __LINE__, "by_participants"
        );
    }
}

void InteractionDataBase::removeManager(const BigUint& id) { this->by_manager.erase(id); }

void InteractionDataBase::removeParticipant(const BigUint& id) { this->by_participants.erase(id); }

void InteractionDataBase::safeRemoveFromMap(
    auto&                 map,
    const auto&           key,
    const InteractionPtr& interaction,
    const size_t          line,
    const std::string&    index_name
)
{
    auto range = map.equal_range(key);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == interaction) {
            map.erase(it);
            return;
        }
    }
    this->logEmptyContainer(__FILE__, line, interaction->getId().num, index_name);
}

void InteractionDataBase::safeRemoveFromVector(
    auto&                 map,
    const auto&           key,
    const InteractionPtr& interaction,
    const size_t          line,
    const std::string&    index_name
)
{
    auto& vec = map[key];
    if (vec.empty()) {
        this->logEmptyContainer(__FILE__, line, interaction->getId().num, index_name);

    } else {
        vec.erase(std::remove(vec.begin(), vec.end(), interaction), vec.end());
        if (vec.empty()) {
            map.erase(key);
        }
    }
}

void InteractionDataBase::logEmptyContainer(
    const std::string& file,
    const size_t       line,
    const std::string& interaction_id,
    const std::string& index_name
)
{
    EventLog::getInstance().log(
        LOG_LEVEL::ERROR,
        file,
        line,
        "Data inconsistency in " + index_name + "\nInteraction id: " + interaction_id +
            "\nExpected entry is missing."
    );
}