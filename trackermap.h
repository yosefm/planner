/*	Defines a class that stores int values per string keys, tracks
	the keys' use or disuse through its slots, and can give a sum 
	of values of the used keys. */

#ifndef TRACKERMAP_H
#define TRACKERMAP_H

#include <map>
#include <qobject.h>

class QString;

typedef std::map<QString, float> NameToVal;

class TrackerMap : public QObject {
	Q_OBJECT
private:
	NameToVal	trackees;

public:
	TrackerMap		(QObject * parent = 0) : QObject(parent) {}
	void removeKey	(QString key); // To add a key, use slot keyUsed.
	bool isUsed		(QString key) const;

	NameToVal::mapped_type value (const QString& key) const; // 0 if unused.
	NameToVal::mapped_type total () const;

public slots:
	void keyUsed	(QString key, float value);
	void keyUnused	(QString key, float value);
};

#endif
