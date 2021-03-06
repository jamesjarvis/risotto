//
// Created by rvigee on 10/4/19.
//

#include "VariablesTable.h"

#include <utility>

VariableEntry::VariableEntry(std::string name, TypeDescriptor *typeRef, int index) : name(std::move(name)),
                                                                                     typeRef(typeRef), index(index) {

}

VariableEntry *VariablesTable::find(const std::string &name) {
    for (auto entry : entries) {
        if (entry->name == name) {
            return entry;
        }
    }

    return nullptr;
}

VariableEntry *VariablesTable::add(std::string name, TypeDescriptor *typeDesc) {
    auto entry = new VariableEntry(std::move(name), typeDesc, entries.size());

    entries.push_back(entry);

    return entry;
}
