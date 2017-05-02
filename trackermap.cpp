#include "trackermap.h"
#include <qstring.h>

// <keyUsed> adds 'value' to key. Creates the key if not present.
void TrackerMap::keyUsed (QString key, float value) {
	trackees[key] += value;
}

// <keyUnused> subtracts 'value' from key but does not remove it.
void TrackerMap::keyUnused (QString key, float value) {
	trackees[key] -= value;
}

// Completely remove a key, regardless of its value.
void TrackerMap::removeKey (QString key) {
	trackees.erase(key);
}

bool TrackerMap::isUsed (QString key) const {
	return ( trackees.find(key) != trackees.end() );
}

NameToVal::mapped_type TrackerMap::value (const QString& key) const {
	return (trackees.find(key))->second;
}

NameToVal::mapped_type TrackerMap::total() const {
	NameToVal::mapped_type total = 0;

	for (NameToVal::const_iterator iter = trackees.begin(); 
	iter != trackees.end(); iter++) {
		total += iter->second;
	}

	return total;
}
