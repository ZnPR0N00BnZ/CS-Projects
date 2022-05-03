
#include "LevelList.h"

LevelList::LevelList(): m_sequence()
{};

bool LevelList::add(unsigned long level) {
    if (level < 30 || level >400 || m_sequence.size() == DEFAULT_MAX_ITEMS) {
        return false;
    }
    else {
        m_sequence.insert(level);
        return true;
    }
}
bool LevelList::remove(unsigned long level) {
    return m_sequence.erase(m_sequence.find(level));
}

int LevelList::size() const {
    return m_sequence.size();
}

unsigned long LevelList:: minimum() const {
    if (m_sequence.empty()) {
        return NO_LEVEL;
    }
    else {
        unsigned long lowestLevel = 0;
        m_sequence.get(0,lowestLevel);
        return lowestLevel;
    }
}

unsigned long LevelList::maximum() const {
    if (m_sequence.empty()) {
        return NO_LEVEL;
    }
    else {
        unsigned long highestLevel = 0;
        m_sequence.get(m_sequence.size()-1, highestLevel);
        return highestLevel;
    }
}


