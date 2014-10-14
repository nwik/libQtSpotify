#ifndef QSPOTIFYQUEUETRACKLIST_H
#define QSPOTIFYQUEUETRACKLIST_H

#include "qspotifytracklist.h"

class QSpotifyQueueTrackList : public QSpotifyTrackList
{
public:
    QSpotifyQueueTrackList(QObject *parent = nullptr)
        : QSpotifyTrackList(parent) {}

    virtual void setShuffle(bool s);
};

#endif // QSPOTIFYQUEUETRACKLIST_H
